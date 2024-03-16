package org.example.config;

import org.mybatis.spring.SqlSessionFactoryBean;
import org.mybatis.spring.mapper.MapperScannerConfigurer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;

import javax.sql.DataSource;

public class MyBatisConfig {

//    等同于注册 SqlsessionFactoryBean
    @Bean
    public SqlSessionFactoryBean getSqlSessionFactoryBean(
            @Autowired DataSource dataSource
            ){
        SqlSessionFactoryBean ssfb=new SqlSessionFactoryBean();
        ssfb.setDataSource(dataSource);
        return ssfb;
    }

//    定义Mybatis的扫描映射
    @Bean
    public MapperScannerConfigurer getMapperScannerConfig(){
        MapperScannerConfigurer msc=new MapperScannerConfigurer();
        msc.setBasePackage("org.example.dao");
        return msc;
    }
}
