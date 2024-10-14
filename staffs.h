#ifndef BMS_SRC_STAFFS_H
#define BMS_SRC_STAFFS_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<sstream>
#include"draw.h"



#define MAX_BORROWED_BOOKS 3  //最大借书为3

//定义人员结构
struct Staff{
    //构造函数初始化人员信息
    Staff(std::string staffName, long staffPassword,std::string staffId,std::vector<std::string> borrowedBooks );
    ~Staff();

    //借阅书籍操作
    void borrowBook(std::string& bookName);
    //归还书籍操作'
    void returnBook(std::string& bookName);

    //检查人物身份与书籍的关系
    int checkBookStatus(const std::string& book);

    //获取人员信息并填充到结果向量
    void getStaffInfo(std::vector<std::string>& result);

    //设置人员姓名
    void setStaffName(std::string newName);
    //设置人员身份标识
    void setStaffId(std::string newId);
    //设置人员密码
    void setStaffPassword(long newPassword);

    //获取人员的所有信息
    void getAllStaffInfo(std::string& name ,long& password,std::string& id,std::vector<std::string>& borrowed);
    //获取人员姓名
    std::string getStaffName() const;
    //获取人员身份标识
    std::string getStaffId() const;
    //获取人员密码
    long getStaffPassword() const;
    //获取人员是否可行
    bool getIsAchievable() const;
    //获取人员借阅的书籍列表
    std::vector<std::string> getBorrowedBooks() const;

    friend void saveStaffInfoToDisk(const Staff& staff);

private:
    //人员姓名
    std::string name;
    //人员密码
    long password;
    //人员标识
    std::string id;
    //人员借阅的书
    std::vector<std::string>borrowed;
};

//将人员信息写入磁盘
void saveStaffInfoToDisk(Staff& staff);

//人员集合
struct Staffs{
    Staffs();
    ~Staffs();

    //检查登录人员信息
    int checkLogin(const int i) ;

    //借阅多本书籍
    void borrowMultipleBooks(std::string& book,const int n);
    //归还多本书籍
    void returnMultipleBooks(std::string& book,const int n);
    
    //添加人员
    void addStaff();
    //删除人员
    void deleteStaff();
    //修改人员信息
    void changeStaff();
    //展示人员信息
    void showStaffs();
    //查找人员
    int findStaff(const std::string& name) ;
    //返回人员信息
    std::vector<Staff> getPerson() const;
    //返回用户
    std::string getUser() const;

    friend int draw_borrow();
    friend int draw_return();
    friend int draw_show_all_books();
    friend int draw_show_all_visitors();

private:
    std::vector<Staff> person;
    std::string user;
        
};

extern Staffs S;

#endif
