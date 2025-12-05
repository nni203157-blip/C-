#include"UserLinkList.h"
using namespace std;

UserLinKList::UserLinKList(ifstream& ifs)
{
	if (ifs.is_open())
	{
		string line;
		while (getline(ifs, line))
		{
			istringstream iss(line);
			string username, password;

			if (getline(iss, username, '#') && getline(iss, password))			// 利用输入流格式从文件中提取出用户名和密码
			{
				User user;
				user.username = username;
				user.pswd = password;
				addUser(user);
			}
		}
		ifs.close();
	}
	else
	{
		cerr << "打开文件时发生错误：" << endl;
	}
}


UserLinKList::~UserLinKList() {

}


// 头插法增加用户
void UserLinKList::addUser(User user)
{
	UserNode* s = new UserNode(user);
	s->next = head;
	head = s;
}


// 按照字符串查找用户
bool UserLinKList::findUser(string username, User& user)
{
	UserNode* p = head;

	while (p != NULL && p->data.username != username)
	{
		p = p->next;
	}

	if (p == NULL)
	{
		return false;			// 查找失败，返回
	}
	else
	{
		user = p->data;
		return true;			// 查找成功返回查找到的节点
	}
}


//修改用户密码（确保用户存在的前提下）
void UserLinKList::changeUser(string username, string pwd)
{
	UserNode* p = head;
	while (p != NULL && p->data.username != username)
	{
		p = p->next;
	}
	if (p != NULL)
		p->data.pswd = pwd;
}


//检查账号正确性
bool UserLinKList::checkInfo(string usr, string pwd)
{
	User idx = { usr, pwd };
	if (!findUser(usr, idx))
	{
		cout << "               账号不存在！" << endl << endl;
		return false;
	}
	else
	{
		if (idx.pswd != pwd)
		{
			cout << "               密码输入错误！" << endl << endl;
			return false;
		}
		else
			return true;
	}
}


//菜单可视化界面
void UserLinKList::menu()
{
	int option = -1;		//操作选择标志位
	int num = -1;

	while (num != 0)
	{
		system("cls");					//清屏
		cout << "**********************************************************\n";
		cout << "------------------------用户登录系统----------------------\n\n";
		cout << "                   请选择您想进行的操作\n";
		cout << "                        0:退出\n";
		cout << "                        1:用户登录\n";
		cout << "                        2:用户注册\n";
		cout << "                        3:找回密码\n\n";
		cout << "----------------------------------------------------------\n\n";
		cout << "                      请输入您的选择:";
		cin >> option;
		switch (option)
		{
			//退出
		case 0: {
			num = 0;
			break;
		}

			  //登录
		case 1:
		{
			system("cls");
			cout << "**********************************************************\n";
			cout << "----------------------------登录--------------------------\n\n";
			cout << "               请输入账号：";
			cin >> usn;
			cout << endl;
			cout << "               请输入密码：";
			cin >> pwd;
			cout << endl;
			if (usn == "root" && pwd == "root") {
				cout << "               管理员，欢迎您使用图书信息管理系统！" << endl << endl;
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
			}

			else {
				if (!checkInfo(usn, pwd)) {				//检查用户是否注册
					cout << "----------------------------------------------------------\n\n";
					cout << "输入-1返回上一界面" << endl;
					cin >> num;
				}
				else
				{
					cout << "               用户" << usn << "欢迎您使用图书馆信息管理系统!" << endl << endl;	//注册成功
					cout << "----------------------------------------------------------\n\n";
					cout << "输入0结束，输入-1返回上一界面" << endl;
					cin >> num;
				}
			}
			break;
		}


		//注册
		case 2:
		{
			system("cls");
			cout << "**********************************************************\n";
			cout << "--------------------------用户注册------------------------\n\n";
			cout << "               请输入注册的账号：";
			cin >> usn;
			cout << endl;
			User user = { usn, pwd };					// 创建新的用户信息结构体
			while (findUser(usn, user))				// 在链表中查找账号是否已经注册过
			{
				system("cls");
				cout << "**********************************************************\n";
				cout << "--------------------------用户注册------------------------\n\n";
				cout << "               该账号已经注册过，请重新输入！" << endl << endl;
				cout << "               请输入注册的账号：";
				cin >> usn;
				cout << endl;
			}
			cout << "               请输入账号的密码：";
			cin >> pwd;
			cout << endl;
			user = { usn, pwd };
			addUser(user);					// 未注册过添加到用户信息链表
			cout << "               用户" << usn << "注册成功！" << endl << endl;
			cout << "----------------------------------------------------------\n\n";
			cout << "输入-1返回上一界面" << endl;
			cin >> num;
			break;
		}
		//修改密码
		case 3:
		{
			system("cls");
			cout << "**********************************************************\n";
			cout << "--------------------------找回密码------------------------\n\n";
			cout << "               请输入需要修改的账号：";
			cin >> usn;
			cout << endl;
			User idx = { usn,"1" };
			while (!findUser(usn, idx))			//检查账号是否存在
			{
				system("cls");
				cout << "**********************************************************\n";
				cout << "--------------------------找回密码------------------------\n\n";
				cout << "               账号不存在" << endl << endl;
				cout << "               请重新输入账号：";
				cin >> usn;
				cout << endl;
			}
			cout << "               请输入账号的新密码：";
			cin >> pwd;
			cout << endl;
			changeUser(usn, pwd);				//重置密码
			cout << "               用户" << usn << "密码重置成功!" << endl << endl;
			cout << "----------------------------------------------------------\n\n";
			cout << "输入-1返回上一界面" << endl;
			cin >> num;
			break;
		}

		//输入的操作不存在
		default:
			continue;
		}

		if (num == 0) {				//保存用户信息文件，然后退出
			return;
		}

	}
}


//封装用户信息
void UserLinKList::save(ofstream& ofs) {
	UserNode* p = head;
	int cnt = 0;
	while (p != NULL) {
		if (cnt != 1)
			ofs <<  endl << p->data.username << '#' << p->data.pswd;
		else if (cnt == 1)
			ofs << endl << p->data.username << '#' << p->data.pswd;
		cnt++;
		p = p->next;
	}
}
