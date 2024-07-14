package SIMS;
import javax.swing.*;
import java.awt.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class query {
    final private JLabel name,id,sex,sc,dept,birth,place;
    final private JTextField name1,id1,sex1,sc1,dept1,birth1,place1;
    final private JButton submit;
    final private JFrame jf=new JFrame();
    public query(){

        jf.setTitle("查询信息输入");
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
        submit.addActionListener(e -> {
            String name=name1.getText();
            String id=id1.getText();
            String sex=sex1.getText();
            String sc=sc1.getText();
            String dept=dept1.getText();
            String birth=birth1.getText();
            String place=place1.getText();

            if(id.equals(" ")){id="";}
            if(name.equals(" ")){name="";}
            if(sex.equals(" ")){sex="";}
            if(sc.equals(" ")){sc="";}
            if(dept.equals(" ")){dept="";}
            if(birth.equals(" ")){birth="";}
            if(place.equals(" ")){place="";}
            if(birth.equals("")||date(birth)||(birth.length()==4)||(birth.length()==2)) {
                connect.queryData(id, name, sex, sc, dept, birth, place);
            }else{
                JOptionPane.showMessageDialog(
                        jf,
                        "日期格式为YYYY-MM-DD或YYYY或MM或DD",
                        "警告",
                        JOptionPane.WARNING_MESSAGE
                );
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
        Date date;
        try {
            // 转化为 Date类型测试判断
            date = dateFormat.parse(rawDateStr);
            return rawDateStr.equals(dateFormat.format(date));
        } catch (ParseException e) {
            return false;
        }
    }
}
