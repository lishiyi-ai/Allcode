package SIMS;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Reward_situation {

    private final JButton bt;
    private final JTextField id1;
    private final JTextField sid1;
    private final JTextField level1;
    private final JTextField des1;
    private final JLabel id;
    private final JLabel sid;
    private final JLabel level;
    private final JLabel des;

    public Reward_situation(){
        JFrame jf=new JFrame();
        jf.setTitle("奖励情况输入");
        jf.setSize(400,400);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

        Font ft=new Font("宋体",Font.PLAIN,20);

        this.id=new JLabel("奖励记录号：");
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

        this.level=new JLabel("奖励等级：");
        this.level1=new JTextField(20);
        Box hb3=Box.createHorizontalBox();
        level.setFont(ft);
        level1.setFont(ft);
        hb3.add(level);
        hb3.add(Box.createHorizontalStrut(2));
        hb3.add(level1);

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
                String des=des1.getText();
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
                }else if(level.equals("")){
                    JOptionPane.showMessageDialog(jf,
                            "奖励等级不能为空",
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
                        String sql = "SELECT * FROM reward WHERE Rid='" + id + "'";
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
                        String sql = "SELECT * FROM reward_level WHERE code='" + level + "'";
                        rs2 = stmt.executeQuery(sql);
                        flag2=rs2.next();
                    } catch (SQLException ex) {
                        ex.printStackTrace();
                    }
                    if(!flag) {
                        if (flag1) {
                            if (flag2) {
                                try {
                                    String sql = "INSERT INTO reward VALUE('" + id + "','" + sid + "','" + level + "',now(),'" + des + "')";
                                    stmt.executeUpdate(sql);
                                    id1.setText(null);
                                    sid1.setText(null);
                                    level1.setText(null);
                                    des1.setText(null);
                                } catch (SQLException ex) {
                                    ex.printStackTrace();
                                }
                            } else {
                                JOptionPane.showMessageDialog(jf,
                                        "0校特等，1校一等，2校二等，3校三等，4系一等,5系二等,6系三等",
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
            }
        });
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
