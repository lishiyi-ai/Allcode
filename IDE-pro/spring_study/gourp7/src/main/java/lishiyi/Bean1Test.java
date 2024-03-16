package lishiyi;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Bean1Test {
    public static void main(String[] args){
//        加载xml配置
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContextBean1.xml");
//        获取Bean1实例
        Bean1 bean1=(Bean1) applicationContext.getBean("bean1");
        System.out.println(bean1);
/*  XmlBeanFactory已被弃用
        // 资源加载
        ClassPathResource = new ClassPathResource("applicationContextBean1.xml");
        // XmlBeanFactory 加载资源并解析注册bean
        BeanFactory = new XmlBeanFactory(classPathResource);
        //获取Bean1实例
        Bean1 bean11=(Bean1) beanFactory.getBean("bean1");
        System.out.println(bean11);*/
    }
}
