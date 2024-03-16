#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <windows.h>
#include <mutex>
#include <chrono>
#include <random>

#define MAX_SEQ 7
#define BUFS ( (MAX_SEQ + 1)/2 )
using namespace std;

#define REC 0
#define SED 1

typedef int seq_nr;
typedef char packet;
typedef enum{network_layer_ready, frame_arr, cksum_err, 
            timeout, 
            ack_timeout} event_type;

typedef enum{data, ack, nak} frame_kind;

bool no_nak = true;
seq_nr oldest_frame = MAX_SEQ + 1;

typedef struct{
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;

}frame;

// 线程锁 
mutex mtx;

queue<frame> network[2];


void getFrame(frame &r, int id);
void getFrame(frame &r, int id){
    r = network[id].front();
    network[id].pop();
}




static bool between(seq_nr a, seq_nr b, seq_nr c){
    return ((a <= b) && (b < c));
}

static void send_frame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expected,packet buff[], int id){

    frame s;
    s.kind = fk;

    if(fk == frame_kind::data){
        s.info = buff[ frame_nr % BUFS ];
    }
    s.seq = frame_nr;

    s.ack =frame_expected;

    if (fk == frame_kind::nak)
        no_nak = false;
    
    mtx.lock();
    cout <<"发送的类型为: " << s.kind << 
            " 发送的frame: " << s.seq << 
            ", 确认号为: " << s.ack << 
            " 发送的目的地为:" << id <<
            " 发送的信息为:" << s.info << endl;
    mtx.unlock();

    if(fk == frame_kind::ack){}; 

    network[id].push(s); 

    // if (fk == frame_kind::data)
    //     cout << "他的数据为: " << s.info << endl;
}

void inc(int &sequence_number) {
    sequence_number = (sequence_number + 1) % (MAX_SEQ + 1);
}



void protocol6(int res, int dest, int fuc){
    // 接收期待
    // 即是发送下限
    seq_nr ack_expected;

    // 下一个发送的frame
    // 发送的上限
    seq_nr next_frame_to_send;

    // 期待的frame
    // 接收下限
    seq_nr frame_expected;

    // 发送的最远距离
    // 接收的上限
    seq_nr too_far;

    // 缓冲池的索引
    int i;
    frame r;
    packet out_buf[BUFS];
    packet in_buf[BUFS];
    // 判断是否已经到达
    bool arrived[BUFS];

    // 有多少输出缓冲区现在被使用
    seq_nr nbuffered;

    // 事件类型
    event_type event;

    // 判断此刻作为接收者还是发送者
    if(fuc == REC){
        event = frame_arr;
    }else{
        event = network_layer_ready;
    }

    // 初始化操作
    ack_expected = 0;   
    next_frame_to_send = 0;
    frame_expected = 0;
    too_far = BUFS;
    nbuffered = 0;
    for(i = 0; i < BUFS; ++i){
        arrived[i] = false;
    }

    // 模拟传输或者接收的次数
    int j  = rand() % 4;

    // 用于模拟传输的数据;
    int datalen = 46;
    char a[datalen+5] = "safsakf;laskf;lasml;mas;lvma;lsmv;lasfa;lsm;l$";
    char b[datalen+5] = {'0'};

    for(int k = 0; k < BUFS && k < datalen; k++){
        out_buf[k] = a[k];
    }

    // 用于计算是否超时
    int start = 0;
    int end = 0;

    while(true){
        if(j == 0){
            j = rand() % 4;
            Sleep(rand() % 2000);
        }
        j--;
        // 等待事件的产生
        // 模拟检验和错误
        if(fuc == REC && event !=ack_timeout){
            int k = rand() % 10;
            if( k  < 5){
                event = cksum_err;
            }else{
                event = frame_arr;
            }
        }

        // 发送完所有数据
        if(ack_expected == datalen && fuc == SED){
            break;
        }

        // 判断发送方的当前时间
        if(fuc == SED && event != timeout){
            if (nbuffered == BUFS){
                event = frame_arr;
            }else{
                event = network_layer_ready;
            }
        }

        switch(event){
            case network_layer_ready:{
                nbuffered = nbuffered +1;

                if(next_frame_to_send >= datalen) break ;
                if( rand() % 10 < 5){
                    send_frame(frame_kind::data, next_frame_to_send, frame_expected, out_buf, dest);
                }else{
                    mtx.lock();
                    cout << "丢弃本次数据发送"<< endl;
                    mtx.unlock();
                }
                next_frame_to_send++;
                // 获取当前时间 发送时;
                start = clock();
                break;
            }
            case frame_arr:{
                
                if(network[res].size() == 0){
                    // 获取发送接收的回应的时间
                    if(fuc == SED){
                        end = clock();
                        // mtx.lock();
                        // cout << "发送者方:开始的时间:" << start << " 结束的时间:" << end << " 时间差:" << end - start << endl;
                        // mtx.unlock();

                        // 1000
                        if(end -start >= 500){
                            mtx.lock();
                            cout << "发送者方:开始的时间:" << start << " 结束的时间:" << end << " 时间差:" << end - start << endl;
                            mtx.unlock();
                            event = timeout;
                        }

                    }

                    if(fuc == REC){
                        end = clock();
                        // mtx.lock();
                        // cout << "接收者方:开始的时间:" << start << " 结束的时间:" << end << " 时间差:" << end - start << endl;
                        // mtx.unlock();


                        // 700
                        if(end -start >= 500){
                            mtx.lock();
                            cout << "接收者方:开始的时间:" << start << " 结束的时间:" << end << " 时间差:" << end - start << endl;
                            mtx.unlock();
                            event = ack_timeout;
                        }

                    }
                    break;
                }

                getFrame(r, res);

                if(r.kind == frame_kind::data){

                    if((r.seq != frame_expected && no_nak)){
                        send_frame(nak, 0, frame_expected ,out_buf, dest);
                        break;
                    }

                    if(between(frame_expected, r.seq, too_far) && (arrived[r.seq % BUFS] == false)){
                        arrived[r.seq % BUFS] = true;
                        in_buf[r.seq % BUFS] = r.info;


                        mtx.lock();
                        cout << res << "线程" << "接收的frame: " << r.seq << " 期待的确认号为" << frame_expected;
                        cout << "信息为:" << r.info << endl;
                        mtx.unlock();

                        while(arrived[frame_expected % BUFS]){

                            b[frame_expected] =  in_buf[frame_expected % BUFS];
                            
                            no_nak = true;

                            arrived[frame_expected % BUFS] = false;

                            frame_expected++;

                            too_far++;
                            
                        }
                    }

                    if(j == 0 || network[res].size() == 0){
                        if(rand() % 10 <5){
                            send_frame(ack, 0, frame_expected ,out_buf, dest);
                            start = clock();
                        }else{
                            mtx.lock();
                            cout << "丢弃本次确认发送"<< endl;
                            mtx.unlock();
                        }
                    }

                }else if(r.kind == nak){

                    ack_expected = r.ack;
                    nbuffered =  0;
                    next_frame_to_send = ack_expected;
                    for(int k = ack_expected; k < ack_expected + 4 && k < datalen; k++){
                        out_buf[k % BUFS] = a[k];
                    }

                    mtx.lock();
                        cout << "收到了nck" << " 消息确认号为:"<< r.ack <<" 滑动的窗口为" << nbuffered <<endl;
                    mtx.unlock();

                }else if(r.kind == ack){
                    ack_expected = r.ack;
                    nbuffered =  0;
                    next_frame_to_send = ack_expected;
                    for(int k = ack_expected; k < ack_expected + 4 && k < datalen; k++){
                        out_buf[k % BUFS] = a[k];
                    }

                    mtx.lock();
                    cout << "收到了ack" << " 消息确认号为:"<< r.ack <<" 滑动的窗口为" << nbuffered <<endl;
                    mtx.unlock();
                }

                break;
            }
            case cksum_err:{
                if(no_nak){
                    mtx.lock();
                    cout <<"出现了cksum_err"<<endl;
                    mtx.unlock();
                    send_frame(nak, 0, frame_expected, out_buf, dest);
                }
                break;
            }
            case timeout:{
                mtx.lock();
                cout <<"出现了timeout"<<endl;
                mtx.unlock();
                next_frame_to_send = ack_expected;
                nbuffered = 0;
                event = network_layer_ready;
                break;
            }
            case ack_timeout:{
                mtx.lock();
                cout <<"出现了ack_timeout"<<endl;
                mtx.unlock();
                send_frame(ack, 0, frame_expected, out_buf, dest);
                start = clock();
                event = frame_arr;
                break;
            }
        }
        if(b[frame_expected - 1]== '$' && event == frame_arr){
            b[frame_expected -1] = '\0';
            cout << b << endl;
            send_frame(ack, 0, frame_expected, out_buf, dest);
            break;
        }
    }

}

int main(int argc, char *argv[]){
    // 随机数
    default_random_engine rand;
    rand.seed(time(0));

    thread sed = thread(protocol6, 0, 1, SED);
    thread rec = thread(protocol6, 1, 0, REC);
    sed.join();
    rec.join();



    system("pause");
    return 0;
}