/* Protocol 6 (Selective repeat) accepts frames out of order but passes packets to the
network layer in order. Associated with each outstanding frame is a timer. When the timer
expires, only that frame is retransmitted, not all the outstanding frames, as in protocol 5. */

/* Sender and receiver are the same */


/*	关键细节
*	
*	1.data，nak都可以携带ack，且每次发送data nak都会携带一个ack，这就意味着会发送重复确认
*	
*	2.receiver收到frame_expected对应的data_frame后，先前移下沿窗口，再发ack(捎带确认)
*	故当发送捎带确认时，ack的序列号总是当前frame_expected的前一个序列号
*
*	3.ATTENTION!!!!!
*	双方是等价的，都各有一个发送窗口和接收窗口，所以双方既是sender也是receiver
*	代码中的sender和receiver都是相对于本方而言
*
*	4.buffer大小
*	(MAX_SEQ+1)>>1 
*
*	5.序列号在buffer内定位
*	frame_nr % NR_BUFS
*
*	6.ack序列号为frame_expected的上一个序列号
*	(frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
*
*	7.请求sender重传的data frame的序列号=frame_expected, 6中得到的ack序列号的下一个
*	(r.ack+1)%(MAX_SEQ+1)
*/

#define MAX_SEQ 7 /* should be 2ˆn − 1 */
#define NR_BUFS ((MAX_SEQ + 1)/2) //4
typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready, ack_timeout} event_type;
#include "protocol.h"

boolean no nak = true; /* no nak has been sent yet */
seq_nr oldest_frame = MAX_SEQ + 1; /* initial value is only for the simulator */
//8

/*	
*	-:表示该区间是窗口区间
*	[0...a---b---c...7,0]:(a <= b) && (b < c)
*	[0---b---c...a---0]:(b < c) && (c < a)
*	[0---c...a---b---0]:(c < a) && (a <= b)
*/
//[a,c) 前闭后开区间 常用区间表示 STL常见到此类区间表示方法

static boolean between(seq_nr a, seq_nr b, seq_nr c)//已经有前提保证b>0
{
/* Same as between in protocol 5, but shorter and more obscure. */
	return ((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a));
}

/*
*	frame_expected对所有种类的frame一视同仁，都是当前本方receiver窗口下沿对应的窗口
*	接收方的frame_expected理论上的确不应该被其它任何值的改变所影响
*	
*	frame_kind=data, 则frame_nr=data_frame的序列号，frame_expected是用于计算获取s.ack（frame_expected的上一个=s.ack）
*	第四个参数是out_buf	
*	
*	s.fk=data, s.seq=frame_nr, s.ack, s.info
*	
*	frame_kind=nak, 则frame_nr无效（默认为0）, frame_expected用于计算s.ack, buffer为out_buf。
*	s.fk=nak, s.seq=0, s.ack, s.info
*	注意：此时的s.ack既有帮助处理nak也有捎带确认的功能（双重功效）
*	
*	发送nak的条件：nak尚未发出，此时receiver收到的data frame != frame_expected（窗口下沿）或checksum错误
*	接收处理nak的语句只有一个，即对上述两种需要发送nak的情况都用一块语句来接收处理。
*	
*	情况1：receiver收到的data frame != frame_expected（窗口下沿）
*	处理办法：假定对方sender窗口是[0 1 2]，本方receiver窗口是[0 1 2]，若对方sender发送0，本方sender回送的ack丢失，
*			但此时本方receiver窗口已经是[1 2 3]，对方会重发0，此时触发本方sender发送nak的情况1。nak的唯一实用参数是
*			本方frame_expected，在send_frame()中，s.ack=本方frame_expected的上一个，
*			在对方接受处理nak的语句中 if(r.kind==nak)，(r.ack+1)%(MAX_SEQ+1)=本方frame_expected=1
*			（这也是为什么这里不直接引用frame_expected而是用(r.ack+1)%(MAX_SEQ+1)计算frame_expected的原因）
*			（因为此时frame_expected是对方的参数，(r.ack+1)%(MAX_SEQ+1)才是本方的frame_expected）
*			会触发对方发送序列号为(r.ack+1)%(MAX_SEQ+1)的data frame，在这里是1，就是本方frame_expected
*			同时由于捎带确认机制，r.ack=本方frame_expected的上一个=0，故完成对0的确认。
*			实现对方sender发送状态同步。
*			（还有一种情况对方发送的data frame!=frame_expected，处理方法与上类似，这里不详细讨论）
*
*	情况2：对方sender发送的data frame的checksum错误
*	处理方法：假定对方sender窗口是[0 1 2]，本方receiver窗口是[0 1 2]，对方发送0错误，本方receiver窗口不变，根据上述分析，
*			会本方回送的nak不仅会触发对方sender重传0，还会给予对方的sender窗口下沿的“上一个”data frame进行确认。显然，后者
*			或者是一个正常确认，或者是一个无害的重复确认，故不碍事。
*				
*	ATTENTION:nak是识别出错误立即重发
*/

static void send_frame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expected, packet buffer[ ])
{
/* Construct and send a data, ack, or nak frame. */

	frame s; /* scratch variable */
	s.kind = fk; /* kind == data, ack, or nak */
	
	if (fk == data) 
		s.info = buffer[frame_nr % NR_BUFS];//NR_BUFS=4
	s.seq = frame_nr; /* only meaningful for data frames */

	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
	/*
	*	(3+7)%(7+1)=2
	*	(4+7)%(7+1)=3
	*	(7+7)%(7+1)=6
	*	(0+7)%(7+1)=7
	*	receiver收到data frame后，lower edge立即前移，“接着”发送
	*	对应的ack frame。故当发送ack frame时，该ack frame应该对应的是前一个
	*	data frame
	*	
	*	这里不能直接s.ack=frame_expected-1，否则当frame_expected=0时会出现bug
	*	这里必须+MAX_SEQ 否则无法实现“取前一个”的功能
	*	“这是个巧妙的处理方法”
	*/

	if (fk == nak) 
		no_nak = false; /* one_nak per frame, please */
	to_physical_layer(&s); /* transmit the frame */

	if (fk == data) 
		start_timer(frame_nr % NR_BUFS);
	stop_ack_timer(); /* no need for separate ack frame */ 
}

void protocol6(void)
{
	seq_nr ack_expected; /* lower edge of sender’s window */
	seq_nr next_frame_to_send; /* upper edge of sender’s window + 1 */
	seq_nr frame_expected; /* lower edge of receiver’s window */
	seq_nr too_far; /* upper edge of receiver’s window + 1 */
    

	int i; /* index into buffer pool */
	frame r; /* scratch variable */
	packet out_buf[NR_BUFS]; /* buffers for the outbound stream */
	packet in_buf[NR_BUFS]; /* buffers for the inbound stream */
	boolean arrived[NR_BUFS]; /* inbound bit map */
	//NR_BUFS=(MAX_SEQ+1)>>1=4
	seq_nr nbuffered; /* how many "output" buffers currently used */
	event_type event;

	enable_network_ayer(); /* initialize */

	ack_expected = 0; 
	/* next ack_expected on the inbound stream */
	/* lower edge of sender’s window */
	next_frame_to_send = 0; 
	/* number of next outgoing frame */
	/* upper edge of sender’s window + 1 */
	frame_expected = 0;
	/* lower edge of receiver’s window */
	too_far = NR_BUFS;
	/* upper edge of receiver’s window + 1 */
	
    // 最初没有数据包没缓冲
    nbuffered = 0; 
	/* initially no packets are buffered */

	for (i = 0; i < NR_BUFS; i++) 
		arrived[i] = false;
	
	double start;
	double end;

	while (true) 
	{
        /* 五种可能性：参见上面的事件类型 */
		
		 /* five possibilities: see event type above */
		switch(event) 
		{
            /* 接受、保存和传输新帧 */
			case network_layer_ready: /* accept, save, and transmit a new frame */
				nbuffered = nbuffered + 1; /* expand the sender window */
				from_network_layer(&out_buf[next_frame_to_send % NR_BUFS]); /* fetch new packet */
				/*
				*	当packet下来时，会存在buffer中，但此时sender窗口下沿还未打开。只有
				*	该frame被传输出去后，sender窗口下沿才会打开，然后该frame对应的窗口
				*	就是有效窗口（即刚刚窗口下沿打开了这个窗口）
				*/

				send_frame(data, next_frame_to_send, frame_expected, out_buf);/* transmit the frame */
				inc(next_frame_to_send); /* advance upper window edge */
				//先发frame 再打开窗口
				break;

			/* 数据或控制帧已到达 */
			case frame_arrival: /* a data or control frame has arrived */

                /* 从物理层获取传入帧 */
				from_physical_layer(&r); /* fetch incoming frame from physical layer */
				
				if (r.kind == data) 
				{
					/* An undamaged frame has arrived. */
					if ((r.seq != frame_expected) && no_nak)//本方receiver ack丢失 对方sender重传data frame 发nak同步对方sender的发送状态
						send_frame(nak, 0, frame_expected, out_buf); 
					else start_ack_timer();
					/* 
					*	进入else的前提：r.seq == frame_expected OR r.seq != frame_expected but no_nak == false
					*	第二种情况：对方sender传来了frame_expected之后的data frame 也需要收下但不push to network layer
					*	第一种情况：r.seq == receiver窗口下沿，则考虑往network layer push
					*	不确定
					*/

					if (between(frame_expected,r.seq,too_far) && (arrived[r.seq % NR_BUFS]==false)) 
					{
						/* Frames may be accepted in any order. */
						arrived[r.seq % NR_BUFS] = true; /* mark buffer as full */
						in_buf[r.seq % NR_BUFS] = r.info; /* insert data into buffer */
						
						while (arrived[frame_expected % NR_BUFS]) 
						{
							/*
							*	收到新的data frame后，此时在该frame之后的data frame可能都已经收到了
							*	于是一个一个前移sender的窗口下沿，只要下沿对应的data frame已到达，就
							*	push to network layer. 否则，即使下沿对应的frame之后的frame已经到达
							*	也不能移动窗口下沿
							*/
							/* Pass frames and advance window. */
							
							to_network_layer(&in_buf[frame_expected % NR_BUFS]);
							no_nak = true;//无异常，因此恢复no_nak
							arrived[frame_expected % NR_BUFS] = false;
							inc(frame_expected); /* advance lower edge of receiver’s window */
							inc(too_far); /* advance upper edge of receiver’s window */
							start_ack_timer(); /* to see if a separate ack is needed */ 
							//当且仅当出现了可以向network layer push data frame的情况时
							//才会start_ack_timer

						} //while (arrived[frame_expected % NR_BUFS]) 
					} //if (between(frame_expected,r.seq,too_far) && (arrived[r.seq % NR_BUFS]==false)) 
				} //if (r.kind == data) 
				
				if((r.kind==nak) && between(ack_expected,(r.ack+1)%(MAX_SEQ+1),next_frame_to_send))
				//本方receiver收到nak用于同步发送状态或重传错误frame
					send_frame(data, (r.ack+1) % (MAX_SEQ + 1), frame_expected, out_buf);
				/*	
				*	这里有一个很有趣的处理
				*	在send_frame()中，r.ack=receiver下沿对应窗口的上一个，
				*	（这是为了保证data nak携带正确的ack编号）
				*	且r.ack的范围只有0~7，而MAX_SEQ+1=8
				*	这意味着r.ack+1=receiver下沿对应窗口(frame_expected)
				* 	这里%MAX_SEQ的意义何在？
				*	若r.kind=nak 且 要求重发的frame的序列号在sender的窗口内，sender就会发一个序列号=frame_expected
				*	的data frame
				*/

				//捎带确认，data,nak都会稍带ack
				while (between(ack_expected, r.ack, next_frame_to_send)) 
				{
					nbuffered = nbuffered - 1; /* handle piggybacked ack */
					stop_timer(ack_expected % NR_BUFS); /* frame arrived intact */
					inc(ack_expected); /* advance lower edge of sender’s window */ 
				}
				break;
			// 检验和出错误
			case cksum_err://data frame错误 receiver传输nak
				if (no_nak) 
					send_frame(nak, 0, frame_expected, out_buf); /* damaged frame */
				break;
			
			case timeout://oldest_frame始终不更新？只适用于模拟，实际在其他部分更新？
					send_frame(data, oldest_frame, frame_expected, out_buf); /* we timed out */
				break;
			
			case ack_timeout:
				send_frame(ack,0,frame_expected, out_buf); /* ack timer expired; send ack */ 
		}
		
		if (nbuffered < NR_BUFS) 
			enable_network_layer(); 
		else 
			disable_network_layer();
	} 
}

















typedef struct{
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;

}frame;