package org.example.demo4;

import org.example.demo3.UserDao;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestAnnotation {
    public static void main(String[] args){
        ApplicationContext context=new ClassPathXmlApplicationContext("applicationContext-Anno.xml");
        UserDao userDao=context.getBean("userDao",UserDao.class);
        userDao.insert();
        System.out.println();
        userDao.delete();
        System.out.println();
        userDao.update();
        System.out.println();
        userDao.select();
    }
}
