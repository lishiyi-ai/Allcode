package org.example.dao;

public class UserDaoImpl implements UserDao {
    @Override
    public boolean login(String name, String password) {
        if(name.equals("张三")&&password.equals("123456")){
            return true;
        }
        return false;
    }
}
