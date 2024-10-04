#ifndef DRAW_H
#define DRAW_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<limits>
#include<type_traits>
#include<iomanip>
#include "books.h"
#include "staffs.h"

//开始界面
int draw_begin();

//管理员、读者界面
int draw_manager();
int draw_reader();

//管理员、读者登陆界面
int draw_long_in_manager();
int draw_long_in_reader();

//借书还书界面
int draw_borrow();
int draw_return();

//管理、增删改查书籍
int draw_manage_book();
int draw_add_book();
int draw_delete_book();
int draw_find_book();
int draw_change_book();

//管理、增删改查人员
int draw_manage_visitor();
int draw_add_visitor();
int draw_delete_visitor();
int draw_find_visitor();
int draw_change_visitor();

//查看所借书籍、所有书籍、所有人员
int draw_show_borrowedBooks();
int draw_show_all_books();
int draw_show_all_visitor();

//暂停等待输入
void pause();
//
void draw_1(std::vector<std::string> messages);
//
void draw_2(std::vector<std::string> messages);
//
void draw_head();
//
void draw_tail_1();
//
void draw_tail_2();
//
void draw_tail_3();
//
void draw_body_1(std::vector<std::string> messages);
//
void draw_body_1(std::vector<std::string> messages);

//检测输入函数
template<typename T>
T get_(T t)
{
    T input;
    bool out=false;
    while (!out){
        
    }
}


#endif
