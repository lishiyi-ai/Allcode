package SIMS;

import javax.swing.*;
import java.awt.*;

public class main_interface {
    final JFrame jf=new JFrame("学生信息管理系统");//窗口

    final JButton abt,dbt,qbt,qbtall;//按钮
    public main_interface(){
        //窗口设置
        jf.setSize(800,600);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        //布局设置
        JPanel panel=new JPanel(new FlowLayout());
        connect con=new connect();
        JPanel cpanel=connect.table();
        //按钮设置
        abt=new JButton("添加学生记录");
        abt.addActionListener(e -> new student_message_input());
        dbt=new JButton("删除学生记录");
        dbt.addActionListener(e -> {
            con.getconnection();
            new delete();
        });
        qbt=new JButton("查询学生记录");
        qbt.addActionListener(e -> {
            con.getconnection();
            new query();
        });
        qbtall=new JButton("查询所有记录");
        qbtall.addActionListener(e -> {
            con.getconnection();
            connect.queryData("","","","","","","");
        });
        //按钮布局第一行
        Box hb=Box.createHorizontalBox();
        hb.add(abt);
        hb.add(Box.createHorizontalStrut(20));
        hb.add(dbt);
        hb.add(Box.createHorizontalStrut(20));
        hb.add(qbt);
        hb.add(Box.createHorizontalStrut(20));
        hb.add(qbtall);
        //教务
        JButton ejb=new JButton("教务信息输入");
        ejb.addActionListener(e-> new sign_up());
        Box hb1=Box.createHorizontalBox();
        hb1.add(ejb);
        //整体布局
        Box vb=Box.createVerticalBox();
        vb.add(cpanel);
        vb.add(hb);
        vb.add(Box.createVerticalStrut(20));
        vb.add(hb1);
        panel.add(vb);
        //窗口可见
        jf.setContentPane(panel);
        jf.setVisible(true);
    }
    public static void main(String[] arg) {
        new main_interface();
    }
}
