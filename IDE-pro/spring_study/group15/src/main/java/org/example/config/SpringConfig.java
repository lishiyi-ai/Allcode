package org.example.config;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;
import org.springframework.jdbc.datasource.DataSourceTransactionManager;
import org.springframework.transaction.annotation.EnableTransactionManagement;

import javax.sql.DataSource;

@Configuration
@Import({MyBatisConfig.class, JdbcConfig.class})
@ComponentScan("org.example.service")
/*开启事务管理
等同于<tx:annotation-driven transaction-manager="transactionManager">
 */
@EnableTransactionManagement
public class SpringConfig {
    /*
     * <"org.springframework.jdbc.datasource.DataSourceTransactionManager">
     */
    @Bean("transactionManager")
    public DataSourceTransactionManager getDataSourceTransactionManager(
            @Autowired DataSource dataSource
    ){
        DataSourceTransactionManager dtm=new DataSourceTransactionManager();
//        等同于<property name="dataSource" ref="dataSource">
        dtm.setDataSource(dataSource);
        return dtm;
    }
}
