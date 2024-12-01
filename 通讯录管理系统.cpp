//封装函数显示该界面    如 void showMenu()
//在main函数中调用封装好的函数 
#include<iostream>
#include<string>
using namespace std;

#define MAX 1000

void showMenu()
{
	cout << "******************************" << endl;
	cout << "*****\t" << "1、添加联系人\t " << "*****" << endl;
	cout << "*****\t" << "2、显示联系人\t " << "*****" << endl;
	cout << "*****\t" << "3、删除联系人\t " << "*****" << endl;
	cout << "*****\t" << "4、查找联系人\t " << "*****" << endl;
	cout << "*****\t" << "5、修改联系人\t " << "*****" << endl;
	cout << "*****\t" << "6、清空联系人\t " << "*****" << endl;
	cout << "*****\t" << "0、退出通讯录\t " << "*****" << endl;
	cout << "******************************" << endl;
}

//联系人结构体:
struct Contact
{
	string m_Name; //名字
	int m_Sex; //性别
	int m_Age; //年龄
	string m_Phone; //电话号码
	string m_Addr; //家庭住址
};

struct Adressbooks
{
	//通讯录中保存的联系人数组
	struct Contact contactArray[MAX];

	//通讯录中当前记录联系人的个数
	int m_Size;
};

//1、添加联系人
void addContact(Adressbooks *abs)
{
	if (abs->m_Size == MAX)
	{
		cout << "通讯录已满，无法添加。" << endl;
		return;
	}
	else
	{
		//名字
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->contactArray[abs->m_Size].m_Name = name;
		//性别
		int sex;
		cout << "请输入性别：(0—女 1—男)" << endl;
		while (1)
		{
			cin >> sex;
			if (sex == 0 || sex == 1)
			{
				abs->contactArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入错误，请重新输入：" << endl;
		}
		//年龄
		int age;
		cout << "请输入年龄：" << endl;
		cin >> age;
		abs->contactArray[abs->m_Size].m_Age = age;
		//电话号码
		string phone;
		cout << "请输入电话号码：" << endl;
		cin >> phone;
		abs->contactArray[abs->m_Size].m_Phone = phone;
		//家庭住址
		string address;
		cout << "请输入家庭住址：" << endl;
		cin >> address;
		abs->contactArray[abs->m_Size].m_Addr = address;

		//更新通讯录人数
		abs->m_Size++;

		cout << "添加成功!" << endl;
	}
}

//2、显示联系人
void showContact(Adressbooks* abs)
{
	if (abs->m_Size == 0)
	{
		cout << "未添加联系人" << endl;
		return;
	}
	else
	{
		cout << "为您显示出所有联系人：" << endl;
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "姓名：" << abs->contactArray[i].m_Name << "\t";
			cout << "性别：" << (abs->contactArray[i].m_Sex == 0 ? "女" : "男") << "\t";
			cout << "年龄：" << abs->contactArray[i].m_Age << "\t";
			cout << "电话：" << abs->contactArray[i].m_Phone << "\t";
			cout << "住址：" << abs->contactArray[i].m_Addr << endl;
		}
	}
}

//检测此人是否存在
int isExist(Adressbooks* abs , string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (name == abs->contactArray[i].m_Name)
			return i;
	}
	return -1;
}

//3、删除联系人
void deleteContact(Adressbooks* abs,int i)
{
	
	for (; i < abs->m_Size; i++)
	{
		abs->contactArray[i] = abs->contactArray[i + 1];
	}
	abs->m_Size--;
	cout << "删除成功！" << endl;
}

//4、查找联系人
void findContact(Adressbooks* abs, int i)
{
	cout << "姓名：" << abs->contactArray[i].m_Name << "\t";
	cout << "性别：" << (abs->contactArray[i].m_Sex == 0 ? "女" : "男") << "\t";
	cout << "年龄：" << abs->contactArray[i].m_Age << "\t";
	cout << "电话：" << abs->contactArray[i].m_Phone << "\t";
	cout << "住址：" << abs->contactArray[i].m_Addr << endl;
}

//5、修改联系人
void modifyContact(Adressbooks* abs,int i)
{
	//名字
	string name;
	cout << "请输入修改后的姓名： " << endl;
	cin >> name;
	abs->contactArray[i].m_Name = name;
	//性别
	int sex;
	cout << "请输入修改后的性别(0—女 1—男)： " << endl;
	while (1)
	{
		cin >> sex;
		if (sex == 0 || sex == 1)
		{
			abs->contactArray[i].m_Sex = sex;
			break;
		}
		cout << "输入错误，请重新输入： " << endl;
	}
	//年龄
	int age;
	cout << "请输入修改后的年龄： " << endl;
	cin >> age;
	abs->contactArray[i].m_Age = age;
	//电话号码
	string phone;
	cout << "请输入修改后的电话号码： " << endl;
	cin >> phone;
	abs->contactArray[i].m_Phone = phone;
	//家庭住址
	string address;
	cout << "请输入修改后的家庭住址： " << endl;
	cin >> address;
	abs->contactArray[i].m_Addr = address;

	cout << "修改成功！" << endl;
}

//6、清空联系人
void cleanContact(Adressbooks* abs)
{
	int i = 0;
	cout << "请确认是否清空所有联系人(0—取消 1—确认)" << endl;
	cin >> i;
	if (i == 0)
	{
		system("cls");
		return;
	}
	else
	{
		abs->m_Size = 0;
		cout << "当前通讯录已清空！" << endl;
	}
	system("pause");
	system("cls");
}

int main()
{
	//创建通讯录结构体变量
	Adressbooks abs;
	//初始化通讯录当前人员个数
	abs.m_Size = 0;

	while (true)
	{
		showMenu();

		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1: //1、添加联系人
			addContact(&abs);
			system("pause");
			system("cls");
			break;
		case 2: //2、显示联系人
			showContact(&abs);
			system("pause");
			system("cls");
			break;
		case 3: //3、删除联系人
		{
			string name;
			cout << "请输入您想要删除的联系人：";
			cin >> name;
			int num = isExist(&abs, name);
			if (num == -1)
				cout << "未找到该联系人" << endl;
			else
				deleteContact(&abs, num);
			system("pause");
			system("cls");
			break;
		}
		case 4: //4、查找联系人
		{
			string name;
			cout << "请输入您想要查找的联系人：" << endl;
			cin >> name;
			int num = isExist(&abs, name);
			if (num == -1)
				cout << "未找到该联系人" << endl;
			else
				findContact(&abs, num);
			system("pause");
			system("cls");
			break;
		}
		case 5: //5、修改联系人
		{
			string name;
			cout << "请输入您想要修改的联系人：" << endl;
			cin >> name;
			int num = isExist(&abs, name);
			if (num == -1)
				cout << "未找到该联系人" << endl;
			else
				modifyContact(&abs,num);
			system("pause");
			system("cls");
			break;
		}
		case 6: //6、清空联系人
			cleanContact(&abs);
			break;
		case 0: //0、退出通讯录
			cout << "正在为您关闭通讯录，欢迎下次使用。" << endl;
			system("pause");
			return 0;
		default:
			return 0;
			break;
		}
	}

	system("pause");
	return 0;
}