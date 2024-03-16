package org.example.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;


//标注在类上
@Controller
@RequestMapping("/springMVC")
public class SecondController {
    @RequestMapping(path = "/firstController")
//    设置当前方法返回值类型为String，用于指定请求完成后跳转的页面
    public void sayHello(){
        System.out.println("访问到controller");
        //    设定具体跳转的页面
        //return "success";

    }
}
