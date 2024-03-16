package org.example.demo3;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestXml {
    public static void main(String[] args){
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContext.xml");
        UserDao userDao =applicationContext.getBean("userDao",UserDao.class);
        userDao.insert();
        System.out.println();
        userDao.delete();
        System.out.println();
        userDao.update();
        System.out.println();
        userDao.select();
    }
}
