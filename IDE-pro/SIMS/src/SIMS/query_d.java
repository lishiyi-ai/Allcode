package SIMS;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class query_d {

    private final JButton bt;
    private final JTextField id1;
    private final JTextField sid1;
    private final JLabel id;
    private final JLabel sid;

    public query_d(){
        JFrame jf=new JFrame();
        jf.setTitle("专业情况查询");
        jf.setSize(400,400);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

        Font ft=new Font("宋体",Font.PLAIN,20);

        this.id=new JLabel("专业号：");
        this.id1=new JTextField(20);
        Box hb1=Box.createHorizontalBox();
        id.setFont(ft);
        id1.setFont(ft);
        hb1.add(id);
        hb1.add(id1);

        this.sid=new JLabel("专业名称：");
        this.sid1=new JTextField(20);
        Box hb2=Box.createHorizontalBox();
        sid.setFont(ft);
        sid1.setFont(ft);
        hb2.add(sid);
        hb2.add(sid1);

        bt=new JButton("确认");
        Box hb8=Box.createVerticalBox();
        hb8.add(Box.createHorizontalStrut(210));
        hb8.add(bt);
        bt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String id=id1.getText();
                String sid=sid1.getText();
                connect con=new connect();
                con.getconnection();
                connect.dtable(id,sid);
            }
        });
        JPanel vb1 = new JPanel(new FlowLayout(FlowLayout.CENTER));
        Box vb=Box.createVerticalBox();
        vb.add(hb1);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb2);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb8);
        vb1.add(vb);
        jf.setContentPane(vb1);
        jf.setVisible(true);
    }
}