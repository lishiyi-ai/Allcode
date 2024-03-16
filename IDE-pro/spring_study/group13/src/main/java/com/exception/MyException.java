package com.exception;
//自定义异常处理器
public class MyException extends Exception{
    private String message;
    public MyException(String message){
        super(message);
        System.out.println(message);
        this.message = message;
    }

    @Override
    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }
}
