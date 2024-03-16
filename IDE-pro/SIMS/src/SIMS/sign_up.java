package SIMS;

import javax.swing.*;
import java.awt.*;

public class sign_up {
    public sign_up(){
        JFrame jf=new JFrame("登入");
        JPanel jp=new JPanel(new FlowLayout(FlowLayout.CENTER));
        JLabel jl=new JLabel("密码:");
        jl.setFont(new Font("宋体",Font.PLAIN,20));
        JPasswordField pass=new JPasswordField();
        pass.setEchoChar('*');
        pass.setFont(new Font("宋体",Font.PLAIN,20));
        pass.setPreferredSize(new Dimension(200,20));
        JButton jb=new JButton("确认");
        jb.addActionListener(e->{
            String pa=new String(pass.getPassword());
            String spa="123456";
            if(pa.equals(spa)){
                new Educational();
                jf.dispose();
            }else{
                JOptionPane.showMessageDialog(
                        jf,
                        "密码错误！",
                        "提示",
                        JOptionPane.WARNING_MESSAGE
                );
                pass.setText(null);
            }
        });
        Box hb=Box.createHorizontalBox();
        hb.add(jl);
        hb.add(pass);
        hb.add(Box.createHorizontalStrut(20));
        hb.add(jb);

        Box vb=Box.createVerticalBox();
        vb.add(Box.createVerticalStrut(50));
        vb.add(hb);
        jp.add(vb);

        jf.setContentPane(jp);
        jf.setSize(400,200);
        jf.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        jf.setLocationRelativeTo(null);
        jf.setResizable(false);
        jf.setVisible(true);
    }
}
