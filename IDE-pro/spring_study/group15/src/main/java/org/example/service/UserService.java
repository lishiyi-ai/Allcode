package org.example.service;

import org.example.domin.User;

/**
 * 用户接口
 */
public interface UserService {
    //用户账号和密码查询
    User login(User user);
}
