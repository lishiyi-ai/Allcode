//package com.Controller;
//
//import com.exception.MyException;
//import org.springframework.stereotype.Component;
//import org.springframework.web.servlet.HandlerExceptionResolver;
//import org.springframework.web.servlet.ModelAndView;
//
//import javax.servlet.http.HttpServletRequest;
//import javax.servlet.http.HttpServletResponse;
//import java.io.PrintWriter;
//import java.io.StringWriter;
//import java.io.Writer;
//
//@Component
//public class MyExceptionHandler implements HandlerExceptionResolver {
//    /**
//     * @param request 当前的http request
//     * @param response 当前http response
//     * @param handler 正在执行的Handler
//     * @param ex handler执行时抛出的exception
//     * @return ModelAndView
//     */
//    public ModelAndView resolveException(HttpServletRequest request
//            ,HttpServletResponse response,Object handler,Exception ex){
//        String msg;
//        if(ex instanceof MyException){
//            msg=ex.getMessage();
//        }else{
//            Writer out=new StringWriter();
//            PrintWriter s=new PrintWriter(out);
//            ex.printStackTrace(s);
//            String sysMsg=out.toString();
//            msg="网络异常";
//        }
//        ModelAndView modelAndView=new ModelAndView();
//        modelAndView.addObject("msg",msg);
//        modelAndView.setViewName("error.jsp");
//        return modelAndView;
//    }
//}
