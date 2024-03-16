package org.example.config;
import com.alibaba.druid.pool.DruidDataSource;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.PropertySource;

import javax.sql.DataSource;

/*
*等同于
* <context:property-placeholder location = "classpath:jdbc.properties"/>
*/
@PropertySource("classpath:jdbc.properties")
public class JdbcConfig {
//    等同于 <property name="   " value=${jdbc.driver}>
    @Value("${jdbc.driverClassName}")
    private String driver;
    @Value("${jdbc.url}")
    private String url;
    @Value("${jdbc.username}")
    private String username;
    @Value("${jdbc.password}")
    private String password;

//    定义dataSource的bean，等同于<bean id="dataSource" class="com,alibaba.druid.pool.DruidDataSource">
    @Bean("dataSource")
    public DataSource getDataSource(){
        DruidDataSource ds=new DruidDataSource();
//        等同于set注入<property name>
        ds.setDriverClassName(driver);
        ds.setUrl(url);
        ds.setUsername(username);
        ds.setPassword(password);
        return ds;
    }
}
