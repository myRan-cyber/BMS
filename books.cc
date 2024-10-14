#include"books.h"
#include"draw.h"
//#include<iostream>
//#include<string>
#include<cstring>
//#include<vector>
//#include<fstream>
#include<sstream>
//#include<iomanip>
//#include<ctime>

Books B;//储存所有书本信息

Book::Book(std::string bookName,std::string bookAuthor,long bookId,std::string bookStatus,std::string bookOwner):name(bookName),author(bookAuthor),id(bookId),owner(bookOwner)
{
    if(bookStatus=="在库"){
        this->status=IN_STOCK;
    }
    else{
        this->status=BORROWED;
    }
}
Book::~Book(){};

//书本借还函数
void Book::borrowBook(std::string& name)
{
    this->status=BORROWED;
    this->owner=name;
}

void Book::returnBook(std::string& name)
{
    this->status=IN_STOCK;
    this->owner="无";
}

//返回书本信息
void Book::getBookInfo(std::vector<std::string>& result)
{
    result={this->name,this->author,std::to_string(this->id)};
    if(this->status==IN_STOCK){
        result.push_back("在库");
    }
    else{
        result.push_back("借出");
    }
    result.push_back(this->owner);
}

//获取书本信息
int Book::getBookStatus() const
{
    return this->status;
}

std::string Book::getBookName() const
{
    return this->name;
}

std::string Book::getBookAuthor() const
{
    return this->author;
}

long Book::getBookId() const
{
    return this->id;
}

std::string Book::getBookOwner() const
{
    return this->owner;
}

void Book::getAllBookInfo(std::string& name,std::string& author, long& id,std::string& status,std::string& owner)
{
    name=this->name;
    author=this->author;
    id=this->id;
    owner=this->owner;

    if(this->status=BORROWED){
        status="借出";
    }
    else{
        status="在库";
    }
}   

//设置书本信息
void Book::setBookName(std::string name)
{
    this->name=name;
}

void Book::setBookAuthor(std::string author)
{
    this->author=author;
}

void Book::setBookId(long id)
{
    this->id=id;
}

void Book::setBookOwner(std::string owner)
{
    this->owner=owner;
}

void Book::setBookStatus(std::string status)
{
    if(status=="借出"){
       this->status=BORROWED;
    }
    else{
        this->status=IN_STOCK;
    }
}

void saveBooksToDisk(std::vector<Book>& books)
{
    //获取当前时间作为文件名
    std::time_t t=std::time(nullptr);
    std::tm tm=*std::localtime(&t);
    std::stringstream filename;
    filename << std::put_time(&tm,"%Y%m%d%H%M%S")<<".txt";
    //打开文件并写入信息
    std::ofstream file(filename.str());
    if(file.is_open()){
        for(auto& book:books)
        {
            file<<"书名："<<book.getBookName()<<std::endl;
            file<<"作者："<<book.getBookAuthor()<<std::endl;
            file<<"书号："<<book.getBookId()<<std::endl;
            file<<"状态："<<(book.getBookStatus()==IN_STOCK?"在库":"借出")<<std::endl;
            file<<"所有者："<<book.getBookOwner()<<std::endl;
            file<<"--------------------"<<std::endl;
        }
        file.close();
        std::cout<<"书籍信息已保存到文件："<<filename.str()<<std::endl;
    }
    else{
        std::cerr<<"无法打开文件："<<filename.str()<<std::endl;
    }
}

Books::Books()
{
    std::ifstream infile;
    infile.open("/home/nuaaer/BMS/src/books.txt",std::ios::in);
    if(infile.fail())
    {
        std::cerr<<"An error occurred while opening the file:"<<std::strerror(errno)<<std::endl;
    }
    
    std::string name,author,owner,status;
    long id;

    while(infile>>name>>author>>id>>status>>owner)
    {
        Book b(name,author,id,status,owner);
        books.push_back(b);
    }

    infile.close();
}

Books::~Books()
{
    std::ofstream outfile;
    outfile.open("/home/nuaaer/BMS/src/books.txt",std::ios::trunc);
    if(outfile.fail()){
        std::cerr<<"An error occurred while opening the file:"<<std::strerror(errno)<<std::endl;
    }
    std::string name,author,owner,status;
    long id;

    for(auto i:books)
    {
        i.getAllBookInfo(name,author,id,status,owner);
        outfile<<name<<" "<<author<<" "<<id<<" "<<status<<" "<<owner<<std::endl;
    }
    outfile.close();

}

//添加书籍
void Books::addBook()
{
    std::string name,author,bookStatus="0",owner;
    long id=0;
    std::cout<<"   >>请输入书籍信息"<<std::endl<<std::endl
    <<"   >>名称：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=this->findBook(name);
    if(index!=INVALID_INDEX){
        std::cout<<"--------->>该书已存在<<---------"<<std::endl;
    }
    else{
        std::cout<<"   >>作者：";
        std::cin>>author;
        std::cout<<std::endl;
        std::cout<<"   >>id:";
        id=get_input_is_valid(id);
        std::cout<<std::endl;
        std::cout<<"   >>状态：";
        bookStatus=get_input_is_valid(bookStatus);
        std::cout<<std::endl;
        std::cout<<"   >>拥有者：";
        std::cin>>owner;
        std::cout<<std::endl;

        Book b(name,author,id,bookStatus,owner);
        books.push_back(b);
        std::cout<<"--------->>添加成功!<<---------"<<std::endl;
    }
}

//删除书籍
void Books::deleteBook()
{
    std::string name;
    std::cout<<"   >>请输入书籍信息 "<<std::endl<<std::endl;
    std::cout<<"   >>名称:";
    std::cin>>name;
    std::cout<<std::endl;
    int index=this->findBook(name);
    if(index!=INVALID_INDEX){
        books[index]=books.back();
        books.pop_back();
        std::cout<<"--------->>删除成功！<<---------"<<std::endl;
    }
    else{
        std::cout<<"--------->>该书不存在<<---------"<<std::endl;
    }
}

//修改书籍
void Books::changeBook()
{
    std::string name,author,status="0",owner;
    long id=0;
    std::cout<<"   >>请输入书籍信息"<<std::endl<<std::endl
    <<"   >>名称：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=this->findBook(name);
    if(index!=INVALID_INDEX)
    {
        std::cout<<"   >>请输入修改后的书籍信息："<<std::endl<<std::endl;
        std::cout<<"   >>名称：";
        std::cin>>name;
        books[index].setBookName(name);
        std::cout<<std::endl;
        std::cout<<"   >>作者：";
        std::cin>>author;
        books[index].setBookAuthor(author);
        std::cout<<std::endl;
        std::cout<<"   >>id:";
        id=get_input_is_valid(id);
        books[index].setBookId(id);
        std::cout<<std::endl;
        std::cout<<"   >>状态：";
        status=get_input_is_valid(status);
        books[index].setBookStatus(status);
        std::cout<<std::endl;
        std::cout<<"   >>拥有者：";
        std::cin>>owner;
        books[index].setBookOwner(owner);
        std::cout<<std::endl;
        std::cout<<"--------->>修改成功<<---------"<<std::endl;
    }
    else{
        std::cout<<"--------->>该书不存在<<---------"<<std::endl;
    }
}

//查找书籍 
int Books::findBook(std::string searchName)
{
    std::string name,author,owner,status;
    long id,n=0;
    for(auto i:books)
    {
        i.getAllBookInfo(name,author,id,status,owner);
        if(name==searchName){
            return n;
        }
        n++;
    }
    return INVALID_INDEX;
}

//展示书籍 
void Books::showBooks()
{
    std::string name,author,status="0",owner;
    long id=0;
    std::cout<<"   >>请输入书籍信息"<<std::endl<<std::endl
    <<"   >>名称：";
    std::cin>>name;
    std::cout<<std::endl;
    int index=this->findBook(name);
    if(index!=INVALID_INDEX)
    {
        //std::vector<std::string> result;
       // books[index].getBookInfo(result);
        std::vector<std::string> messages ;
        books[index].getBookInfo(messages);
        messages.push_back("输入任意值返回");
        draw_body_2(messages);
    }
    else{
        std::cout<<"--------->>该书不存在<<---------"<<std::endl;
    }
}

//借阅多本书籍
void Books::borrowMultipleBooks(std::string name,int n)
{
    books[n].borrowBook(name);
}

//归还多本书籍
void Books::returnMultipleBooks(std::string name,int n)
{
    books[n].returnBook(name);
}
