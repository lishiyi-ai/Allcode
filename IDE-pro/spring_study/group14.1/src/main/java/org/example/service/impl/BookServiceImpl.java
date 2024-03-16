package org.example.service.impl;

import org.example.dao.BookMapper;
import org.example.domain.Book;
import org.example.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;



@Service
public class BookServiceImpl implements BookService {
    @Autowired
    private BookMapper bookMapper;
    public Book findBookById(Integer id) {
        return bookMapper.findBookById(id);
    }
}
