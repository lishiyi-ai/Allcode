package org.example.service;

import org.example.domin.Book;
import org.example.domin.User;
import org.example.entity.PageResult;

/**
 * 图书接口
 */
public interface BookService {
    //查询最新上架的图书
    PageResult selectNewBooks(Integer pageNum, Integer pageSize);
    Book findById(String id);
    Integer borrowBook(Book book);
    PageResult search(Book book, Integer pageNum,Integer pageSize);
    Integer addBook(Book book);
    Integer editBook(Book book);

    PageResult searchBorrowed(Book book, User user, Integer pageNum, Integer pageSize);
    boolean returnBook(String id, User user);
    Integer returnConfirm(String id);
}
