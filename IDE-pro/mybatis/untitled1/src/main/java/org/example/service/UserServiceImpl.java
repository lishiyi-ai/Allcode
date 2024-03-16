package org.example.service;

import org.example.dao.UserDao;

public class UserServiceImpl implements UserService {
    UserDao userdao;

    public void setUserDao(UserDao userdao) {
        this.userdao = userdao;
    }

    @Override
    public boolean login(String name, String password) {
        return userdao.login(name,password);
    }
}
