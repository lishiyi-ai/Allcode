package org.example;

import org.example.service.UserService;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class TestSpring {
    public static void main(String[] args){
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContext.xml");
        UserService userService=applicationContext.getBean("userService", UserService.class);
        boolean flag=userService.login("张三","123456");
        if(flag) {
            System.out.println("登入成功");
        }else{
            System.out.println("登入失败");
        }
    }
}
