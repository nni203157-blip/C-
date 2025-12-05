#include"AVLTree.h"
#include"UserLinkList.h"
ifstream ifs;
ofstream ofs;
int main() {
    //用户登录页面
    ifs.open("UserData.txt", ios::in);
    UserLinKList user(ifs);              //从UserData中读取用户信息，构建用户信息链表
    ofs.open("UserData.txt");
    if (!ofs) {
        cerr << "无法打开用户数据文件进行保存!" << endl;
        return -1;                              // 文件打开失败，退出程序
    }
    user.menu();                           //进入登录菜单
    user.save(ofs);                     //保存退出
    ofs.close();
    system("pause");

    //图书管理页面
    ifs.open("BookData.txt", ios::in);
    AVLTree AVLTree(ifs);                //从BookData中读取图书信息，构建图书信息平衡二叉树
    AVLTree.menu();                             //进入图书管理系统菜单
    ofs.open("BookData.txt");
    if (!ofs) {
        cerr << "无法打开图书数据文件进行保存!" << endl;
        return -1;                           // 文件打开失败，退出程序
    }
    AVLTree.save(ofs);                   //保存退出
    ofs.close();
    cout << endl;
    cout << "文件已保存，退出管理系统！" << endl;

    return 0;
}