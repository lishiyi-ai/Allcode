package org.example.service;

import org.example.domin.Record;
import org.example.domin.User;
import org.example.entity.PageResult;

/**
 * 借阅记录接口
 */
public interface RecordService {
    //新增借阅记录
    Integer addRecord(Record record);
    //查询借阅记录
    PageResult searchRecords(Record record, User user, Integer pageNum, Integer pageSize);
}
