package org.example.config;

import org.example.interceptor.ResourcesInterceptor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;
import org.springframework.web.servlet.ViewResolver;
import org.springframework.web.servlet.config.annotation.*;

import java.util.List;


@Configuration
@PropertySource("classpath:ignoreUrl.properties")
@ComponentScan({"org.example.controller"})
@EnableWebMvc
public class SpringMvcConfig implements WebMvcConfigurer {

    @Value("#{'${ignoreUrl}'.split(',')}")
    private List<String> ignoreUrl;
    @Bean
    public ResourcesInterceptor resourcesInterceptor(){
        return new ResourcesInterceptor(ignoreUrl);
    }
    /*
     * 在注册的拦截器类中添加自定义拦截器
     * addPathPatterns()方法设置拦截的路径
     * excludePathPatterns()方法设置不拦截的路径
     */

    /*
     开启对静态资源的访问 类似<mvc:default-servlet-handler>
    */
    @Override
    public void configureDefaultServletHandling(
        DefaultServletHandlerConfigurer configurer
    ){
        configurer.enable();
    }
//    配置视图解析程序
    @Override
    public void configureViewResolvers(ViewResolverRegistry registry){
        registry.jsp("/admin/",".jsp");
    }

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(resourcesInterceptor())
                .addPathPatterns("/**")
                .excludePathPatterns("/css/**","/js/**","/img/**");
    }
}
