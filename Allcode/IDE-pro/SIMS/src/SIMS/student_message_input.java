package SIMS;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

//import SIMS.connect;
public class student_message_input {
    final private JLabel name,id,sex,sc,dept,birth,place;
    final private JTextField name1,id1,sex1,sc1,dept1,birth1,place1;
    final private JButton submit;
    final private JFrame jf=new JFrame();
    public student_message_input(){

        jf.setTitle("学生信息输入");
        jf.setSize(400,400);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

        Font ft=new Font("宋体",Font.PLAIN,20);

        this.id=new JLabel("学    号：");
        this.id1=new JTextField(20);
        Box hb1=Box.createHorizontalBox();
        id.setFont(ft);
        id1.setFont(ft);
        hb1.add(id);
        hb1.add(id1);

        this.name=new JLabel("姓    名：");
        this.name1=new JTextField(20);
        Box hb2=Box.createHorizontalBox();
        name.setFont(ft);
        name1.setFont(ft);
        hb2.add(name);
        hb2.add(name1);

        this.sex=new JLabel("性别(M/F):");
        this.sex1=new JTextField(20);
        Box hb3=Box.createHorizontalBox();
        sex.setFont(ft);
        sex1.setFont(ft);
        hb3.add(sex);
        hb3.add(sex1);

        this.sc=new JLabel("班级编号：");
        this.sc1=new JTextField(20);
        sc.setFont(ft);
        sc1.setFont(ft);
        Box hb4=Box.createHorizontalBox();
        hb4.add(sc);
        hb4.add(Box.createHorizontalStrut(2));
        hb4.add(sc1);

        this.dept=new JLabel("院系编号：");
        this.dept1=new JTextField(20);
        Box hb5=Box.createHorizontalBox();
        dept.setFont(ft);
        dept1.setFont(ft);
        hb5.add(dept);
        hb5.add(Box.createHorizontalStrut(2));
        hb5.add(dept1);

        this.birth=new JLabel("生    日：");
        this.birth1=new JTextField(20);
        Box hb6=Box.createHorizontalBox();
        birth.setFont(ft);
        birth1.setFont(ft);
        hb6.add(birth);
        hb6.add(birth1);

        this.place=new JLabel("籍    贯：");
        this.place1=new JTextField(20);
        place.setFont(ft);
        place1.setFont(ft);
        Box hb7=Box.createHorizontalBox();
        hb7.add(place);
        hb7.add(place1);

        submit=new JButton("确认");
        Box hb8=Box.createVerticalBox();
        hb8.add(Box.createHorizontalStrut(210));
        hb8.add(submit);
        submit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name=name1.getText();
                String id=id1.getText();
                String sex=sex1.getText();
                String sc=sc1.getText();
                String dept=dept1.getText();
                String birth=birth1.getText();
                String place=place1.getText();

                connect o=new connect();
                Connection con=o.getconnection();
                Statement stmt = null;
                try {
                    stmt = con.createStatement();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                String sql = "select * from class where Cid='"+sc+"'";
                ResultSet rs=null;
                boolean flag1=true;
                try {
                    rs = stmt.executeQuery(sql);
                    flag1=rs.next();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                String sql1="select * from department where Did='"+dept+"'";
                ResultSet rs1=null;
                boolean flag2=true;
                try {
                    rs1 = stmt.executeQuery(sql1);
                    flag2=rs1.next();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                String sql2="select * from student where Sid='"+id+"'";
                ResultSet rs2=null;
                boolean flag3=false;
                try {
                    rs2 = stmt.executeQuery(sql2);
                    flag3=rs2.next();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
                System.out.println(flag1+" "+flag2+" "+flag3);

                boolean flag=true;
                if(id.equals("")){
                    JOptionPane.showMessageDialog(jf,
                            "学号不能为空",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    id1.setText(null);
                }else if(flag3){
                    JOptionPane.showMessageDialog(jf,
                            "学号已存在",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    id1.setText(null);
                }else if(name.equals("")||name.length()>5){
                    JOptionPane.showMessageDialog(jf,
                            "姓名不能为空且不能长于五个字",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    name1.setText(null);
                }else if((!sex.equals("M"))&&(!sex.equals("F"))){
                    System.out.println(sex.equals("M")+" "+sex.equals("F"));
                    JOptionPane.showMessageDialog(jf,
                            "性别输入错误，男生为M女生为F",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    sex1.setText(null);
                }else if(sc.equals("")){
                    JOptionPane.showMessageDialog(jf,
                            "班级编号不能为空",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    sc1.setText(null);
                }else if(!flag1){
                    JOptionPane.showMessageDialog(jf,
                            "班级不存在",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    sc1.setText(null);
                }else if(dept.equals("")){
                    JOptionPane.showMessageDialog(jf,
                            "院系编号不能为空",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    dept1.setText(null);
                }else if(!flag2){
                    JOptionPane.showMessageDialog(jf,
                            "专业不存在",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    dept1.setText(null);
                }else if(!date(birth)){
                    JOptionPane.showMessageDialog(jf,
                            "生日时间不正确或格式错误，格式为yyyy-mm-dd",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    birth1.setText(null);
                }else if(place.equals("")||place.length()>50){
                    JOptionPane.showMessageDialog(jf,
                            "籍贯不能为空且小于50字",
                            "警告",
                            JOptionPane.WARNING_MESSAGE);
                    flag=false;
                    place1.setText(null);
                }
                if(flag) {
                    connect c=new connect();
                    c.getconnection();
                    c.addData(id,name,sex,sc,dept,birth,place);
                    JOptionPane.showMessageDialog(jf,
                            "添加成功",
                            "确认",
                            JOptionPane.PLAIN_MESSAGE
                    );
                    name1.setText(null);
                    id1.setText(null);
                    sex1.setText(null);
                    sc1.setText(null);
                    dept1.setText(null);
                    birth1.setText(null);
                    place1.setText(null);

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
        vb.add(hb4);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb5);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb6);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb7);
        vb.add(Box.createVerticalStrut(5));
        vb.add(hb8);
        vb1.add(vb);
        jf.setContentPane(vb1);
        jf.setVisible(true);
    }
    public static boolean date(String rawDateStr) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        Date date = null;
        try {
            // 转化为 Date类型测试判断
            date = dateFormat.parse(rawDateStr);
            return rawDateStr.equals(dateFormat.format(date));
        } catch (ParseException e) {
            return false;
        }

    }
}
