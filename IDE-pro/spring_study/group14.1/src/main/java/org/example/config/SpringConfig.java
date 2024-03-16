package org.example.config;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

@Configuration
@Import({MyBatisConfig.class, JdbcConfig.class})
@ComponentScan(value = "org.example.service")
public class SpringConfig {
}
