package Test;

import lishiyi.pojo.Student;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.io.Reader;
import java.util.List;

public class MyBatisTest {
//    private SqlSessionFactory sqlSessionFactory;
    private SqlSession sqlSession;
    @Before
    public void init() {
        String resources = "mybatis-config.xml";
        Reader reader=null;
        try {
            reader = Resources.getResourceAsReader(resources);
        } catch (IOException e) {
            e.printStackTrace();
        }
        SqlSessionFactory sqlMapper = new SqlSessionFactoryBuilder().build(reader);
        sqlSession = sqlMapper.openSession();
    }
    @Test
    public void findAllStudent(){
        List<Student> list= sqlSession.selectList("findAll");
        for(Student student:list){
            System.out.println(student);
        }
    }
    @After
    public void destroy(){
        sqlSession.commit();
        sqlSession.close();
    }
}
