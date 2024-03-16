import org.example.User2;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestUser2 {
    public static void main(String[] args)throws Exception{
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContext-user2.xml");
        User2 user2=applicationContext.getBean("user2",User2.class);
        System.out.println(user2);
    }
}
