#include"staffs.h"
#include<fstream>
#include"books.h"
#include <cstring>


std::string user;
Staffs S;

Staff::Staff(std::string staffName, long staffPassword,std::string staffId,std::vector<std::string> borrowedBooks ):name(staffName),password(staffPassword),id(staffId),borrowed(borrowedBooks){}
Staff::~Staff(){}

//设置人员信息
void Staff::setStaffName(std::string name)
{
    this->name=name;
}

void Staff::setStaffId(std::string id)
{
    this->id=id;
}

void Staff::setStaffPassword(long password)
{
    this->password=password;
}

//获取个人信息
void Staff::getAllStaffInfo(std::string& name ,long& password,std::string& id,std::vector<std::string>& borrowed)
{
    name=this->name;
    password=this->password;
    id=this->id;
    borrowed=this->borrowed;
}

std::string Staff::getStaffName()const
{
    return this->name;
}

std::string Staff::getStaffId()const
{
    return this->id;
}

long Staff::getStaffPassword()const
{
    return this->password;
}

bool Staff::getIsAchievable()const
{
    if(this->borrowed.size()>(MAX_BORROWED_BOOKS-1))
    {
        return false;
    }
    return true;
}

std::vector<std::string> Staff::getBorrowedBooks()const
{
    return this->borrowed;
}

//个人借书、还书检查身份
void Staff::borrowBook(std::string& book)
{
    if(!borrowed.empty()&&borrowed.back()=="无"){
        borrowed.pop_back();
    }
    borrowed.push_back(book);
}

void Staff::returnBook(std::string& book)
{
    auto it = std::find(borrowed.begin(),borrowed.end(),book);//std::find包含在algorithm
    if(it!=borrowed.end()){
        borrowed.erase(it);
        if(borrowed.size()<1){
            borrowed.push_back("无");
        }
    }
}

int Staff::checkBookStatus(const std::string& book) 
{
    int n=0;
    for(const auto& i:borrowed)
    {
        if(i==book)
        {
            return n;
        }
        n++;
    }
    return -1;
}

//返回人员信息
void Staff::getStaffInfo(std::vector<std::string>& result)
{
    result={this->name,std::to_string(this->password),this->id};
    for(const auto& i:borrowed)
    {
        result.push_back(i);
    }
}

//将人员信息写入磁盘
void saveStaffInfoToDisk(Staff& staff)
{
    std::time_t t = std::time(nullptr);
    std::tm tm=*std::localtime(&t);
    std::stringstream filename;
    filename<<std::put_time(&tm,"%Y%m%d%H%M%S")<<".txt";

    std::ofstream file(filename.str());
    if(file.is_open())
    {
        file<<"姓名："<<staff.getStaffName()<<std::endl;
        file<<"密码："<<staff.getStaffPassword()<<std::endl;
        file<<"身份："<<staff.getStaffId()<<std::endl;
        file<<"借书："<<std::endl;
        for(const auto& book:staff.getBorrowedBooks())
        {
            file<<book<<std::endl;
        }
        file.close();
        std::cout<<"信息已保存到文件："<<filename.str()<<std::endl;
    }
    else{
        std::cerr<<"无法打开文件："<<filename.str()<<std::endl;
    }
}


Staffs::Staffs()
{
    std::ifstream infile;
    infile.open("/home/nuaaer/BMS/src/staffs.txt",std::ios::in);
    if(infile.fail())
    {
        std::cerr<<"An error occurred while opening the file:"<<strerror(errno)<<std::endl;
    }
    std::string name,id,temp;
    long password;
    std::vector<std::string>borrowed;

    while(std::getline(infile,temp)){
        std::stringstream line_stream(temp);
        line_stream>>name>>password>>id;
        while(line_stream>>temp)
        {
            borrowed.push_back(temp);
        }
        Staff s(name,password,id,borrowed);
        person.push_back(s);
        borrowed.clear();
    }
    infile.close();
}

Staffs::~Staffs()
{
    std::ofstream outfile;
    outfile.open("/home/nuaaer/BMS/src/staffs.txt",std::ios::trunc);
    if(outfile.fail())
    {
        std::cerr<<"An error occurred while opening the file:"<<strerror(errno)<<std::endl;
    }
    std::string name,id;
    long password;
    std::vector<std::string>borrowed;

    for( auto& i:person)
    {
        i.getAllStaffInfo(name,password,id,borrowed);
        outfile<<name<<" "<<password<<" "<<id<<" ";
        for(const auto&j: borrowed){
            outfile<<j<<" ";
        }
        outfile<<std::endl;
    }
    outfile.close();
}

//添加、删除人员
void Staffs::addStaff()
{
    std::string name,id="1";
    long password=0;
    std::vector<std::string>borrowed={"无"};
    std::cout<<"   >>请输入人员信息："<<std::endl;
    std::cout<<"   >>姓名：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=findStaff(name);
    if(index!=INVALID_INDEX){
        std::cout<<"--------->>该人已存在<<---------"<<std::endl<<std::endl;
    }
    else{
        std::cout<<"   >>密码："<<std::endl;
        password=get_(password);
        std::cout<<std::endl;
        std::cout<<"   >>身份：";
        id=get_(id);
        std::cout<<std::endl;

        Staff staff(name,password,id,borrowed);
        person.push_back(staff);
        std::cout<<"--------->>添加成功<<---------"<<std::endl<<std::endl;
    }
}

void Staffs::deleteStaff()
{
    std::string name;
    std::cout<<"   >>请输入人员信息："<<std::endl;
    std::cout<<"   >>姓名：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=findStaff(name);
    if(index!=INVALID_INDEX){
        person[index]=person.back();
        person.pop_back();
        std::cout<<"--------->>删除成功<<---------"<<std::endl<<std::endl;
    }
    else{
        std::cout<<"--------->>该人不存在<<---------"<<std::endl<<std::endl;
    }
}

//检查登录人员身份
int Staffs::checkLogin(const int i)
{
    std::string name,id="读者",id_input;
    std::vector<std::string>borrowed;
    if(i){
        id="管理员";
    }
    long password_input=0,password;
    std::cout<<"   >>请输入用户名：";
    std::cin>>name;
    //std::cout<<"用户名："<<name<<std::endl;
    std::cout<<std::endl;
    int index=findStaff(name);
    //std::cout<<"index="<<index<<std::endl;
    if(index!=INVALID_INDEX){
        person[index].getAllStaffInfo(name,password,id_input,borrowed);
        //std::cout<<"该用户名对应的文件信息："<<std::endl;
        //std::cout<<person[index].name<<" "<<person[index].password<<" "<<person[index].id<<std::endl;
        std::cout<<"   >>输入密码：";
        password_input=get_(password_input);
        //std::cout<<"输入的密码为："<<password_input<<std::endl;
        std::cout<<std::endl;
        if(password==password_input){
            if(id==id_input){
                user=name;
                std::cout<<"   >>密码正确！"<<std::endl;
                std::cout<<"   >>输入任意值返回"<<std::endl;
                return 1;
            }
            else{
                std::cout<<"--------->>身份错误<<---------"<<std::endl<<std::endl;
                std::cout<<"   >>输入任意值返回"<<std::endl;
            }
        }
        else{
            std::cout<<"--------->>密码错误<<---------"<<std::endl<<std::endl;
            std::cout<<"   >>输入任意值返回"<<std::endl;
        }
    }
    else{
        std::cout<<"--------->>该人不存在<<---------"<<std::endl<<std::endl;
    }
    return 0;
}

//借 还 改 
void Staffs::borrowMultipleBooks(std::string& book,const int n)
{
    person[n].borrowBook(book);
}

void Staffs::returnMultipleBooks(std::string& book,const int n)
{
    person[n].returnBook(book);
}

void Staffs::changeStaff()
{
    std::string name,id="0";
    long password=0;
    std::cout<<"   >>请输入人员信息："<<std::endl;
    std::cout<<"   >>姓名：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=findStaff(name);
    if(index!=INVALID_INDEX){
        std::cout<<"   >>请输入新的信息"<<std::endl<<std::endl;
        std::cout<<"   >>姓名：";
        std::cin>>name;
        std::cout<<std::endl;
        std::cout<<"   >>密码：";
        password=get_(password);
        std::cout<<std::endl;
        std::cout<<"   >>身份：";
        id=get_(id);
        std::cout<<std::endl;
        person[index].setStaffName(name);
        person[index].setStaffId(id);
        person[index].setStaffPassword(password);
        std::cout<<"--------->>修改成功<<---------"<<std::endl<<std::endl;
    }
    else{
        std::cout<<"--------->>该人不存在<<---------"<<std::endl<<std::endl;
    }
}

/*void Staff::getStaffInfo(std::vector<std::string>& result)
{
    result.push_back(this->name);
    result.push_back(std::to_string(this->password));
    result.push_back(this->id);
    for(const auto& book:getBorrowedBooks()){
        result.push_back(book);
    }
}*/

void Staffs::showStaffs()
{
    std::string name;
    std::cout<<"   >>请输入人员信息"<<std::endl<<std::endl;
    std::cout<<"   >>姓名：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=this->findStaff(name);
    if(index!=INVALID_INDEX){
        std::vector<std::string>messages;
        person[index].getStaffInfo(messages);
        messages.push_back("输入任意值返回");

        draw_body_2(messages);
    }
    else{
        std::cout<<"--------->>该人不存在<<---------"<<std::endl;
    }
}

int Staffs::findStaff(const std::string& name) 
{
    int n=0;
    //std::cout<<"findStaff: name="<<name<<std::endl;
    //std::cout<<"person容器中的名字:"<<std::endl;
   // std::cout<<person[0].name<<std::endl;
    //for( auto& i:person)
    for( auto i : person)
    {
        //std::cout<<i.getStaffName()<<std::endl;
        if(i.getStaffName()==name)
        {
            return n;
        }
        n++;
    }
    return -1;
}

std::vector<Staff> Staffs::getPerson() const
{
    return this->person;
}

std::string Staffs::getUser()const
{
    return this->user;
}