#include "AVLTree.h"
using namespace std;
//AVLTree类的实现
AVLTree::AVLTree(ifstream& ifs) {
	if (ifs.is_open()) {
		string line;
		while (getline(ifs, line)) {// 逐行读取文件数据
			// 使用 输入流stringstream 分割每行数据
			stringstream ss(line);
			string bookname, number;
			int bookstates, bookBorrow;

			// 以:为分隔符提取每个属性
			getline(ss, bookname, ':');
			getline(ss, number, ':');
			ss >> bookstates;
			ss.ignore();  // 忽略:符号
			ss >> bookBorrow;

			// 将图书信息添加到二叉树中
			add(bookname, number, bookstates, bookBorrow);
		}
		ifs.close();
	}
	else
	{
		cerr << "打开文件时发生错误：" << endl;
	}
}


AVLTree::~AVLTree() {

}

void AVLTree::menu()
{
	int option = -1;			//操作选择标志位
	int num = -1;
	int op;
	system("cls");
	cout << "**********************************************************\n";
	cout << "----------------欢迎来到图书馆书籍管理系统----------------\n\n";
	cout << "                    请选择你的身份\n";
	cout << "                    1：管理员\n";
	cout << "                    2：读者\n\n";
	cout << "----------------------------------------------------------\n\n";
	cout << "                    请输入您的选择:";
	cin >> op;
	if (op == 1) {
		while (num != 0)
		{
			system("cls");
			cout << "**********************************************************\n";
			cout << "----------------------图书馆管理系统----------------------\n\n";
			cout << "                      0:退出\n";
			cout << "                      1:更新图书信息\n";
			cout << "                      2:添加新图书\n";
			cout << "                      3:删除旧图书\n";
			cout << "                      4:显示当前图书信息树\n\n";
			cout << "----------------------------------------------------------\n\n";
			cout << "                      请输入您的选择:";
			cin >> option;
			switch (option)
			{
			case 0: {
				num = 0;
				break;
			}
			case 1:
			{
				string Num;
				system("cls");
				cout << "**********************************************************\n";
				cout << "-----------------------更新图书信息-----------------------\n\n";
				cout << "               请输入需要更新的图书编号：";
				cin >> Num;
				cout << endl;
				updataInfo(Num);
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;
			}
			case 2:
			{
				string Name, Num;
				int states, borrow;
				system("cls");
				cout << "**********************************************************\n";
				cout << "------------------------添加新图书------------------------\n\n";
				cout << "               请输入图书名称：";
				cin >> Name;
				cout << endl;
				cout << "               请输入图书编号：";
				cin >> Num;
				cout << endl;
				cout << "               请输入图书状态（0 - 旧书，1 - 新书）：" ;
				cin >> states;
				cout << endl;
				cout << "               请输入图书是否在馆（0 - 出借，1 - 在馆）：" ;
				cin >> borrow;
				cout << endl;
				if (add(Name, Num, states, borrow)) {
					cout << "                        添加成功！" << endl << endl;
				}
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;
			}
			case 3:
			{
				string Num;
				system("cls");
				cout << "**********************************************************\n";
				cout << "------------------------删除旧图书------------------------\n\n";
				cout << "               请输入需要删除的图书编号：";
				cin >> Num;
				cout << endl;
				if(deleteNode(Num))
					cout << "                        删除成功！"<<endl<<endl;
				else
					cout << "                删除失败！没有编号为" <<Num<<"的书！"<< endl << endl;
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;  
			}
			case 4:
			{
				system("cls");
				cout << "**********************************************************\n";
				cout << "---------------------显示当前图书信息树-------------------\n\n";
				printAVL(r);
				cout << endl;
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;
			}
			default:
				continue;
			}
			if (num == 0)
				return;
		}
	}
	else if (op == 2) {
		while (num != 0)
		{
			system("cls");
			cout << "**********************************************************\n";
			cout << "-----------------------图书馆管理系统---------------------\n\n";
			cout << "                       0:退出\n";
			cout << "                       1:借书\n";
			cout << "                       2:还书\n";
			cout << "                       3:显示当前图书信息树\n\n"; 
			cout << "----------------------------------------------------------\n\n";
			cout << "                       请输入您的选择:";
			cin >> option;
			switch (option)
			{
			case 0: {
				num = 0;
				break;
			}
			case 1:
			{
				string Num;
				system("cls");
				cout << "**********************************************************\n";
				cout << "---------------------------借书---------------------------\n\n";
				cout << "               请输入想要借走的图书编号：";
				cin >> Num;
				cout << endl;
				bookborrow(Num);
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;
			}
			case 2:
			{
				string Num;
				system("cls");
				cout << "**********************************************************\n";
				cout << "---------------------------还书---------------------------\n\n";
				cout << "               请输入您想要归还的图书的编号：";
				cin >> Num;
				cout << endl;
				bookreturn(Num);
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;
			}
			case 3:
			{
				system("cls");
				cout << "**********************************************************\n";
				cout << "---------------------显示当前图书信息树-------------------\n\n";
				printAVL(r);
				cout << endl;
				cout << "----------------------------------------------------------\n\n";
				cout << "输入0结束，输入-1返回上一界面" << endl;
				cin >> num;
				break;
			}
			default:
				continue;
			}
			if (num == 0)
				return;
		}
	}
}

//打印函数
void AVLTree::printAVL(AVLNode* p)
{
	if (!p) {  //当结点不存在的时候
		return;
	}
	depth = getHeight(r);
	printAVL(p->lchild);
	cout << p->book.number << ' ' << p->book.bookname << ' ';
	if (p->book.states == 0)
		cout << "旧书" << ' ';
	else
		cout << "新书" << ' ';
	if (p->book.borrow == 0)
		cout << "出借" << ' ';
	else
		cout << "在库" << ' ';
	cout << "平衡因子为"<<p->bf;
	cout << endl;
	printAVL(p->rchild);
}

	
//删除图书（封装）
bool AVLTree::deleteNode(string num) {
	flag=deleteNode(r, num,NULL);
	depth = getHeight(r);
	banlance(r);
	return flag;
}

bool AVLTree::deleteNode(AVLNode* p, string usn, AVLNode* parent) {
	if (p == NULL) return false;  // 如果节点为空，直接返回
	// 找到要删除的节点
	if (p->book.number == usn) {
		// 1. 节点有两个子节点
		if (p->lchild && p->rchild) {
			if (getHeight(p->lchild) < getHeight(p->rchild)) {
				AVLNode* successorParent = p;
				AVLNode* successor = p->rchild;
				// 寻找右子树的最小节点（中序后继）
				while (successor->lchild) {
					successorParent = successor;
					successor = successor->lchild;
				}

				// 将后继节点的值赋给当前节点
				p->book = successor->book;
				return  deleteNode(successor, successor->book.number, successorParent);
			}
			else {
				AVLNode* successorParent = p;
				AVLNode* successor = p->lchild;
				// 寻找左子树的最大节点（中序后继）
				while (successor->rchild) {
					successorParent = successor;
					successor = successor->rchild;
				}

				// 将后继节点的值赋给当前节点
				p->book = successor->book;
				return  deleteNode(successor, successor->book.number, successorParent);
			}
		}
		// 2. 只有一个子节点（左或右）
		else if(p->lchild&&!p->rchild) {
			if (parent == NULL) {  // 如果删除的是根节点
				 r =  p->lchild;
			}
			else {
				parent->lchild =p->lchild;
			}
			delete p;  // 删除节点
			p = NULL;
		}
		else if (!p->lchild && p->rchild) {

			if (parent == NULL) {  // 如果删除的是根节点
				* r =* p->rchild;
			}
			else {
				parent->rchild = p->rchild;
			}
			delete p;  // 删除节点
			p = NULL;
		}
		else {
			if (parent == NULL) {  // 删除根节点的情况
				r = NULL;
			}
			else if (parent->lchild == p) {
				parent->lchild = NULL;
			}
			else if (parent->rchild == p) {
				parent->rchild = NULL;
			}

			delete p;  // 删除节点
			p = NULL;
			depth = getHeight(r);

		}
		depth = getHeight(r);
		return true;
	}
	// 3. 节点不等于要删除的编号，递归查找
	else if (p->book.number > usn) {
		return deleteNode(p->lchild, usn, p);

	}
	else {
		return deleteNode(p->rchild, usn, p);

	}
}

//增加新书
bool AVLTree::add(string name, string num, int state, int borrow) {
	AVLNode* p = new AVLNode(name, num, state, borrow);
	return add(r, p);  // r是根节点
}

bool AVLTree::add(AVLNode*& T, AVLNode* p) {
	if (r == NULL) {
		r = p;
		depth = getHeight(r);
		return true;
	}

	// 按书编号进行插入
	if (T->book.number > p->book.number) {
		if (T->lchild == NULL) {
			T->lchild = p;
			depth = getHeight(r);
			banlance(T);
		}
		else {
			flag = add(T->lchild, p);	
			banlance(T);
			return flag;
		}
	}
	else if (T->book.number < p->book.number) {
		if (T->rchild == NULL) {
			T->rchild =p;
			depth = getHeight(r);
			banlance(T);
		}
		else {
			flag = add(T->rchild, p);
			banlance(T);

			return flag;
		}
	}
	else {  // 书已存在
		cout << "               编号为 " << p->book.number << " 的书已存在！" << endl;
		delete p;
		return false;
	}

}


//平衡操作(遍历每个结点)
void AVLTree::banlance(AVLNode*& T) {
	if (T == NULL)return;
	banlance(T->lchild);
	depth = getHeight(r);
	if (T->bf>1) {
		if (T->lchild->bf >= 0) {
			T = LL(T);
		}
		else if (T->lchild->bf < 0) {
			T = LR(T);
		}
	}
	else if (T->bf<-1) {
		if (T->rchild->bf <= 0) {
			T = RR(T);
			
		}
		else if (T->rchild->bf >0) {
			T = RL(T);
		}
	}
	banlance(T->rchild);
	depth = getHeight(r);
}

// LL旋转
AVLNode* AVLTree::LL(AVLNode* a) {
	AVLNode* b = a->lchild;
	a->lchild = b->rchild;
	b->rchild = a;
	depth = getHeight(r);
	return b;
}

// RR旋转
AVLNode* AVLTree::RR(AVLNode* a) {
	AVLNode* b = a->rchild;
	a->rchild = b->lchild;
	b->lchild = a;
	depth = getHeight(r);
	return b;
	
}

// LR旋转
AVLNode* AVLTree::LR(AVLNode* a) {
	a->lchild=RR(a->lchild);  // 先对a的左子树进行RR旋转
	return LL(a);                // 然后对a进行LL旋转
}

// RL旋转
AVLNode* AVLTree::RL(AVLNode* a) {
	a->rchild=LL(a->rchild);  // 先对a的右子树进行LL旋转
	return RR(a);               // 然后对a进行RR旋转
}

//获取树的深度
int AVLTree::getHeight(AVLNode* T) {
	if (T == NULL) return 0;

	int left, right;		//记录左右子树深度

	left = getHeight(T->lchild);		 //当前结点左子树深度
	right = getHeight(T->rchild);		 //当前结点右子树深度
	T->bf = left - right;
	return  max(left, right) + 1;		 //取左右子树中最深的一个作为返回值
}






//更新图书信息
void AVLTree::updataInfo(string num)
{
	AVLNode* T = r;
	while (T != NULL && num != T->book.number) {		//查找需要修改的图书编号
		if (num < T->book.number)
			T = T->lchild;		//小于就在左子树上查找
		else
			T = T->rchild;		//大于就在右子树上查找
	}
	if (T == NULL) {
		system("cls");
		cout << "**********************************************************\n";
		cout << "------------------------更新图书信息----------------------\n\n";
		cout << "               图书编号 " << num << " 不存在，请重新输入！" << endl;
	}
	else {
		int sign ;			//每一项元素是否需要修改标志位
		string idxs;				//暂存需要修改的字符串类型数据
		system("cls");
		cout << "**********************************************************\n";
		cout << "------------------------更新图书信息----------------------\n\n";
		cout << "        是否修改图书名称（0 - 不需要，1 - 需要）：";
		cin >> sign;
		cout << endl;
		if (sign == 1) {
			while (1) {
				cout << "               请输入新的图书名：";
				cin >> idxs;
				cout << endl;
				if (idxs == T->book.bookname) {
					cout << "               与原名称一致，请重新修改" << endl<<endl;
				}
				else {
					T->book.bookname = idxs;
					cout << "                        修改成功!" << endl<<endl;
					break;
				}
			}
		}
		cout << "      是否修改图书在馆状态（0 - 不需要，1 - 需要）：" ;
		cin >> sign;
		cout << endl;
		if (sign == 1) {
			if (T->book.borrow == 1)
				T->book.borrow = 0;
			else
				T->book.borrow = 1;
			cout << "                        修改成功!" << endl << endl;
		}

		cout << "                      全部修改完成！" << endl << endl;
	}
}



//借书
void AVLTree::bookborrow(string num) {
	AVLNode* T = r;
	while (T != NULL && num != T->book.number) {		//查找需要修改的图书编号
		if (num < T->book.number)
			T = T->lchild;		//小于就在左子树上查找
		else
			T = T->rchild;		//大于就在右子树上查找
	}
	if (T == NULL)
		cout << "               图书编号 " << num << " 的书不存在，请重新输入！" << endl << endl;
	else {
		if (T->book.borrow == 0) {
			cout << "               图书编号 " << num << " 的书已出借，借书失败！" << endl << endl;
		}
		else {
			T->book.borrow = 0;
			cout << "                        借书成功!" << endl << endl;
		}
	}
}

//还书
void AVLTree::bookreturn(string num) {
	AVLNode* T = r;
	while (T != NULL && num != T->book.number) {		//查找需要修改的图书编号
		if (num < T->book.number)
			T = T->lchild;		//小于就在左子树上查找
		else
			T = T->rchild;		//大于就在右子树上查找
	}
	if (T == NULL)
		cout << "               图书编号 " << num << " 的书不存在，请重新输入！" << endl << endl;
	else {
		T->book.borrow = 1;
		cout << "                        还书成功!" << endl << endl;
	}
}


//保存
void AVLTree::save(ofstream& ofs) {
	save(ofs, r);
}

void AVLTree::save(ofstream& ofs, AVLNode* T) {
	if (T == NULL) return;
	if (T == r) ofs << T->book.bookname << ':' << T->book.number << ':' << T->book.states << ':' << T->book.borrow;
	else ofs << endl << T->book.bookname << ':' << T->book.number << ':' << T->book.states << ':' << T->book.borrow;
	save(ofs, T->lchild);
	save(ofs, T->rchild);
}

