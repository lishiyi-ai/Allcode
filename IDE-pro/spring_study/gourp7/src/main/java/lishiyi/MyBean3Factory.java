package lishiyi;

public class MyBean3Factory {
    public MyBean3Factory(){
        System.out.println("bean3工厂实例化中");
    }
    public Bean3 createBean3(){
        return new Bean3();
    }
}
