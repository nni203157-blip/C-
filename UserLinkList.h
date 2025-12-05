#ifndef USERLINKLIST_H
#define USERLINKLIST_H
//用户登录管理系统（链表）
#include<string>
#include<sstream>
#include <fstream>					
#include<iostream>
using namespace std;

struct User {                           //用户结构体
	string username;                        //用户名
	string pswd;                        //密码
};

struct UserNode	                    //用户链表结点类型						        
{
	User data;									//数据域：存放用户数据
	UserNode* next;								    //指针域：下一个结点的指针
	UserNode() :next(NULL) {}					    //构造函数
	UserNode(User d) :data(d), next(NULL) {}        //重载构造函数
};

class UserLinKList
{
	UserNode* head;							  //用户链表头结点
public:
	string usn, pwd;						//用户账号密码
	UserLinKList(ifstream& ifs);					//用文件初始化链表
	~UserLinKList();								//释放链表
	bool checkInfo(string usr, string idx);		  //校验账号信息
	void addUser(User user);                       //添加用户
	bool findUser(string username, User& user);		//寻找用户
	void changeUser(string username, string pswd);		//修改用户信息
	void menu();								  //登录菜单函数
	void save(ofstream& ofs);				  //封装过的保存用户信息函数(外部调用)
};
#endif //USERLINKLIST_H

