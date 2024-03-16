package SIMS;

import javax.swing.*;
import javax.swing.event.TableModelEvent;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableRowSorter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.sql.ResultSet;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
public class connect {
    private static Connection con=null;//连接数据库
    private static Statement stmt=null;//获取连接对象

    public Connection getconnection(){
        //连接设置
        String url="jdbc:mysql://localhost:3306/sims";
        String user="root";
        String password="123456";
        //驱动加载
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            System.out.println("驱动加载成功");
        }catch (ClassNotFoundException e){
            System.out.println("驱动加载失败");
            e.printStackTrace();
        }
        //数据库连接
        try {
            con = DriverManager.getConnection(url, user, password);
            System.out.println("数据库连接成功");
        } catch (SQLException e) {
            e.printStackTrace();
            System.out.println("数据库连接失败");
        }
        try {
            stmt=con.createStatement();
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
        return con;
    }
    public static void rtable(String rid,String sid,String rl,String rt,String rdes){
        //r窗口设置
        JFrame cpj=new JFrame("奖励情况");
        JPanel cppa=new JPanel(new BorderLayout());
        //表格设置
        Object[] name={"奖励记录号","学号","奖励情况","时间","具体描述"};
        Object[][] row=new Object[1000][5];
        //连接进行操作
        try {
            stmt = con.createStatement();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        String sql="select reward.Rid, Sid,reward_level.Cdes, Rtime, Rdes " +
                "from reward LEFT JOIN reward_level ON reward.Rlevel = reward_level.code";
        if((!rid.equals(""))||(!sid.equals(""))||(!rl.equals(""))||(!rt.equals(""))||(!rdes.equals(""))){
            sql=sql+" WHERE";
            if((!rid.equals(""))){sql+=" Rid LIKE'"+rid+"' AND";}
            if((!sid.equals(""))){sql+=" Sid LIKE'"+sid+"' AND";}
            if((!rl.equals(""))){sql+=" Rlevel LIKE'"+rl+"' AND";}
            if((!rt.equals(""))){sql+=" Rtime LIKE'%"+rt+"%' AND";}
            if((!rdes.equals(""))){sql+=" Rdes LIKE'"+rdes+"' AND";}
            sql=sql.substring(0,sql.length()-3);
        }
        final int[] i = {0};
        try {
            ResultSet rs=stmt.executeQuery(sql);
            while(rs.next()){
                String a = rs.getString(1);
                String b = rs.getString(2);
                String c = rs.getString(3);
                String d = rs.getString(4);
                String e1 = rs.getString(5);
                Object[] rowdate={a,b,c,d,e1};
                System.arraycopy(rowdate, 0,row[i[0]], 0, 5);
                i[0]++;
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        //表格模式以及表格创建
        DefaultTableModel tableModel=new DefaultTableModel(row,name);
        tableModel.setNumRows(i[0]);
        JTable table = new JTable(tableModel);
        final int[] m = {-1};
        tableModel.addTableModelListener(e -> {
            int type=e.getType();
            if(type==TableModelEvent.DELETE){
                for(int h = m[0] +1; h< i[0]; h++){
                    System.arraycopy(row[h], 0, row[h-1], 0, 5);
                    System.out.println(Arrays.toString(row[h-1]));
                }
                for(int h=0;h<5;h++){row[i[0]-1][h]=null;}
                i[0]--;
                System.out.println("删除第"+(i[0]+1)+"行");
            }else if(type==TableModelEvent.UPDATE) {
                int column = e.getColumn();
                int firstRow = e.getFirstRow();
                Object id = row[firstRow][0];
                if (id == null && column != 0) {
                    Object new1 = tableModel.getValueAt(firstRow, column);
                    if (!(new1 == null)) {
                        JOptionPane.showMessageDialog(
                                cpj,
                                "记录号不能为空！",
                                "警告",
                                JOptionPane.WARNING_MESSAGE
                        );
                        tableModel.setValueAt(row[firstRow][column], firstRow, column);
                    }
                } else {
                    Object new1;
                    if (column == 0) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String sql2 = "select * from reward where Rid='" + new1 + "'";
                        ResultSet rs2;
                        boolean flag = false;
                        try {
                            rs2 = stmt.executeQuery(sql2);
                            flag = rs2.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if (!(row[firstRow][column] == null)) {
                            if (!(new1 == row[firstRow][column])) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "记录号不能修改",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else if (flag || new1 == null) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "记录号已存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql10 = "insert into reward value('" + new1 + "',null,null,null,null)";
                                stmt.executeUpdate(sql10);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 1) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                String sql1 = "UPDATE reward set Sid='" + new1 + "'"
                                        + " WHERE Rid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql1);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "学号不存在",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                        }
                    } else if (column == 2) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if ((!da.equals("1")) && (!da.equals("2")) && (!da.equals("0")) && (!da.equals("3")) && (!da.equals("4")) && (!da.equals("5")) && (!da.equals("6"))) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "奖励等级为0-6，0校特等，1校一等，2校二等，3校三等，4系一等，5系二等，6系三等",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql2 = "UPDATE reward set Rlevel='" + new1 + "'"
                                        + " WHERE Rid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql2);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 3) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if (!date(da)) {
                            if ((!(new1 == null))) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "日期不正确或格式错误，格式为yyyy-mm-dd",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql5 = "UPDATE reward set Rtime='" + new1 + "'"
                                        + " WHERE Rid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql5);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 4) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                String sql6 = "UPDATE reward set Rdes='" + new1 + "'"
                                        + " WHERE Rid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql6);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "描述不能为空且小于50字",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            //ex.printStackTrace();
                        }
                    }
                }
            }else if(type == TableModelEvent.INSERT){
                    System.out.println("添加成功第"+i[0]+"行");
            }
        });
        // 设置滚动面板视口大小（超过该大小的行数据，需要拖动滚动条才能看到）
        table.setPreferredScrollableViewportSize(new Dimension(400, 300));

        // 把 表格 放到 滚动面板 中（表头将自动添加到滚动面板顶部）
        JScrollPane scrollPane = new JScrollPane(table);

        cppa.add(table.getTableHeader(),BorderLayout.NORTH);
        cppa.add(scrollPane,BorderLayout.CENTER);

        //删除开关
        JButton jb=new JButton("删除");
        jb.addActionListener(e -> {
            int result=JOptionPane.showConfirmDialog(
                    cpj,
                    "确认删除？",
                    "提示",
                    JOptionPane.YES_NO_OPTION
            );
            //System.out.println(result);
            if(result==0){
                int[] selectedRows = table.getSelectedRows();
                for (int selectedRow : selectedRows) {
                    // 从表格模型中移除表格中的选中行
                    Object id = table.getValueAt(selectedRow, 0);
                    System.out.println(id);
                    if (id != null) {
                        //System.out.println(id);
                        String sql1 = "DELETE  FROM reward WHERE Rid='" + id + "'";
                        try {
                            stmt.executeUpdate(sql1);
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        System.out.println("删除已完成");
                    }
                    for(int h = 0; h< i[0]; h++){
                        System.out.println(h);
                        if(id==row[h][0]){
                            m[0] = h;
                            tableModel.removeRow(m[0]);
                            break;
                        }
                    }
                }
            }
        });
        //添加开关
        JButton ajb=new JButton("添加");
        ajb.addActionListener(e -> {
            Object[] row1=new Object[5];
            tableModel.addRow(row1);
            i[0]++;
        });
        //按钮布局设置
        Box hb=Box.createHorizontalBox();
        hb.add(ajb);
        hb.add(jb);

        Box vb=Box.createVerticalBox();
        vb.add(cppa);
        vb.add(hb);
        JPanel jp=new JPanel(new FlowLayout());
        jp.add(vb);

        cpj.setContentPane(vb);
        cpj.setSize(400,400);
        cpj.setLocationRelativeTo(null);
        cpj.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        cpj.setVisible(true);
    }
    public static void ptable(String pid,String sid,String pl,String pt,String pa,String pdes){
        JFrame cpj=new JFrame("处罚情况");
        JPanel cppa=new JPanel(new BorderLayout());
        Object[] name={"处罚记录号","学号","处罚情况","时间","是否生效","具体描述"};
        Object[][] row=new Object[1000][6];
        try {
            stmt = con.createStatement();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        String sql="select punishment.Pid, Sid, punish_level.Cdes, Ptime, Penable, Pdes "+ "from punishment LEFT JOIN punish_level on punishment.Plevel =punish_level.code ";
        if((!pid.equals(""))||(!sid.equals(""))||(!pl.equals(""))||(!pt.equals(""))||(!(pa.equals("")))||(!pdes.equals(""))){
            sql=sql+"WHERE ";
            if((!pid.equals(""))){sql+=" Pid LIKE'"+pid+"' AND";}
            if((!sid.equals(""))){sql+=" Sid LIKE'"+sid+"' AND";}
            if((!pl.equals(""))){sql+=" Plevel LIKE'"+pl+"' AND";}
            if((!pt.equals(""))){sql+=" Ptime LIKE'%"+pt+"%' AND";}
            if((!pa.equals(""))){sql+=" Penable LIKE'%"+pa+"%' AND";}
            if((!pdes.equals(""))){sql+=" Pdes LIKE'"+pdes+"' AND";}
            sql=sql.substring(0,sql.length()-3);
        }
        final int[] i={0};
        try {
            ResultSet rs=stmt.executeQuery(sql);
            while(rs.next()){
                System.out.println("yes");
                String a = rs.getString(1);
                String b = rs.getString(2);
                String c = rs.getString(3);
                String d = rs.getString(4);
                String e1 = rs.getString(5);
                String f = rs.getString(6);
                Object[] rowdate={a,b,c,d,e1,f};
                System.arraycopy(rowdate, 0,row[i[0]], 0, 6);
                i[0]++;
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        final int[] m = {-1};
        DefaultTableModel tableModel=new DefaultTableModel(row,name);
        tableModel.setNumRows(i[0]);
        JTable table = new JTable(tableModel);

        tableModel.addTableModelListener(e -> {
            int type=e.getType();
            if(type==TableModelEvent.DELETE){
                for(int h = m[0] +1; h< i[0]; h++){
                    System.arraycopy(row[h], 0, row[h-1], 0, 6);
                    System.out.println(Arrays.toString(row[h-1]));
                }
                for(int h=0;h<6;h++){row[i[0]-1][h]=null;}
                i[0]--;
                System.out.println("删除第"+(i[0]+1)+"行");
            }else if(type==TableModelEvent.UPDATE) {
                int column = e.getColumn();
                int firstRow = e.getFirstRow();
                Object id = row[firstRow][0];
                if (id == null && column != 0) {
                    Object new1 = tableModel.getValueAt(firstRow, column);
                    if (!(new1 == null)) {
                        JOptionPane.showMessageDialog(
                                cpj,
                                "记录号不能为空！",
                                "警告",
                                JOptionPane.WARNING_MESSAGE
                        );
                        tableModel.setValueAt(row[firstRow][column], firstRow, column);
                    }
                } else {
                    Object new1;
                    if (column == 0) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String sql2 = "select * from punishment where Pid='" + new1 + "'";
                        ResultSet rs2;
                        boolean flag = false;
                        try {
                            rs2 = stmt.executeQuery(sql2);
                            flag = rs2.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if (!(row[firstRow][column] == null)) {
                            if (!(new1 == row[firstRow][column])) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "记录号不能修改",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else if (flag || new1 == null) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "记录号已存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            if(new1=="") new1=null;
                            try {
                                String sql10 = "insert into punishment value('" + new1 + "',null,null,null,null,null)";
                                stmt.executeUpdate(sql10);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 1) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                //System.out.println(new1);
                                String sql1 = "UPDATE punishment set Sid='" + new1 + "'"
                                        + " WHERE Pid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql1);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "学号不存在",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    } else if (column == 2) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if ((!da.equals("1")) && (!da.equals("2")) && (!da.equals("0")) && (!da.equals("3")) && (!da.equals("4"))) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "处罚等级为0-4，0警告，1严重警告，2记过，3记大过，4开除",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql2 = "UPDATE punishment set Plevel='" + new1 + "'"
                                        + " WHERE Pid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql2);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 3) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if (!date(da)) {
                            if ((!(new1 == null))) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "日期不正确或格式错误，格式为yyyy-mm-dd",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql5 = "UPDATE punishment set Ptime='" + new1 + "'"
                                        + " WHERE Pid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql5);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if(column==4){
                        new1 = tableModel.getValueAt(firstRow,column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if ((!da.equals("T")) && (!da.equals("F"))) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "生效为T或F",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql2 = "UPDATE punishment set Penable='" + new1 + "'"
                                        + " WHERE Pid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql2);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 5) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                String sql6 = "UPDATE punishment set Pdes='" + new1 + "'"
                                        + " WHERE Pid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql6);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "描述不能为空且小于50字",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    }
                }
            }else if(type == TableModelEvent.INSERT){
                System.out.println("添加成功第"+i[0]+"行");
            }
        });

        JScrollPane scrollPane = new JScrollPane(table);
        cppa.add(table.getTableHeader(),BorderLayout.NORTH);
        cppa.add(scrollPane,BorderLayout.CENTER);

        JButton jb=new JButton("删除");
        jb.addActionListener(e -> {
            int result=JOptionPane.showConfirmDialog(
                    cpj,
                    "确认删除？",
                    "提示",
                    JOptionPane.YES_NO_OPTION
            );
            if(result==0){
                int[] selectedRows = table.getSelectedRows();
                for (int selectedRow : selectedRows) {
                    // 从表格模型中移除表格中的选中行
                    Object id = table.getValueAt(selectedRow, 0);
                    if (id != null) {
                        //System.out.println(id);
                        String sql1 = "DELETE  FROM punishment WHERE Pid='" + id + "'";
                        try {
                            stmt.executeUpdate(sql1);
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        System.out.println("删除已完成");
                    }
                    for(int h = 0; h< i[0]; h++){
                        System.out.println(h);
                        if(id==row[h][0]){
                            m[0] = h;
                            tableModel.removeRow(m[0]);
                            break;
                        }
                    }
                }
            }
        });
        //添加开关
        JButton ajb=new JButton("添加");
        ajb.addActionListener(e -> {
            Object[] row1=new Object[5];
            tableModel.addRow(row1);
            i[0]++;
        });

        Box hb=Box.createHorizontalBox();
        hb.add(ajb);
        hb.add(jb);

        Box vb=Box.createVerticalBox();
        vb.add(cppa);
        vb.add(hb);
        JPanel jp=new JPanel(new FlowLayout());
        jp.add(vb);

        cpj.setContentPane(vb);
        cpj.setSize(400,400);
        cpj.setLocationRelativeTo(null);
        cpj.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        cpj.setVisible(true);
    }
    public static void chtable(String cid,String sid,String ch,String ct,String cdes){
        JFrame cpj=new JFrame("学籍变更情况");
        JPanel cppa=new JPanel(new BorderLayout());
        Object[] name={"变更记录号","学号","变更情况","时间","具体描述"};
        Object[][] row=new Object[1000][5];
        try {
            stmt = con.createStatement();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        String sql="select changes.C_id,Sid,change_code.Cdes, Ctime, changes.Cdes " +
                "from changes LEFT JOIN change_code on changes.Ch = change_code.code ";//,change_code " +
        if((!cid.equals(""))||(!sid.equals(""))||(!ch.equals(""))||(!ct.equals(""))||(!cdes.equals(""))){
            sql=sql+"WHERE ";
            if((!cid.equals(""))){sql+=" C_id LIKE'"+cid+"' AND";}
            if((!sid.equals(""))){sql+=" Sid LIKE'"+sid+"' AND";}
            if((!ch.equals(""))){sql+=" Ch LIKE'"+ch+"' AND";}
            if((!ct.equals(""))){sql+=" Ctime LIKE'%"+ct+"%' AND";}
            if((!cdes.equals(""))){sql+=" Cdes LIKE'"+cdes+"' AND";}
            sql=sql.substring(0,sql.length()-3);
        }
        final int[] i={0};
        try {
            ResultSet rs=stmt.executeQuery(sql);
            while(rs.next()){
                String a = rs.getString(1);
                String b = rs.getString(2);
                String c = rs.getString(3);
                String d = rs.getString(4);
                String e1 = rs.getString(5);
                Object[] rowdate={a,b,c,d,e1};
                System.arraycopy(rowdate, 0,row[i[0]], 0, 5);
                i[0]++;
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        final int[] m = {-1};
        DefaultTableModel tableModel=new DefaultTableModel(row,name);
        tableModel.setNumRows(i[0]);
        JTable table = new JTable(tableModel);

        tableModel.addTableModelListener(e -> {
            int type=e.getType();
            if(type==TableModelEvent.DELETE){
                for(int h = m[0] +1; h< i[0]; h++){
                    System.arraycopy(row[h], 0, row[h-1], 0, 5);
                    System.out.println(Arrays.toString(row[h-1]));
                }
                for(int h=0;h<5;h++){row[i[0]-1][h]=null;}
                i[0]--;
                System.out.println("删除第"+(i[0]+1)+"行");
            }else if(type==TableModelEvent.UPDATE) {
                int column = e.getColumn();
                int firstRow = e.getFirstRow();
                Object id = row[firstRow][0];
                if (id == null && column != 0) {
                    Object new1 = tableModel.getValueAt(firstRow, column);
                    if (!(new1 == null)) {
                        JOptionPane.showMessageDialog(
                                cpj,
                                "记录号不能为空！",
                                "警告",
                                JOptionPane.WARNING_MESSAGE
                        );
                        tableModel.setValueAt(row[firstRow][column], firstRow, column);
                    }
                } else {
                    Object new1;
                    if (column == 0) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String sql2 = "select * from changes where C_id='" + new1 + "'";
                        ResultSet rs2;
                        boolean flag = false;
                        try {
                            rs2 = stmt.executeQuery(sql2);
                            flag = rs2.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if (!(row[firstRow][column] == null)) {
                            if (!(new1 == row[firstRow][column])) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "记录号不能修改",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else if (flag || new1 == null) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "记录号已存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql10 = "insert into changes value('" + new1 + "',null,null,null,null)";
                                stmt.executeUpdate(sql10);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][0] ,firstRow,0);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 1) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                //System.out.println(new1);
                                String sql1 = "UPDATE changes set Sid='" + new1 + "'"
                                        + " WHERE C_id='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql1);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "学号不存在",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    } else if (column == 2) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if ((!da.equals("1")) && (!da.equals("2")) && (!da.equals("0")) && (!da.equals("3")) && (!da.equals("4"))) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "学籍变成等级为0-4，0转系，1休学，2复学，3退学，4毕业",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql2 = "UPDATE changes set Ch='" + new1 + "'"
                                        + " WHERE C_id='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql2);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 3) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String da = (String) new1;
                        if (new1 == null) da = "";
                        if (!date(da)) {
                            if ((!(new1 == null))) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "日期不正确或格式错误，格式为yyyy-mm-dd",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql5 = "UPDATE changes set Ctime='" + new1 + "'"
                                        + " WHERE C_id='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql5);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 4) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                String sql6 = "UPDATE changes set Cdes='" + new1 + "'"
                                        + " WHERE C_id='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql6);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "描述不能为空且小于50字",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    }
                }
            }else if(type == TableModelEvent.INSERT){
                System.out.println("添加成功第"+i[0]+"行");
            }
        });

        JScrollPane scrollPane = new JScrollPane(table);
        cppa.add(table.getTableHeader(),BorderLayout.NORTH);
        cppa.add(scrollPane,BorderLayout.CENTER);

        JButton jb=new JButton("删除");
        jb.addActionListener(e -> {
            int result=JOptionPane.showConfirmDialog(
                    cpj,
                    "确认删除？",
                    "提示",
                    JOptionPane.YES_NO_OPTION
            );
            //System.out.println(result);
            if(result==0){
                int[] selectedRows = table.getSelectedRows();
                for (int selectedRow : selectedRows) {
                    // 从表格模型中移除表格中的选中行
                    Object id = table.getValueAt(selectedRow, 0);
                    if (id != null) {
                        //System.out.println(id);
                        String sql1 = "DELETE  FROM changes WHERE C_id='" + id + "'";
                        try {
                            stmt.executeUpdate(sql1);
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        System.out.println("删除已完成");
                    }
                    for(int h = 0; h< i[0]; h++){
                        //System.out.println(h);
                        if(id==row[h][0]){
                            m[0] = h;
                            tableModel.removeRow(m[0]);
                            break;
                        }
                    }
                }
            }
        });
        JButton ajb=new JButton("添加");
        ajb.addActionListener(e -> {
            Object[] row1=new Object[5];
            tableModel.addRow(row1);
            i[0]++;
        });
        Box hb=Box.createHorizontalBox();
        hb.add(ajb);
        hb.add(jb);

        Box vb=Box.createVerticalBox();
        vb.add(cppa);
        vb.add(hb);
        JPanel jp=new JPanel(new FlowLayout());
        jp.add(vb);

        cpj.setContentPane(vb);
        cpj.setSize(400,400);
        cpj.setLocationRelativeTo(null);
        cpj.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        cpj.setVisible(true);
    }
    public static void ctable(String id,String cname,String mo){
        JFrame cpj=new JFrame("所有班级情况");
        JPanel cppa=new JPanel(new BorderLayout());
        Object[] name={"班级号","班级名称","班长"};
        Object[][] row=new Object[1000][3];
        try {
            stmt = con.createStatement();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        String sql="select * " +
                "from class ";//,change_code " +
        if((!id.equals(""))||(!cname.equals(""))||(!mo.equals(""))){
            sql=sql+"WHERE ";
            if((!id.equals(""))){sql+=" Cid LIKE'"+id+"' AND";}
            if((!cname.equals(""))){sql+=" Cname LIKE'"+cname+"' AND";}
            if((!mo.equals(""))){sql+=" monitor LIKE'"+mo+"' AND";}
            sql=sql.substring(0,sql.length()-3);
        }
        final int[] i={0};
        try {
            ResultSet rs=stmt.executeQuery(sql);
            while(rs.next()){
                String a = rs.getString(1);
                String b = rs.getString(2);
                String c = rs.getString(3);
                Object[] rowdate={a,b,c};
                System.arraycopy(rowdate, 0,row[i[0]], 0, 3);
                i[0]++;
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        final int[] m = {-1};
        DefaultTableModel tableModel=new DefaultTableModel(row,name);
        tableModel.setNumRows(i[0]);
        JTable table = new JTable(tableModel);

        tableModel.addTableModelListener(e -> {
            int type=e.getType();
            if(type==TableModelEvent.DELETE){
                for(int h = m[0] +1; h< i[0]; h++){
                    System.arraycopy(row[h], 0, row[h-1], 0, 3);
                    System.out.println(Arrays.toString(row[h-1]));
                }
                for(int h=0;h<3;h++){row[i[0]-1][h]=null;}
                i[0]--;
                System.out.println("删除第"+(i[0]+1)+"行");
            }else if(type==TableModelEvent.UPDATE) {
                int column = e.getColumn();
                int firstRow = e.getFirstRow();
                Object id1 = row[firstRow][0];
                if (id1 == null && column != 0) {
                    Object new1 = tableModel.getValueAt(firstRow, column);
                    if (!(new1 == null)) {
                        JOptionPane.showMessageDialog(
                                cpj,
                                "班级号不能为空！",
                                "警告",
                                JOptionPane.WARNING_MESSAGE
                        );
                        tableModel.setValueAt(row[firstRow][column], firstRow, column);
                    }
                } else {
                    Object new1;
                    if (column == 0) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String sql2 = "select * from class where Cid='" + new1 + "'";
                        ResultSet rs2;
                        boolean flag = false;
                        try {
                            rs2 = stmt.executeQuery(sql2);
                            flag = rs2.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if (!(row[firstRow][column] == null)) {
                            if (!(new1 == row[firstRow][column])) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "班级号不能修改",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else if (flag || new1 == null) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "班级号已存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql10 = "insert into class value('" + new1 + "',null,null)";
                                stmt.executeUpdate(sql10);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][0] ,firstRow,0);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 1) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                //System.out.println(new1);
                                String sql1 = "UPDATE class set Cname='" + new1 + "'"
                                        + " WHERE Cid='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql1);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "班级名字过长",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    }else if (column == 2) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String sql8="select * from student where class='"+row[firstRow][0]+"'" +
                                " and Sid='"+new1+"'";
                        ResultSet rs;
                        boolean f=true;
                        try {
                            rs=stmt.executeQuery(sql8);
                            f=rs.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        try {
                            if(f) {
                                if (!(new1 == null)) {
                                    String sql6 = "UPDATE class set monitor='" + new1 + "'"
                                            + " WHERE Cid='" + row[firstRow][0] + "'";
                                    stmt.executeUpdate(sql6);
                                }
                                System.out.println("修改完成：第" + firstRow + "行，第" + column + "列，旧值：" + row[firstRow][column] + "新值：" + new1);
                                row[firstRow][column] = new1;
                            }else{
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "该班级无此人",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "该班级无此人",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    }
                }
            }else if(type == TableModelEvent.INSERT){
                System.out.println("添加成功第"+i[0]+"行");
            }
        });

        JScrollPane scrollPane = new JScrollPane(table);
        cppa.add(table.getTableHeader(),BorderLayout.NORTH);
        cppa.add(scrollPane,BorderLayout.CENTER);

        JButton jb=new JButton("删除");
        jb.addActionListener(e -> {
            int result=JOptionPane.showConfirmDialog(
                    cpj,
                    "确认删除？",
                    "提示",
                    JOptionPane.YES_NO_OPTION
            );
            //System.out.println(result);
            if(result==0){
                int[] selectedRows = table.getSelectedRows();
                for (int selectedRow : selectedRows) {
                    // 从表格模型中移除表格中的选中行
                    Object id1 = table.getValueAt(selectedRow, 0);
                    if (id1 != null) {
                        //System.out.println(id);
                        String sql1 = "DELETE  FROM class WHERE Cid='" + id1 + "'";
                        try {
                            stmt.executeUpdate(sql1);
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        System.out.println("删除已完成");
                    }
                    for(int h = 0; h< i[0]; h++){
                        //System.out.println(h);
                        if(id1==row[h][0]){
                            m[0] = h;
                            tableModel.removeRow(m[0]);
                            break;
                        }
                    }
                }
            }
        });
        JButton ajb=new JButton("添加");
        ajb.addActionListener(e -> {
            Object[] row1=new Object[5];
            tableModel.addRow(row1);
            i[0]++;
        });
        Box hb=Box.createHorizontalBox();
        hb.add(ajb);
        hb.add(jb);

        Box vb=Box.createVerticalBox();
        vb.add(cppa);
        vb.add(hb);
        JPanel jp=new JPanel(new FlowLayout());
        jp.add(vb);

        cpj.setContentPane(vb);
        cpj.setSize(400,400);
        cpj.setLocationRelativeTo(null);
        cpj.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        cpj.setVisible(true);
    }
    public static void dtable(String id,String cname){
        JFrame cpj=new JFrame("所有专业情况");
        JPanel cppa=new JPanel(new BorderLayout());
        Object[] name={"专业号","专业名称"};
        Object[][] row=new Object[1000][2];
        try {
            stmt = con.createStatement();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        String sql="select * " +
                "from department ";//,change_code " +
        if((!id.equals(""))||(!cname.equals(""))){
            sql=sql+"WHERE ";
            if((!id.equals(""))){sql+=" Did LIKE'"+id+"' AND";}
            if((!cname.equals(""))){sql+=" Dname LIKE'"+cname+"' AND";}
            sql=sql.substring(0,sql.length()-3);
        }
        final int[] i={0};
        try {
            ResultSet rs=stmt.executeQuery(sql);
            while(rs.next()){
                String a = rs.getString(1);
                String b = rs.getString(2);
                Object[] rowdate={a,b};
                System.arraycopy(rowdate, 0,row[i[0]], 0, 2);
                i[0]++;
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
        final int[] m = {-1};
        DefaultTableModel tableModel=new DefaultTableModel(row,name);
        tableModel.setNumRows(i[0]);
        JTable table = new JTable(tableModel);

        tableModel.addTableModelListener(e -> {
            int type=e.getType();
            if(type==TableModelEvent.DELETE){
                for(int h = m[0] +1; h< i[0]; h++){
                    System.arraycopy(row[h], 0, row[h-1], 0, 2);
                    System.out.println(Arrays.toString(row[h-1]));
                }
                for(int h=0;h<2;h++){row[i[0]-1][h]=null;}
                i[0]--;
                System.out.println("删除第"+(i[0]+1)+"行");
            }else if(type==TableModelEvent.UPDATE) {
                int column = e.getColumn();
                int firstRow = e.getFirstRow();
                Object id1 = row[firstRow][0];
                if (id1 == null && column != 0) {
                    Object new1 = tableModel.getValueAt(firstRow, column);
                    if (!(new1 == null)) {
                        JOptionPane.showMessageDialog(
                                cpj,
                                "班级号不能为空！",
                                "警告",
                                JOptionPane.WARNING_MESSAGE
                        );
                        tableModel.setValueAt(row[firstRow][column], firstRow, column);
                    }
                } else {
                    Object new1;
                    if (column == 0) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        String sql2 = "select * from department where Did='" + new1 + "'";
                        ResultSet rs2;
                        boolean flag = false;
                        try {
                            rs2 = stmt.executeQuery(sql2);
                            flag = rs2.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if (!(row[firstRow][column] == null)) {
                            if (!(new1 == row[firstRow][column])) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "专业号不能修改",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else if (flag || new1 == null) {
                            if (!(new1 == null)) {
                                JOptionPane.showMessageDialog(
                                        cpj,
                                        "专业号已存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            }
                        } else {
                            try {
                                String sql10 = "insert into department value('" + new1 + "',null)";
                                stmt.executeUpdate(sql10);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                                row[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(row[firstRow][0] ,firstRow,0);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 1) {
                        new1 = tableModel.getValueAt(firstRow, column);
                        try {
                            if (!(new1 == null)) {
                                //System.out.println(new1);
                                String sql1 = "UPDATE department set Dname='" + new1 + "'"
                                        + " WHERE Did='" + row[firstRow][0] + "'";
                                stmt.executeUpdate(sql1);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+row[firstRow][column]+"新值："+new1);
                            row[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    cpj,
                                    "专业名称过长",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                            tableModel.setValueAt(row[firstRow][column], firstRow, column);
                            ex.printStackTrace();
                        }
                    }
                }
            }else if(type == TableModelEvent.INSERT){
                System.out.println("添加成功第"+i[0]+"行");
            }
        });

        JScrollPane scrollPane = new JScrollPane(table);
        cppa.add(table.getTableHeader(),BorderLayout.NORTH);
        cppa.add(scrollPane,BorderLayout.CENTER);

        JButton jb=new JButton("删除");
        jb.addActionListener(e -> {
            int result=JOptionPane.showConfirmDialog(
                    cpj,
                    "确认删除？",
                    "提示",
                    JOptionPane.YES_NO_OPTION
            );
            //System.out.println(result);
            if(result==0){
                int[] selectedRows = table.getSelectedRows();
                for (int selectedRow : selectedRows) {
                    // 从表格模型中移除表格中的选中行
                    Object id1 = table.getValueAt(selectedRow, 0);
                    if (id1 != null) {
                        //System.out.println(id);
                        String sql1 = "DELETE  FROM department WHERE Did='" + id1 + "'";
                        try {
                            stmt.executeUpdate(sql1);
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        System.out.println("删除已完成");
                    }
                    for(int h = 0; h< i[0]; h++){
                        //System.out.println(h);
                        if(id1==row[h][0]){
                            m[0] = h;
                            tableModel.removeRow(m[0]);
                            break;
                        }
                    }
                }
            }
        });
        JButton ajb=new JButton("添加");
        ajb.addActionListener(e -> {
            Object[] row1=new Object[5];
            tableModel.addRow(row1);
            i[0]++;
        });
        Box hb=Box.createHorizontalBox();
        hb.add(ajb);
        hb.add(jb);

        Box vb=Box.createVerticalBox();
        vb.add(cppa);
        vb.add(hb);
        JPanel jp=new JPanel(new FlowLayout());
        jp.add(vb);

        cpj.setContentPane(vb);
        cpj.setSize(400,400);
        cpj.setLocationRelativeTo(null);
        cpj.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        cpj.setVisible(true);
    }
    //学生信息存放数组
    final private static Object[] columnNames = {"学号", "姓名", "性别", "班级编号",
                                    "院系编号","生日","籍贯","奖励情况","处罚情况","学籍变更情况"};
    final private static Object[][] rowData =new Object[100000][10];

    public static int search(Object firstRow){
        for(int i=0;i<row;i++){
            if(firstRow==rowData[i][0]){
                return i;
            }
        }
        return -1;
    }

    public static void reward_punish(){
        for (int i=0;i<row;i++) {
            String sql1 = "select reward_level.Cdes from reward,reward_level " +
                    "WHERE reward.Sid='" + rowData[i][0] + "'and reward_level.code=reward.Rlevel " +
                    "order by reward.Rtime DESC,reward.Rid " +
                    "limit 1";
            String sql2 ="select punish_level.Cdes from punishment,punish_level " +
                    "WHERE punishment.Sid='"+rowData[i][0]+"' and punishment.Penable='T' " +
                    "and punish_level.code=punishment.Plevel order by punishment.Ptime DESC,punishment.Pid "
                    +"limit 1";
            String sql3="select change_code.Cdes from changes,change_code " +
                    "WHERE changes.Sid='"+rowData[i][0]+"' " +
                    "and change_code.code=changes.Ch order by changes.Ctime DESC,changes.C_id "
                    +"limit 1";
            ResultSet rs;
            try {
                stmt = con.createStatement();
                rs = stmt.executeQuery(sql1);
                if (rs.next()) {
                    rowData[i][7] = rs.getString(1);
                    tableModel.setValueAt(rowData[i][7],i,7);
                }
                rs =stmt.executeQuery(sql2);
                if (rs.next()) {
                    rowData[i][8] = rs.getString(1);

                    tableModel.setValueAt(rowData[i][8],i,8);
                }
                rs=stmt.executeQuery(sql3);
                if(rs.next()){

                    rowData[i][9]=rs.getString(1);
                    tableModel.setValueAt(rowData[i][9],i,9);
                }else{
                    rowData[i][9]="无";
                    tableModel.setValueAt(rowData[i][9],i,9);
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
    private static int row=0;
    public static void queryData(String id0,String name0,String sex0,String sc0,String dept0,String birth0,String place0) {
        for(int i=row-1;i>=0;i--){
            m=i;
            tableModel.removeRow(i);
        }
        row=0;
        try {
            stmt = con.createStatement();
            String sql = "SELECT sid, sname, sex, c.Cname Class, D.Dname Dept, birth, native_place FROM student LEFT JOIN class c on c.Cid = student.Class LEFT JOIN department d on d.Did = student.Dept ";
            if((!id0.equals(""))||(!name0.equals(""))||(!sex0.equals(""))||(!sc0.equals(""))||(!dept0.equals(""))||(!birth0.equals(""))||(!place0.equals(""))){
                sql=sql+"WHERE ";
                if((!id0.equals(""))){sql+="Sid LIKE'"+id0+"' AND";}
                if((!name0.equals(""))){sql+="Sname LIKE'"+name0+"' AND";}
                if((!sex0.equals(""))){sql+="Sex LIKE'"+sex0+"' AND";}
                if((!sc0.equals(""))){sql+="Class LIKE'"+sc0+"' AND";}
                if((!dept0.equals(""))){sql+="Dept LIKE'"+dept0+"' AND";}
                if((!birth0.equals(""))){sql+="Birth LIKE'%"+birth0+"%' AND";}
                if((!place0.equals(""))){sql+="Native_Place LIKE'%"+place0+"%' AND";}
                sql=sql.substring(0,sql.length()-3);
            }
            ResultSet rs = stmt.executeQuery(sql);
            while (rs.next()) {
                String id = rs.getString("Sid");
                String name = rs.getString("Sname");
                String sex = rs.getString("Sex");
                String sc = rs.getString("Class");
                String dept = rs.getString("Dept");
                String birth = rs.getString("Birth");
                String place = rs.getString("Native_Place");
                Object[] rowdate={id,name,sex,sc,dept,birth,place};
                System.arraycopy(rowdate, 0,rowData[row], 0, 7);
                tableModel.addRow(rowdate);
                row++;
            }
            reward_punish();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void deleteData(String id0,String name0,String sex0,String sc0,String dept0,String birth0,String place0){
        queryData(id0,name0,sex0,sc0,dept0,birth0,place0);
        if(row==0){
            JOptionPane.showMessageDialog(
                    jp,
                    "无相关信息",
                    "提示",
                    JOptionPane.PLAIN_MESSAGE
            );
        }
        try {
            stmt = con.createStatement();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        String sql = "DELETE FROM student ";
        if((!id0.equals(""))||(!name0.equals(""))||(!sex0.equals(""))||(!sc0.equals(""))||(!dept0.equals(""))||(!birth0.equals(""))||(!place0.equals(""))){
            sql=sql+"WHERE ";
            if((!id0.equals(""))){sql+="Sid='"+id0+"' AND";}
            if((!name0.equals(""))){sql+="Sname='"+name0+"' AND";}
            if((!sex0.equals(""))){sql+="Sex='"+sex0+"' AND";}
            if((!sc0.equals(""))){sql+="Class='"+sc0+"' AND";}
            if((!dept0.equals(""))){sql+="Dept='"+dept0+"' AND";}
            if((!birth0.equals(""))){sql+="Birth='"+birth0+"' AND";}
            if((!place0.equals(""))){sql+="Native_Place='"+place0+"' AND";}
            sql=sql.substring(0,sql.length()-3);
            try {
                stmt.executeUpdate(sql);
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }else{
            int result;
            result=JOptionPane.showConfirmDialog(
                    jp,
                    "确认删除全部学生信息？",
                    "提示",
                    JOptionPane.YES_NO_OPTION
            );
            if(result==0){
                result=1;
                /*try {
                    stmt.executeUpdate(sql);
                } catch (SQLException e) {
                    e.printStackTrace();
                }*/
            }
        }
    }
    private static final JPanel jp=new JPanel(new FlowLayout());
    static int m = -1;
    //学生信息表格模型
    private static DefaultTableModel tableModel=new DefaultTableModel(rowData,columnNames);
    public static JPanel table(){
        connect co=new connect();
        con=co.getconnection();
        //设置为边界布局
        JPanel panel = new JPanel(new BorderLayout());
        //创建表格
        tableModel=new DefaultTableModel(rowData,columnNames);
        tableModel.setNumRows(row);
        JTable table = new JTable(tableModel);
        // 给 表格 设置 行排序器
        RowSorter<DefaultTableModel> rowSorter = new TableRowSorter<>(tableModel);
        table.setRowSorter(rowSorter);
        //给表格设置滚动条
        table.setPreferredScrollableViewportSize(new Dimension(400,400));
        JScrollPane scrollPane = new JScrollPane(table);
        //表格增加行
        JButton bt2=new JButton("添加");
        bt2.addActionListener(e -> {
            //new student_message_input();
            String[] rowdate=new String[7];
            row++;
            tableModel.addRow(rowdate);
        });
        //表格删除行
        JButton bt=new JButton("删除");
        bt.setSize(50,50);
        bt.addActionListener(new ActionListener() {
            int result;
            @Override
            public void actionPerformed(ActionEvent e) {
                result=JOptionPane.showConfirmDialog(
                        panel,
                        "确认删除？",
                        "提示",
                        JOptionPane.YES_NO_OPTION
                );
                if(result==0){
                    int[] selectedRows = table.getSelectedRows();
                    for (int selectedRow : selectedRows) {
                        Object id = table.getValueAt(selectedRow, 0);
                        if (id != null) {
                            String sql = "DELETE  FROM student WHERE Sid='" + id + "'";
                            try {
                                stmt.executeUpdate(sql);
                            } catch (SQLException ex) {
                                ex.printStackTrace();
                            }
                            System.out.println("删除已完成");
                        }
                        m=search(id);
                        tableModel.removeRow(m);
                    }
                }
            }
        });

        Box hb=Box.createHorizontalBox();
        hb.add(bt2);
        hb.add(Box.createHorizontalStrut(20));
        hb.add(bt);
        // 在 表格模型上 添加 数据改变监听器
        tableModel.addTableModelListener(e -> {
            // 获取 第一个 和 最后一个 被改变的行（只改变了一行，则两者相同）
            int firstRow = e.getFirstRow();
            //int lastRow = e.getLastRow();
            // 获取被改变的列
            int column = e.getColumn();
            // 事件的类型，可能的值有:
            //     TableModelEvent.INSERT   新行或新列的添加
            //     TableModelEvent.UPDATE   现有数据的更改
            //     TableModelEvent.DELETE   有行或列被移除
            int type = e.getType();
            // 针对 现有数据的更改 更新其他单元格数据
            if(type == TableModelEvent.DELETE){
                for(int i=m+1;i<row;i++){
                    System.arraycopy(rowData[i], 0, rowData[i-1], 0, 10);
                }
                for(int i=0;i<10;i++){rowData[row-1][i]=null;}
                row--;
                System.out.println("删除成功第"+(m+1)+"行");
            }else if (type == TableModelEvent.UPDATE) {
                Object id=rowData[firstRow][0];
                if(id==null&&column!=0) {
                    Object new1=tableModel.getValueAt(firstRow,column);
                    if(!(new1==null)) {
                        JOptionPane.showMessageDialog(
                                panel,
                                "学号不能为空！",
                                "警告",
                                JOptionPane.WARNING_MESSAGE
                        );
                        tableModel.setValueAt(rowData[firstRow][column],firstRow,column);
                    }
                }else{
                    Object new1;
                    if(column==0) {
                        new1=tableModel.getValueAt(firstRow,0);
                        String sql2="select * from student where Sid='"+new1+"'";
                        ResultSet rs2;
                        boolean flag=false;
                        try {
                            rs2 = stmt.executeQuery(sql2);
                            flag=rs2.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if(!(rowData[firstRow][0]==null)){
                            if(!(new1==rowData[firstRow][0])) {
                                JOptionPane.showMessageDialog(
                                        panel,
                                        "学号不能修改",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(rowData[firstRow][0], firstRow, 0);
                            }
                        }else if(flag||new1==null) {
                            if(!(new1==null)){
                                JOptionPane.showMessageDialog(
                                        panel,
                                        "学号已存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE
                                );
                                tableModel.setValueAt(rowData[firstRow][0],firstRow,0);
                            }
                        }else{
                            try {
                                String sql="insert into student value('"+new1+"',null,null,null,null,null,null)";
                                stmt.executeUpdate(sql);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                                rowData[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(rowData[firstRow][0] ,firstRow,0);
                                ex.printStackTrace();
                            }
                        }
                    }else if (column == 1) {
                        new1= tableModel.getValueAt(firstRow, 1);
                        try {
                            if(!(new1==null)) {
                                String sql1 = "UPDATE student set Sname='" + new1 + "'"
                                        + " WHERE Sid='" + rowData[firstRow][0] + "'";
                                stmt.executeUpdate(sql1);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                            rowData[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    panel,
                                    "姓名不能为空且不能长于五个字",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE);
                            tableModel.setValueAt(rowData[firstRow][1], firstRow, 1);
                            ex.printStackTrace();
                        }
                    } else if (column == 2) {
                        new1= tableModel.getValueAt(firstRow, 2);
                        String da=(String) new1;
                        if(new1==null) da="";
                        if((!da.equals("M"))&&(!da.equals("F"))) {
                            if (!(new1==rowData[firstRow][2])) {
                                JOptionPane.showMessageDialog(
                                        panel,
                                        "性别输入错误，男生为M女生为F",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(rowData[firstRow][2], firstRow, 2);
                            }
                        }else{
                            try {
                                String sql2 = "UPDATE student set Sex='" + new1 + "'"
                                    + " WHERE Sid='" + rowData[firstRow][0] + "'";
                                stmt.executeUpdate(sql2);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                                rowData[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(rowData[firstRow][2], firstRow, 2);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 3) {
                        new1= tableModel.getValueAt(firstRow, 3);
                        String sql = "select * from class where Cid='"+new1+"'";
                        ResultSet rs;
                        boolean flag1=true;
                        try {
                            rs = stmt.executeQuery(sql);
                            flag1=rs.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if(!flag1){
                            if((!(new1==rowData[firstRow][3]))) {
                                JOptionPane.showMessageDialog(
                                        panel,
                                        "班级不存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(rowData[firstRow][3], firstRow, 3);
                            }
                        }else {
                            String sql3 = "UPDATE student set Class='" + new1 + "'"
                                    + " WHERE Sid='" + rowData[firstRow][0] + "'";
                            try {
                                stmt.executeUpdate(sql3);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                                rowData[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(rowData[firstRow][3], firstRow, 3);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 4) {
                        new1 = tableModel.getValueAt(firstRow, 4);
                        String sql = "select * from department where Did='"+new1+"'";
                        ResultSet rs;
                        boolean flag1=true;
                        try {
                            rs = stmt.executeQuery(sql);
                            flag1=rs.next();
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                        }
                        if(!flag1){
                            if((!(new1==rowData[firstRow][4]))) {
                                JOptionPane.showMessageDialog(
                                        panel,
                                        "专业不存在",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(rowData[firstRow][4], firstRow, 4);
                            }
                        }else {
                            try {
                                String sql4 = "UPDATE student set Dept='" + new1 + "'"
                                        + " WHERE Sid='" + rowData[firstRow][0] + "'";
                                stmt.executeUpdate(sql4);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                                rowData[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(rowData[firstRow][4], firstRow, 4);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 5) {
                        new1= tableModel.getValueAt(firstRow, 5);
                        String da=(String) new1;
                        if(new1==null) da="";
                        if(!date(da)){
                            if((!(new1==null))) {
                                JOptionPane.showMessageDialog(
                                        panel,
                                        "生日时间不正确或格式错误，格式为yyyy-mm-dd",
                                        "警告",
                                        JOptionPane.WARNING_MESSAGE);
                                tableModel.setValueAt(rowData[firstRow][5], firstRow, 5);
                            }
                        }else {
                            try {
                                String sql5 = "UPDATE student set Birth='" + new1 + "'"
                                        + " WHERE Sid='" + rowData[firstRow][0] + "'";
                                stmt.executeUpdate(sql5);
                                System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                                rowData[firstRow][column] = new1;
                            } catch (SQLException ex) {
                                tableModel.setValueAt(rowData[firstRow][5], firstRow, 5);
                                ex.printStackTrace();
                            }
                        }
                    } else if (column == 6) {
                        new1= tableModel.getValueAt(firstRow, 6);
                        try {
                            if(!(new1==null)) {
                                String sql6 = "UPDATE student set Native_Place='" + new1 + "'"
                                        + " WHERE Sid='" + rowData[firstRow][0] + "'";
                                stmt.executeUpdate(sql6);
                            }
                            System.out.println("修改完成：第"+firstRow+"行，第"+column+"列，旧值："+rowData[firstRow][column]+"新值："+new1);
                            rowData[firstRow][column] = new1;
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(
                                    panel,
                                    "籍贯不能为空且小于50字",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(rowData[firstRow][6],firstRow, 6);
                            ex.printStackTrace();
                        }
                    } else if(column==7){
                        new1= tableModel.getValueAt(firstRow, 7);
                        if(!(new1==rowData[firstRow][7])) {
                            JOptionPane.showMessageDialog(
                                    panel,
                                    "奖惩情况不可修改",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(rowData[firstRow][7], firstRow, 7);
                        }
                    }else if(column==8){
                        new1= tableModel.getValueAt(firstRow, 8);
                        if(!(new1==rowData[firstRow][8])) {
                            JOptionPane.showMessageDialog(
                                    panel,
                                    "奖惩情况不可修改",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(rowData[firstRow][8], firstRow, 8);
                        }
                    }else if(column==9){
                        new1= tableModel.getValueAt(firstRow, 9);
                        if(!(new1==rowData[firstRow][9])) {
                            JOptionPane.showMessageDialog(
                                    panel,
                                    "变更情况不可修改",
                                    "警告",
                                    JOptionPane.WARNING_MESSAGE
                            );
                            tableModel.setValueAt(rowData[firstRow][9], firstRow, 9);
                        }
                    }
                }
            }else if(type == TableModelEvent.INSERT){
                System.out.println("添加成功第"+row+"行");
            }
        });
        // 把 表头 添加到容器顶部（使用普通的中间容器添加表格时，表头 和 内容 需要分开添加）
        panel.add(table.getTableHeader(), BorderLayout.NORTH);
        // 把 表格内容 添加到容器中心
        panel.add(scrollPane, BorderLayout.CENTER);

        Box vb=Box.createVerticalBox();
        vb.add(panel);
        vb.add(hb);

        TableColumn tableColumn = table.getColumnModel().getColumn(5);
        tableColumn.setPreferredWidth(85);
        
        jp.add(vb);
        panel.setPreferredSize(new Dimension(600,300));
        return jp;
    }
    public static void addData(String id,String name,String sex,String sc,String dept,String birth,String place){
        try {
            stmt = con.createStatement();
        } catch (SQLException e) {
            e.printStackTrace();
        }
       try {
            String sql="INSERT INTO student value('"+id+"','"+name+"','"+sex+"','"+sc+"','"+dept+"','"+birth+"','"+place+"')";
            stmt.executeUpdate(sql);
            Object[] rowdate={id,name,sex,sc,dept,birth,place};
            System.arraycopy(rowdate, 0,rowData[row], 0, 7);
            tableModel.addRow(rowdate);
            row++;
        } catch (SQLException e) {
            e.printStackTrace();
        }

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
