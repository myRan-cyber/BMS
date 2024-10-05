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
int draw_log_in_manager();
int draw_log_in_reader();

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
int draw_show_all_visitors();

//暂停等待输入
void pause();
//几种绘制函数
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
void draw_body_2(std::vector<std::string> messages);

//检测输入函数
template<typename T>
T get_(T t)
{
    T input;
    bool out=false;
    while (!out){        std::cin>>input;
        //输入类型不匹配
        if(std::cin.fail()){
            std::cout<<"!>> >> 类型错误 << <<!"<<std::endl
            <<"    >> 请重新输入：";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        //针对不同类型进行检查
        else{
            if constexpr(std::is_same<T,int>::value)
            {
                if(input<=0||input>t){
                    std::cout<<"!>> >> 输入错误 << <<!"<<std::endl
                    <<"   >> 请重新输入：";
                }
                else{
                    out=true;
                }
            }
            else if constexpr(std::is_same<T,long>::value)
            {
                if(input>std::numeric_limits<long>::max())
                {
                    std::cout<<"!>> >> 输入错误 << <<!"<<std::endl
                    <<"   >> 请重新输入：";
                }
                else{
                    out=true;
                }
            }
            else if constexpr(std::is_same<T,string>::value){
                if(t=="1"&&input!="管理者"&&input!="读者"){
                    std::cout<<"!>> >> 输入错误 << <<!"<<std::endl
                    <<"!>> >> 应输入管理者或读者 << <<!"<<std::endl
                    <<"   >> 请重新输入：";
                }
                else if(t=="0"&&input!="在库"&&input!="借出"){
                    std::cout<<"!>> >> 输入错误 << <<!"<<std::endl
                    <<"!>> >> 应输入在库或借出 << <<!"<<std::endl
                    <<"   >> 请重新输入：";
                }
                else{
                    out=true;
                }
            }
        }
    }
    return input;
}

//界面函数数组
extern std::vector<int(*)()>Interface;


#endif
