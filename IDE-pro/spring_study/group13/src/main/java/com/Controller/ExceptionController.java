//package com.Controller;
//
//import com.exception.MyException;
//import org.springframework.stereotype.Controller;
//import org.springframework.web.bind.annotation.RequestMapping;
//
//import java.io.FileInputStream;
//import java.io.FileNotFoundException;
//import java.util.ArrayList;
//
//@Controller
//public class ExceptionController {
//    @RequestMapping("/showNullPointer")
//    public void showNullPointer(){
//        System.out.println("yes");
//        ArrayList<Object> list=null;
//        System.out.println(list.get(4));
//    }
//
//    @RequestMapping("/showIOException")
//    public void showIOException() throws FileNotFoundException {
//        FileInputStream in=new FileInputStream("Java.xml");
//    }
//    @RequestMapping("/showArithmetic")
//    public void showArithmetic(){
//        int c=1/0;
//    }
//
//    @RequestMapping("/addData")
//    public void addData()throws MyException {
//        throw new MyException("新增数据异常!");
//    }
//}
