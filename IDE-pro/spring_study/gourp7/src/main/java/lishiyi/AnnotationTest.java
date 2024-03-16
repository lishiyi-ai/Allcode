package lishiyi;

import lishiyi.controller.UserController;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class AnnotationTest {
    public static void main(String[] args){
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContext.xml");
        UserController userController=(UserController) applicationContext.getBean("userController");
        userController.save();
    }
}
