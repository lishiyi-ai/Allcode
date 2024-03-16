package Test;

import lishiyi.pojo.User;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Test;

import org.apache.ibatis.io.Resources;

import java.io.IOException;
import java.io.Reader;

public class UserTest {
    @Test
    public void userFindByIdTest(){
        String resources="mybatis-config.xml";
//        创建流
        Reader reader=null;
        try{
//            读取核心映射文件内容到reader对象中
            reader= Resources.getResourceAsReader(resources);
        }catch (IOException e){
            e.printStackTrace();
        }
//        初始化数据库
        SqlSessionFactory sqlMapper=new SqlSessionFactoryBuilder().build(reader);
//        创建SqlSession实例
        SqlSession session=sqlMapper.openSession();
//        传入参数查询
        User user=session.selectOne("findById",1);
        System.out.println(user.getUname());
//        添加一个记录
        User user1=new User();
        user1.setUid(3);
        user1.setUname("王五");
        user1.setUage(18);
        session.insert("addUser",user1);
        session.commit();
        User user2=session.selectOne("findById",3);
        System.out.println(user2.getUid()+" "+user2.getUname());

//        修改一条记录
        user.setUname("赵六");
        user.setUage(19);
        session.update("updateUser",user);
        User user3=session.selectOne("findById",1);
        System.out.println(user3.getUid()+" "+user3.getUname());
//        删除一个记录
        User user4=session.selectOne("findById",3);
        System.out.println(user4.getUid()+" "+user4.getUname());
        session.delete("deleteUser",3);
        User user5=session.selectOne("findById",3);
        if(user5!=null) {
            System.out.println(user5.getUid()+" "+user5.getUname());
        }
//        结束会话
        session.close();
    }
}
