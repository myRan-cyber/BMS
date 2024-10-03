#ifndef BOOKS_H
#define BOOKS_H

#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<vector>

#include"draw.h"
#include"staffs.h"


//定义书籍状态常量
#define BORROWED 0
#define IN_STOCK 1
#define INVALID_INDEX -1

//使用struct定义书籍结构体
struct Book{
    //构造函数，用于初始化书籍信息
    BOOK(std::string bookName,std::string bookAuthor,long bookId,std::string bookStatus,std::string bookOwner);
    ~Book();


    //借阅书籍操作
    void borrowBook(std::string& borrowerName);
    //归还书籍操作
    void returnBook(std::string& returnerName);

    //获取书籍信息并写入结果向量中
    void getBookInfo(std::vector<std::string>& result);
    //获取书籍状态
    int getBookStatus() const;
    //获取书籍作者
    std::string getBookAuthor()const;
    //获取书籍名称
    std::string getBookName() const;
    //获取书籍编号
    long getBookId()const;
    //获取书籍所有者
    std::string getBookOwner()const;

    //获取书籍的所有信息
    void getAllBookInfo(const std::string& name,const std::string& author, const long& id,const std::string& status, const std::string& owner);
    

    //设置书籍名称
    void setBookName(std::string newName);
    //设置书籍作者
    void setBookAuthor(std::string newAuthor);
    //设置书籍编号
    void setBookId(long newId);
    //设置书籍状态
    void setBookStatus(std::string newStatus);
    //设置书籍所有者
    void setBookOwner(std::string newOwner);
}


#endif
