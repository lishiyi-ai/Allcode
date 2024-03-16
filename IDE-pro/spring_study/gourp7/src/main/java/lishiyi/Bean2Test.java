package lishiyi;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Bean2Test {
    public static void main(String[] args){
        //        加载xml配置
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContextBean2.xml");
        //        获取Bean2实例
        Bean2 bean2=(Bean2) applicationContext.getBean("bean2");
        System.out.println(bean2);
    }
}
