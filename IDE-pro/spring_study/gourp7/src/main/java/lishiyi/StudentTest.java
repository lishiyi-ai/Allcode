package lishiyi;

import org.springframework.context.support.AbstractApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class StudentTest {
    public static void main(String[] args){
        AbstractApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContextStudent.xml");
        Student student=(Student) applicationContext.getBean("student");
        System.out.println(student);
        applicationContext.registerShutdownHook();
    }
    /* bean的生命周期 java EE的书上代码
        public static void main(String[] args){
        ApplicationContext applicationContext=
                new ClassPathXmlApplicationContext("applicationContextStudent.xml");
        Student student=(Student) applicationContext.getBean("student");
        System.out.println(student);
        AbstractApplicationContext ac=(AbstractApplicationContext) applicationContext;
        applicationContext.registerShutdownHook();
    }
     */
}
