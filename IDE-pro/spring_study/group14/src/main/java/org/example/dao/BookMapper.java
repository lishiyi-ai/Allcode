package org.example.dao;

import org.example.domain.Book;

public interface BookMapper {
    public Book findBookById(Integer id);
}
