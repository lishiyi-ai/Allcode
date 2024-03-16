package org.example.service.impl;

import org.example.mapper.UserMapper;
import org.example.domin.User;
import org.example.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.SQLOutput;

/**
 * 用户接口实现类
 */
@Service
public class UserServiceImpl implements UserService {
    @Autowired
    private UserMapper userMapper;
    @Override
    public User login(User user){
        System.out.println(user.getEmail()+" "+user.getPassword());
        User user1 =userMapper.login(user);
        System.out.println(user1);
        return userMapper.login(user);
    }
}
