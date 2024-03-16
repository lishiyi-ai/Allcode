package org.example.controller;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

public class AuthController {
    @RequestMapping(value = {"add","delete"})
    public void checkAuh(){
        System.out.println("增删操作校验");
    }
    @RequestMapping(value = "/method", method = {RequestMethod.GET,RequestMethod.POST})
    public void getandpost(){
        System.out.println("get and post");
    }
}
