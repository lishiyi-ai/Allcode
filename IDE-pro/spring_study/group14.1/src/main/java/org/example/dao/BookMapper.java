package org.example.dao;

import org.apache.ibatis.annotations.Select;
import org.example.domain.Book;

public interface BookMapper {
    public Book findBookById(Integer id);
}
