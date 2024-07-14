package SIMS;
import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Change_of_student_status {
    final private JTextField  C_id1,Sid1,Ch1,Cdes1;
    final private JLabel C_id,Sid,Ch,Cdes;
    final private JButton bt;
    public Change_of_student_status(){
        //窗口设置
        JFrame jf=new JFrame();
        jf.setTitle("学籍变更输入");
        jf.setSize(400,400);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

        Font ft=new Font("宋体",Font.PLAIN,20);

        this.C_id=new JLabel("变更记录号：");
        this.C_id1=new JTextField(20);
        Box hb1=Box.createHorizontalBox();
        C_id.setFont(ft);
        C_id1.setFont(ft);
        hb1.add(C_id);
        hb1.add(C_id1);

        this.Sid=new JLabel("学    号：");
        this.Sid1=new JTextField(20);
        Box hb2=Box.createHorizontalBox();
        Sid.setFont(ft);
        Sid1.setFont(ft);
        hb2.add(Sid);
        hb2.add(Sid1);

        this.Ch=new JLabel("变更代码：");
        this.Ch1=new JTextField(20);
        Box hb3=Box.createHorizontalBox();
        Ch.setFont(ft);
        Ch1.setFont(ft);
        hb3.add(Ch);
        hb3.add(Ch1);

        this.Cdes=new JLabel("描    述：");
        this.Cdes1=new JTextField(20);
        Cdes.setFont(ft);
        Cdes1.setFont(ft);
        Box hb7=Box.createHorizontalBox();
        hb7.add(Cdes);
        hb7.add(Cdes1);

        bt=new JButton("确认");
        Box hb8=Box.createVerticalBox();
        hb8.add(Box.createHorizontalStrut(210));
        hb8.add(bt);
        bt.addActionListener(e -> {
            String id=C_id1.getText();
            String sid=Sid1.getText();
            String ch=Ch1.getText();
            String des=Cdes1.getText();
            if(id.equals("")){
                JOptionPane.showMessageDialog(jf,
                        "奖励记录号不能为空",
                        "警告",
                        JOptionPane.WARNING_MESSAGE);
            }else if(sid.equals("")){
                JOptionPane.showMessageDialog(jf,
                        "学号不能为空",
                        "警告",
                        JOptionPane.WARNING_MESSAGE);
            }else if(ch.equals("")){
                JOptionPane.showMessageDialog(jf,
                        "变更等级不能为空",
                        "警告",
                        JOptionPane.WARNING_MESSAGE);
            }else if(des.equals("")){
                JOptionPane.showMessageDialog(jf,
                        "描述不能为空",
                        "警告",
                        JOptionPane.WARNING_MESSAGE);
            }else {
                connect con = new connect();
                Connection co = con.getconnection();
                Statement stmt = null;
                try {
                    stmt = co.createStatement();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                ResultSet rs;
                boolean flag=true;
                try {
                    String sql = "SELECT * FROM changes WHERE C_id='" + id + "'";
                    assert stmt != null;
                    rs=stmt.executeQuery(sql);
                    flag=rs.next();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                ResultSet rs1;
                boolean flag1=true;
                try {
                    String sql = "SELECT * FROM student WHERE Sid='" + sid + "'";
                    rs1=stmt.executeQuery(sql);
                    flag1=rs1.next();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                ResultSet rs2;
                boolean flag2=true;
                try {
                    String sql = "SELECT * FROM change_code WHERE code='" + ch + "'";
                    rs2 = stmt.executeQuery(sql);
                    flag2=rs2.next();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                if(!flag) {
                    if (flag1) {
                        if (flag2) {
                            try {
                                String sql = "INSERT INTO changes VALUE('" + id + "','" + sid + "','" + ch + "',now(),'" + des + "')";
                                stmt.executeUpdate(sql);
                                C_id1.setText(null);
                                Sid1.setText(null);
                                Ch1.setText(null);
                                Cdes1.setText(null);
                            } catch (SQLException ex) {
                                ex.printStackTrace();
                            }
                        } else {
                            JOptionPane.showMessageDialog(jf,
                                    "0转系，1休学，2复学，3退学，4毕业",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                        }
                    } else {
                        JOptionPane.showMessageDialog(jf,
                                "该学号不存在",
                                "警告",
                                JOptionPane.WARNING_MESSAGE);
                    }
                }else{
                    JOptionPane.showMessageDialog(jf,
                            "记录号已存在",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                }
            }
        });
        //组件设置
        JPanel vb1 = new JPanel(new FlowLayout(FlowLayout.CENTER));
        Box vb=Box.createVerticalBox();
        vb.add(hb1);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb2);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb3);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb7);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb8);
        vb1.add(vb);
        jf.setContentPane(vb1);
        jf.setVisible(true);
    }
}