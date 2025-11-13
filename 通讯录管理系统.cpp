//添加，显示，删除，查找，修改，清空，退出

#include<iostream>
#include<string>

#define MAX 1000

using namespace std;

//菜单
void showmenu()
{
	cout<<"**********管理系统**********\n"<<endl;
	cout << "1.添加信息" << endl;
	cout << "2.显示信息"<<endl;
	cout << "3.删除信息"<<endl;
	cout << "4.查找信息"<<endl;
	cout << "5.修改信息"<<endl;
	cout << "6.清空信息"<<endl;
	cout << "0.退出系统"<<endl;
}
//联系人
struct person
{
	string name;
	int sex;
	int age;
	string phone;
	string addr;
};
//通讯录
struct book
{
	struct person array[MAX];
	int size;
};

//添加
void addperson(book* abs)
{
	if (abs->size == MAX)
	{
		cout << "已经达到上限。" << endl;
	}
	else
	{
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->array[abs->size].name = name;
		cout << "请输入性别：" << endl;
		cout << "1.----man" << endl;
		cout << "2.----woman" << endl;
		int sex = 0;
		while(true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->array[abs->size].sex = sex;
				break;//输入1和2才跳出循环
			}
			cout << "输入有误，请重新输入！" << endl;
		}
		cout << "请输入年龄：" << endl;
		int age = 0;
		cin >> age;
		abs->array[abs->size].age = age;
		cout << "请输入电话号码：" << endl;
		string phone;
		cin >> phone;
		abs->array[abs->size].phone = phone;
		cout << "请输入家庭住址：" << endl;
		string addr;
		cin >> addr;
		abs->array[abs->size].addr = addr;

		//更新人数
		abs->size++;
		cout << "添加成功！" << endl;
		system("pause");
		system("cls");//清屏
	}
}

//显示联系人
void showperson(book* abs)
{
	//判断人数是否为0
	if (abs->size == 0)
	{
		cout << "当前没有联系人" << endl;
	}
	else
	{
		for (int i = 0; i < abs->size; i++)
		{
			cout << "姓名：" << abs->array[i].name << "\t";
			if( abs->array[i].sex==1)
			{
				cout << "性别：man\t";
			}
			else
			{
				cout << "性别：woman\t";
			}
			cout << "年龄：" << abs->array[i].age << "\t";
			cout << "电话：" << abs->array[i].phone << "\t";
			cout << "住址：" << abs->array[i].addr << "\t";
		}

	}
	system("pause");
	system("cls");
}

//删除联系人
int isexist(book* abs, string name)
{
	for (int i = 0; i < abs->size; i++)
	{
		if (abs->array[i].name == name)
		{
			return i;
		}
	}
	return -1;
}
void deleteperson(book* abs)
{
	cout << "请输入希望删除的联系人" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		for (int i = ret; i < abs->size; i++)
		{
			//数据前移，相当于删除
			abs->array[i] = abs->array[i + 1];

		}
		//更新人数
		abs->size--;
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

//查找联系人
void findperson(book* abs)
{
	cout << "请输入您希望查找的联系人" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		cout << "姓名：" << abs->array[ret].name << "\t";
		cout << "年龄：" << abs->array[ret].age << "\t";
		cout << "电话：" << abs->array[ret].phone << "\t";
		cout << "住址：" << abs->array[ret].addr << "\t";
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

void modifyperson(book* abs)
{
	cout << "请输入希望修改的联系人" << endl;
	string name;
	cin >> name;
	int ret = isexist(abs, name);
	if (ret != -1)
	{
		int choice = 0;
		cout << "请输入你希望改变的部分" << endl;
		cout << "1.姓名" << endl;
		cout << "2.性别" << endl;
		cout << "3.年龄" << endl;
		cout << "4.电话号码" << endl;
		cout << "5.住址" << endl;
		cin >> choice;
		if(choice==1)
		{
			string name;
			cin >> name;
			abs->array[ret].name = name;
		}
		else if(choice==2)
		{
			int sex;
			cin >> sex;
			abs->array[ret].sex = sex;
		}
		else if(choice==3)
		{
			int age;
			cin >> age;
			abs->array[ret].age = age;
		}
		else if(choice==4)
		{
			string phone;
			cin >> phone;
			abs->array[ret].phone = phone;
		}
		else if(choice==5)
		{
			string addr;
			cin >> addr;
			abs->array[ret].addr = addr;
		}
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

void clearperson(book* abs)
{
	abs -> size = 0;
	cout << "已清空" << endl;
	system("pause");
	system("cls");
}

//主程序
int main()
{
	book abs;
	abs.size = 0;//初始化

	int select = 0;
	while (true)
	{
		showmenu();
		cin >> select;
		switch (select)
		{
		case 1:
			addperson(&abs);
			break;
		case 2:
			showperson(&abs);
			break;
		case 3:
			deleteperson(&abs);
			break;
		case 4:
			findperson(&abs);
			break;
		case 5:
			modifyperson(&abs);
			break;
		case 6:
			clearperson(&abs);
			break;
		case 0:
			cout<<"欢迎下次使用！" << endl;
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}