package SIMS;

import javax.swing.*;
import java.awt.*;

public class Educational {
    public Educational(){
        JFrame jf=new JFrame("教务信息输入");
        JLabel jt=new JLabel("教务系统");
        Box hb4=Box.createHorizontalBox();
        hb4.add(jt);
        jt.setFont(new Font("宋体",Font.PLAIN,60));
        Panel pl=new Panel(new FlowLayout());
        connect con=new connect();
        JButton abtp,abtr,pbt,rbt,chbt,achbt,qrbt,qpbt;
        JButton qcbt,cbt,dbt,qcbt1,qdbt;

        abtp=new JButton("处罚情况输入");
        abtp.addActionListener(e -> new Penalties());
        abtr=new JButton("奖励情况输入");
        abtr.addActionListener(e -> new Reward_situation());
        pbt=new JButton("所有处罚情况");
        pbt.addActionListener(e -> {
            con.getconnection();
            connect.ptable("","","","","","");
        });
        rbt=new JButton("所有奖励情况" );
        rbt.addActionListener(e -> {
            con.getconnection();
            connect.rtable("","","","","");
        });
        chbt=new JButton("学籍变更输入");
        chbt.addActionListener(e-> new Change_of_student_status());
        achbt=new JButton("学籍变更情况");
        achbt.addActionListener(e -> {
            con.getconnection();
            connect.chtable("","","","","");
        });
        qrbt=new JButton("奖励情况查询");
        qrbt.addActionListener(e->{
            new query_r();
        });
        qcbt=new JButton("变更情况查询");
        qcbt.addActionListener(e->{
            new query_ch();
        });
        qpbt=new JButton("处罚情况查询");
        qpbt.addActionListener(e->{
            new query_p();
        });
        //第一行
        Box hb1=Box.createHorizontalBox();
        hb1.add(abtr);
        hb1.add(Box.createHorizontalStrut(20));
        hb1.add(rbt);
        hb1.add(Box.createHorizontalStrut(20));
        hb1.add(qrbt);
        //第二行
        Box hb5=Box.createHorizontalBox();
        hb5.add(chbt);
        hb5.add(Box.createHorizontalStrut(20));
        hb5.add(achbt);
        hb5.add(Box.createHorizontalStrut(20));
        hb5.add(qcbt);
        //第三行
        Box hb3=Box.createHorizontalBox();
        hb3.add(abtp);
        hb3.add(Box.createHorizontalStrut(20));
        hb3.add(pbt);
        hb3.add(Box.createHorizontalStrut(20));
        hb3.add(qpbt);
        //第四行
        Box hb6=Box.createHorizontalBox();
        cbt=new JButton("所有班级情况");
        cbt.addActionListener(e->{
            con.getconnection();
            connect.ctable("","","");
        });
        qcbt1=new JButton("班级情况查询");
        qcbt1.addActionListener(e->{
            new query_c();
        });
        Box hb7=Box.createHorizontalBox();
        dbt=new JButton("所有专业情况");
        dbt.addActionListener(e->{
            con.getconnection();
            connect.dtable("","");
        });
        qdbt=new JButton("专业情况查询");
        qdbt.addActionListener(e->{
            new query_d();
        });

        hb6.add(cbt);
        hb6.add(Box.createHorizontalStrut(20));
        hb6.add(qcbt1);

        hb7.add(dbt);
        hb7.add(Box.createHorizontalStrut(20));
        hb7.add(qdbt);

        Box vb=Box.createVerticalBox();
        vb.add(Box.createVerticalStrut(75));
        vb.add(hb4);
        vb.add(Box.createVerticalStrut(100));
        vb.add(hb1);
        vb.add(Box.createVerticalStrut(20));
        vb.add(hb3);
        vb.add(Box.createVerticalStrut(20));
        vb.add(hb5);
        vb.add(Box.createVerticalStrut(20));
        vb.add(hb6);
        vb.add(Box.createVerticalStrut(20));
        vb.add(hb7);

        pl.add(vb);
        jf.setContentPane(pl);
        jf.setSize(700,500);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        jf.setVisible(true);
    }
}
