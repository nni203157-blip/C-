#ifndef AVLTREE_H
#define AVLTREE_H
//图书书籍管理系统
#include<string>
#include<sstream>
#include <fstream>					
#include<iostream>
using namespace std;

//图书结构体
struct Book {
    string bookname;                       //图书名称
    string number;                        //图书编号   
    int states;                        //图书状态(1 - 新书, 0 - 旧书）  
    int borrow;                        //图书借阅状态(1 - 在库, 0 - 出借）
    
};

//定义图书信息二叉平衡树结点结构体
struct AVLNode {
    int bf = 0;                  //结点平衡因子
    AVLNode* lchild;     //左右孩子指针
    AVLNode* rchild;
    Book book;          //图书信息

public:
    AVLNode():lchild(NULL),rchild(NULL) {}
    AVLNode(string name, string num, int state, int borrow) {          //构造函数
        book.bookname = name;
        book.number = num;
        book.states = state;
        book.borrow = borrow;
        lchild = NULL;
        rchild = NULL;
    }                
};

class AVLTree {
    bool flag;
    AVLNode* r = NULL;               //指向树根
    int depth = 0;

public:
    AVLTree(ifstream& ifs);  //使用文件对象初始化二叉树
    ~AVLTree();  //二叉树的释放

    void menu();
    void printAVL(AVLNode* p);  //打印二叉树

    bool add(string name, string num, int state, int borrow);  //封装后的添加结点函数
    bool add(AVLNode*& T, AVLNode* p);  //添加结点

    bool deleteNode(string num);                               //封装后的删除结点函数
    bool deleteNode(AVLNode* p, string usn, AVLNode* s);     //删除结点


    void banlance(AVLNode*& T);  //平衡操作
    AVLNode* RR(AVLNode* a);  //RR
    AVLNode* LR(AVLNode* a);  //LR
    AVLNode* LL(AVLNode* a);  //LL
    AVLNode* RL(AVLNode* a);  //RL

    void updataInfo(string num);                               //更新图书状态
    void bookborrow(string num);                              //借书
    void bookreturn(string num);                              //还书
    int getHeight(AVLNode* T);                                 //获取树的高度

    void save(ofstream& ofs);  //封装后的写入函数
    void save(ofstream& ofs, AVLNode* T);//将图书信息存入文件
};


#endif //AVLTREE_H
