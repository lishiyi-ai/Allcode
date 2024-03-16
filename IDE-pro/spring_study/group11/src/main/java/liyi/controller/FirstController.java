package liyi.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class FirstController {
    @RequestMapping(value="/firstController1")
    public String sayHello(){
        System.out.println("访问到controller");
        return "success";
    }
}
