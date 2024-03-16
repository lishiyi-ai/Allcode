package org.example.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.DefaultServletHandlerConfigurer;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ViewResolverRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
@ComponentScan("org.example.controller")
@EnableWebMvc
public class SpringMvcConfig implements WebMvcConfigurer {

//    /*
//        开启对静态资源的访问 类似<mvc:default-servlet-handler>
//         */
//    @Override
//    public void configureDefaultServletHandling(
//            DefaultServletHandlerConfigurer configurer
//    ){
//        configurer.enable();
//    }
//    //    配置视图解析程序
//    @Override
//    public void configureViewResolvers(ViewResolverRegistry registry){
//        registry.jsp("/",".jsp");
//    }
}
