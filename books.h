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

//书籍结构体
struct Book{
    //构造函数，用于初始化书籍信息
    Book(std::string bookName,std::string bookAuthor,long bookId,std::string bookStatus,std::string bookOwner);
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
    void getAllBookInfo(std::string& name,std::string& author, long& id,std::string& status,std::string& owner);
    

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

    //书籍名称
    std::string name = "nuaa";
    //书籍作者
    std::string author =  "nuaaer";
    //书籍编号
    long id = 001;
    //书籍状态
    int status=IN_STOCK;
    //书籍所有者，若被借出为借出者姓名，若在库为无
    std::string owner = "nuaaer";
};

//书籍集合
struct Books{
    Books();
    ~Books();

    //添加书籍操作
    void addBook();
    //删除书籍操作
    void deleteBook();
    //修改书籍操作
    void changeBook();
    //展示书籍操作
    void showBooks();
    //借阅多本书籍操作
    void borrowMultipleBooks(std::string borrowerName,int numBooks);
    //归还多本书籍操作
    void returnMultipleBooks(std::string returnerName,int numBooks);
    //查找书籍操作
    int findBook(std::string bookName);
    //返回书籍容器
    std::vector<Book> getBooks() const;


    //几个友元函数
    friend int draw_borrow();
    friend int draw_return();
    friend int draw_show_all_books();

private:
    //书籍容器，包含所有的Book类书籍
    std::vector<Book>books = { };
};

//将书籍集合保存到磁盘的函数
void saveBooksToDisk(std::vector<Book>& books);
//外部定义的Books类对象
extern Books B;

#endif
