#include"draw.h"
#include"books.h"
#include"staffs.h"
//Interface 界面函数数组
std::vector<int(*)()> Interface ={draw_begin,draw_manager,draw_reader,draw_log_in_manager,draw_log_in_reader,draw_borrow,draw_return,
                                    draw_manage_book,draw_add_book,draw_delete_book,draw_change_book,draw_find_book,
                                    draw_manage_visitor,draw_add_visitor,draw_delete_visitor,draw_change_visitor,draw_find_visitor,
                                    draw_show_borrowedBooks,draw_show_all_books,draw_show_all_visitors};
int introduction()
{
	std::cout << "*********************************************************" << std::endl << std::endl;
	std::cout << "————-————-————-————-————-关于本图书管理系统-————-————-————-————-————" << std::endl;
	std::cout << "|                                                    |" << std::endl;
	std::cout << "|        ————-————->>1.功能说明<<-————-————           |" << std::endl;
	std::cout << "|        ————-————->>2.书籍说明<<-————-————           |" << std::endl;
	std::cout << "|        ————-————->>3.返回   <<-————-————           |" << std::endl;
	std::cout << "|                                                  |" << std::endl;
	std::cout << "*********************************************************" << std::endl;
	std::cout << "————-————->>请选择：";

	int i;
	std::cin >> i;
	switch (i)
	{
	case 1:
		std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
		std::cout << "|       通过本系统你可以：                                |" << std::endl;
		std::cout << "|登录管理员信息，对书本信息、相关人员操作                     |" << std::endl;
		std::cout << "|登录读者信息，可进行借书还书操作                            |" << std::endl;
		std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
		break;
	case 2:
		std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
		std::cout << "|图书主要分文学类和技术类两种                                           |" << std::endl;
		std::cout << "|你最多可在本图书馆借出三本书                                           |" << std::endl;
		std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
		break;
	case 3: 
		return 0;
	default:
		std::cout << "输入错误" << std::endl;
		break;
	}
	return 0;
}

void find_back()
{
	std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
	std::cout << "|如果读者遗忘密码，请联系管理员                                    |" << std::endl;
	std::cout << "|可联系以下管理员：                                              |" << std::endl;
	std::cout << "|姓名：张一  电话号码：10086                                      |" << std::endl;
	std::cout << "|姓名：钱七  电话号码：10087                                      |" << std::endl;
	std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
}

int help()
{
	std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
	std::cout << "|          1.将人员信息保存在磁盘文件                             |" << std::endl;
	std::cout << "|          2.将书籍信息保存在磁盘文件                             |" << std::endl;
	std::cout << "|          3.忘记密码                                          |" << std::endl;
	std::cout << "————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl;
    std::cout << "————-————->>请选择";
	
    int i;
    std::string staffName;
    long staffPassword;
    std::string staffId;
    std::vector<std::string>borrowedBooks;
    Staff staff(staffName,staffPassword,staffId,borrowedBooks);
    std::vector<Book>books;
	std::cin >> i;
	switch (i) 
    {
	case 1:
        std::cout<<"请输入人员姓名：";
        std::cin>>staffName;
        std::cout<<"请输入人员密码：";
        std::cin>>staffPassword;
        std::cout<<"请输入人员标志：";
        std::cin>>staffId;
		saveStaffInfoToDisk(staff);
		    break;
	case 2:
		saveBooksToDisk(books);
			break;
	case 3:
			void find_back();
			break;
	default:
			std::cout << "输入错误" << std::endl;
			break;
	}
	return 0;
}

//开始界面 管理员界面 登录界面
int draw_begin()
{
    std::vector<std::string>messages={"1 序言","2 管理员","3 普通读者","4 帮助","5 退出"};
    draw_1(messages);
    int message=get_(5);
    switch(message)
    {
        case 1:
        return introduction();
        case 2:
        return 15;
        case 3:
        return 14;
        case 4:
        return help();
        case 5:
        std::exit(0);
    }
    return 0;

}

int draw_manager()
{
	std::vector<std::string> messages = { "1 管理书籍", "2 管理人员", "3 返回"};
	draw_1(messages);
	int message = get_(3);
	switch (message)
	{
	case 1:  return 3;
	case 2:  return 4;
	case 3:  return 0;
	}
	return 0;
}
int draw_log_in_manager()
{
	draw_head();
	int n = S.checkLogin(1);
	draw_tail_3();
	pause();
	if (n)
		return 2;
	return 0;
}
int draw_log_in_reader()
{
    draw_head();
	int n = S.checkLogin(0);
	draw_tail_3();
	pause();
	if (n)
		return 1;
	return 0;
}


//管理书籍界面 增删改查界面 查看界面
int draw_manage_book()
{
	std::vector<std::string> messages = { "1 添加书籍", "2 删除书籍", "3 查找书籍", "4 修改书籍", "5 查看所有书籍", "6 返回" };
	draw_1(messages);
	int message = get_(6);
	switch (message)
	{
	case 1:  return 7;
	case 2:  return 8;
	case 3:  return 9;
	case 4:  return 10;
	case 5:  return 19;
	case 6:  return 2;
	}
	return 0;
}
int draw_add_book()
{
	draw_head();
	B.addBook();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 3;
}
int draw_delete_book()
{
	draw_head();
	B.deleteBook();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 3;
}
int draw_find_book()
{
	draw_head();
	B.showBooks();
	draw_tail_3();
	pause();
	return 3;
}
int draw_change_book()
{
	draw_head();
	B.changeBook();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 3;
}
int draw_show_all_books()
{
	std::vector<std::string> messages;
    std::vector<Book> books=B.getBooks();

	for (const auto& book: books)
	{
		std::string temp = book.getBookName();
		if (book.getBookStatus())
		{
			temp += " ";
			temp += "在库";
			messages.push_back(temp);
		}
	}

	messages.push_back("输入任意值返回");
	draw_head();
	draw_body_2(messages);
	draw_tail_3();
	pause();
	return 3;
}

//管理人员界面，增删改查，查看所有人信息界面
int draw_manage_visitor()
{
	std::vector<std::string> messages = { "1 添加用户", "2 删除用户", "3 修改用户","4 查看用户", "5 查看所有人员", "6 返回" };
	draw_1(messages);
	int message = get_(6);
	switch (message)
	{
	case 1:  return 11;
	case 2:  return 12;
	case 3:  return 13;
	case 4:  return 17;
	case 5:  return 18;
	case 6:  return 2;
	}
	return 0;
}
int draw_add_visitor()
{
	draw_head();
	S.addStaff();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 4;
}
int draw_delete_visitor()
{
	draw_head();
	S.deleteStaff();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 4;
}
int draw_change_visitor()
{
	draw_head();
	S.changeStaff();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 4;
}
int draw_find_visitor()
{
	draw_head();
	S.showStaffs();
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	pause();
	return 4;
}
int draw_show_all_visitors()
{
	std::vector<std::string> messages;

	for (const auto& staff: S.getPerson())
	{
		std::string temp = staff.getStaffName();
		temp += " ";
		temp += staff.getStaffId();
		messages.push_back(temp);
	}
	messages.push_back("输入任意值返回");
    draw_head();
	draw_body_2(messages);
	draw_tail_3();
	pause();
	return 4;
}


//读者界面 借书、还书界面，查看借书信息界面
int draw_reader()
{
	std::vector<std::string> messages = { "1 借书", "2 还书", "3 查看书籍", "4 返回" };
	draw_1(messages);
	int message = get_(4);
	switch (message)
	{
	case 1: return 6;
	case 2: return 5;
	case 3: return 16;
	case 4: return 0;
	}
	return 0;
}
int draw_borrow()
{
	draw_head();
	std::string name;
	std::cout << "     >>请输入要借阅书的名字";
	std::cin >> name;
    std::cout << std::endl;
	int staff_Index = S.findStaff(S.user);
	int book_Index = B.findBook(name);
	if (S.person[staff_Index].getIsAchievable() && B.books[book_Index].getBookStatus()==IN_STOCK)
	{
		S.person[staff_Index].borrowBook(name);
        B.books[book_Index].borrowBook(S.user);
		std::cout << "     >>借阅成功!" << std::endl << std::endl;
		//std::cout << "  >>借出时间为：" << getCurrentSystemTime() << std::endl;
		std::cout << "     >>输入任意值返回" << std::endl;
		draw_tail_3();
		pause();
		return 1;
	}
	std::cout << "     >>借阅失败!" << std::endl << std::endl;
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	std::cin >> name;
	return 1;
}
int draw_return()
{
	draw_head();
	std::string book;
	std::cout << "     >>请输入要归还书的名字:";
	std::cin >> book; std::cout << std::endl;
	int staff_Index = S.findStaff(S.getUser());
	int book_Index = B.findBook(book);
    std::vector<Staff> person=S.getPerson();
    std::vector<Book> books=B.getBooks();
	if (person[staff_Index].checkBookStatus(book) != INVALID_INDEX && (books[book_Index].getBookStatus()!=IN_STOCK))
	{
		S.getPerson()[staff_Index].returnBook(book);
        std::string user=S.getUser();
        B.getBooks()[book_Index].returnBook(user);
		std::cout << "     >>归还成功" << std::endl << std::endl;
		std::cout << "     >>输入任意值返回" << std::endl;
		draw_tail_3();
		pause();
		return 1;
	}
	std::cout << "     >>并未借阅该书籍" << std::endl << std::endl;
	std::cout << "     >>输入任意值返回" << std::endl;
	draw_tail_3();
	std::cin >> book;
	return 1;
}
int draw_show_borrowedBooks()
{
    std::string user=S.getUser();
	int n = S.findStaff(user);
    std::vector<Staff> person = S.getPerson();
	std::vector<std::string> borrowed = person[n].getBorrowedBooks();
	borrowed.push_back("输入任意值返回");
	draw_head();
	draw_body_2(borrowed);
	draw_tail_3();
	pause();
	return 1;

}

void pause()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

//绘制函数 两个设定好的函数 一个绘制头的函数 两个绘制内容主体函数 三种绘制尾的函数
void draw_1(std::vector <std::string> messages)
{
	draw_head();
	draw_body_1(messages);
	draw_tail_1();

}
void draw_2(std::vector<std::string> messages)
{
	draw_head();
	draw_body_2(messages);
	draw_tail_1();
}
void draw_head()
{
	std::cout << "-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-" << std::endl ;
	std::cout << "|                   欢迎来到图书管理系统                     |" << std::endl << std::endl;
}
void draw_body_1(std::vector<std::string> messages)
{
	for (const auto& i:messages)
	{
		std::cout << "      ————-————->> " <<std::setw(15) <<std::left << i << " <<-————-————                  |" << std::endl << std::endl;
	}
	int n = 5 - messages.size();
	for (int i = 0; i < n; i++)
	{
		std::cout << "                                                             |" << std::endl << std::endl;
	}
}
void draw_body_2(std::vector<std::string> messages)
{
	for (const auto&i : messages)
	{
		std::cout << "     >> " << std::setw(30) << std::left << i << " <<                      |" << std::endl << std::endl;
	}
	int n = messages.size();
	for (int i = 0; i < 5 - n; i++)
	{
		std::cout << "                                                                |" << std::endl << std::endl;
	}
}
void draw_tail_1()
{
	std::cout << "-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————" << std::endl << std::endl;
	std::cout << "<<-————请选择————->> : ";
}
void draw_tail_2()
{
	std::cout << "-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————" << std::endl << std::endl;
	std::cout << "<<-————请输入————->> : ";
}
void draw_tail_3()
{
	std::cout << "-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————-————" << std::endl << std::endl;
}
