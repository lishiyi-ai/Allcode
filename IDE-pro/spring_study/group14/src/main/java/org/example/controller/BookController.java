package org.example.controller;

import org.example.domain.Book;
import org.example.service.BookService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class BookController {
    @Autowired
    private BookService bookService;
    @RequestMapping("/book")
    public ModelAndView findBookById(Integer id){
        Book book = bookService.findBookById(id);
        System.out.println(book.getId());
        ModelAndView modelAndView = new ModelAndView();
        modelAndView.setViewName("book.jsp");
        modelAndView.addObject("book",book);
        return modelAndView;
    }
}
