package SIMS;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class query_p {

    private final JButton bt;
    private final JTextField id1;
    private final JTextField sid1;
    private final JTextField level1;
    private final JTextField des1;
    private final JLabel id;
    private final JLabel sid;
    private final JLabel level;
    private final JLabel des;
    private final JLabel rt;
    private final  JTextField rt1;
    private final  JLabel ab;
    private final JTextField ab1;

    public query_p(){
        JFrame jf=new JFrame();
        jf.setTitle("学籍变更查询");
        jf.setSize(400,400);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

        Font ft=new Font("宋体",Font.PLAIN,20);

        this.id=new JLabel("变更记录号：");
        this.id1=new JTextField(20);
        Box hb1=Box.createHorizontalBox();
        id.setFont(ft);
        id1.setFont(ft);
        hb1.add(id);
        hb1.add(id1);

        this.sid=new JLabel("学    号：");
        this.sid1=new JTextField(20);
        Box hb2=Box.createHorizontalBox();
        sid.setFont(ft);
        sid1.setFont(ft);
        hb2.add(sid);
        hb2.add(sid1);

        this.level=new JLabel("变更等级：");
        this.level1=new JTextField(20);
        Box hb3=Box.createHorizontalBox();
        level.setFont(ft);
        level1.setFont(ft);
        hb3.add(level);
        hb3.add(Box.createHorizontalStrut(2));
        hb3.add(level1);

        this.rt=new JLabel("时    间：");
        this.rt1=new JTextField(20);
        Box hb=Box.createHorizontalBox();
        rt.setFont(ft);
        rt1.setFont(ft);
        hb.add(rt);
        hb.add(Box.createHorizontalStrut(2));
        hb.add(rt1);

        this.ab=new JLabel("是否生效：");
        this.ab1=new JTextField(20);
        Box hb4=Box.createHorizontalBox();
        ab.setFont(ft);
        ab1.setFont(ft);
        hb4.add(ab);
        hb4.add(Box.createHorizontalStrut(2));
        hb4.add(ab1);

        this.des=new JLabel("描    述：");
        this.des1=new JTextField(20);
        des.setFont(ft);
        des1.setFont(ft);
        Box hb7=Box.createHorizontalBox();
        hb7.add(des);
        hb7.add(des1);

        bt=new JButton("确认");
        Box hb8=Box.createVerticalBox();
        hb8.add(Box.createHorizontalStrut(210));
        hb8.add(bt);
        bt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String id=id1.getText();
                String sid=sid1.getText();
                String level=level1.getText();
                String time=rt1.getText();
                String able=ab1.getText();
                String des=des1.getText();
                connect con=new connect();
                con.getconnection();
                connect.ptable(id,sid,level,time,able,des);
            }
        });
        JPanel vb1 = new JPanel(new FlowLayout(FlowLayout.CENTER));
        Box vb=Box.createVerticalBox();
        vb.add(hb1);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb2);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb3);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb4);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb7);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb8);
        vb1.add(vb);
        jf.setContentPane(vb1);
        jf.setVisible(true);
    }
}