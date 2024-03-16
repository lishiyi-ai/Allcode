package org.example.demo1;
//JDK代理

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class MyProxy implements InvocationHandler {
//    声明目标类接口
    private UserDao userDao;
//    创建代理方法
    public Object createProxy(UserDao userDao){
        this.userDao=userDao;
//        1.类加载器
        ClassLoader classLoader=MyProxy.class.getClassLoader();
//        2.被代理对象实现的所有接口
        Class[] classes=userDao.getClass().getInterfaces();
//        使用代理类进行增强，返回代理对象
        return Proxy.newProxyInstance(classLoader,classes,this);
    }

    /*
    *所有动态代理类的方法，都会交由invoke（）方法去处理
    * proxy被代理对象
    * method将要被执行的方法信息（反射）
    * args执行方法需要的参数
     */

    public Object invoke(Object proxy, Method method,Object[] args)throws Throwable{
//        创建切面对象
        MyAspect myAspect=new MyAspect();
//        前增强
        myAspect.check_Permissions();
//        在目标类上调用方法，并传入参数
        Object object=method.invoke(userDao,args);
//        后增强
        myAspect.log();
        return object;
    }
}
