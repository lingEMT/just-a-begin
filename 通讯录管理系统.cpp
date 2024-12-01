//��װ������ʾ�ý���    �� void showMenu()
//��main�����е��÷�װ�õĺ��� 
#include<iostream>
#include<string>
using namespace std;

#define MAX 1000

void showMenu()
{
	cout << "******************************" << endl;
	cout << "*****\t" << "1�������ϵ��\t " << "*****" << endl;
	cout << "*****\t" << "2����ʾ��ϵ��\t " << "*****" << endl;
	cout << "*****\t" << "3��ɾ����ϵ��\t " << "*****" << endl;
	cout << "*****\t" << "4��������ϵ��\t " << "*****" << endl;
	cout << "*****\t" << "5���޸���ϵ��\t " << "*****" << endl;
	cout << "*****\t" << "6�������ϵ��\t " << "*****" << endl;
	cout << "*****\t" << "0���˳�ͨѶ¼\t " << "*****" << endl;
	cout << "******************************" << endl;
}

//��ϵ�˽ṹ��:
struct Contact
{
	string m_Name; //����
	int m_Sex; //�Ա�
	int m_Age; //����
	string m_Phone; //�绰����
	string m_Addr; //��ͥסַ
};

struct Adressbooks
{
	//ͨѶ¼�б������ϵ������
	struct Contact contactArray[MAX];

	//ͨѶ¼�е�ǰ��¼��ϵ�˵ĸ���
	int m_Size;
};

//1�������ϵ��
void addContact(Adressbooks *abs)
{
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӡ�" << endl;
		return;
	}
	else
	{
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->contactArray[abs->m_Size].m_Name = name;
		//�Ա�
		int sex;
		cout << "�������Ա�(0��Ů 1����)" << endl;
		while (1)
		{
			cin >> sex;
			if (sex == 0 || sex == 1)
			{
				abs->contactArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "����������������룺" << endl;
		}
		//����
		int age;
		cout << "���������䣺" << endl;
		cin >> age;
		abs->contactArray[abs->m_Size].m_Age = age;
		//�绰����
		string phone;
		cout << "������绰���룺" << endl;
		cin >> phone;
		abs->contactArray[abs->m_Size].m_Phone = phone;
		//��ͥסַ
		string address;
		cout << "�������ͥסַ��" << endl;
		cin >> address;
		abs->contactArray[abs->m_Size].m_Addr = address;

		//����ͨѶ¼����
		abs->m_Size++;

		cout << "��ӳɹ�!" << endl;
	}
}

//2����ʾ��ϵ��
void showContact(Adressbooks* abs)
{
	if (abs->m_Size == 0)
	{
		cout << "δ�����ϵ��" << endl;
		return;
	}
	else
	{
		cout << "Ϊ����ʾ��������ϵ�ˣ�" << endl;
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "������" << abs->contactArray[i].m_Name << "\t";
			cout << "�Ա�" << (abs->contactArray[i].m_Sex == 0 ? "Ů" : "��") << "\t";
			cout << "���䣺" << abs->contactArray[i].m_Age << "\t";
			cout << "�绰��" << abs->contactArray[i].m_Phone << "\t";
			cout << "סַ��" << abs->contactArray[i].m_Addr << endl;
		}
	}
}

//�������Ƿ����
int isExist(Adressbooks* abs , string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (name == abs->contactArray[i].m_Name)
			return i;
	}
	return -1;
}

//3��ɾ����ϵ��
void deleteContact(Adressbooks* abs,int i)
{
	
	for (; i < abs->m_Size; i++)
	{
		abs->contactArray[i] = abs->contactArray[i + 1];
	}
	abs->m_Size--;
	cout << "ɾ���ɹ���" << endl;
}

//4��������ϵ��
void findContact(Adressbooks* abs, int i)
{
	cout << "������" << abs->contactArray[i].m_Name << "\t";
	cout << "�Ա�" << (abs->contactArray[i].m_Sex == 0 ? "Ů" : "��") << "\t";
	cout << "���䣺" << abs->contactArray[i].m_Age << "\t";
	cout << "�绰��" << abs->contactArray[i].m_Phone << "\t";
	cout << "סַ��" << abs->contactArray[i].m_Addr << endl;
}

//5���޸���ϵ��
void modifyContact(Adressbooks* abs,int i)
{
	//����
	string name;
	cout << "�������޸ĺ�������� " << endl;
	cin >> name;
	abs->contactArray[i].m_Name = name;
	//�Ա�
	int sex;
	cout << "�������޸ĺ���Ա�(0��Ů 1����)�� " << endl;
	while (1)
	{
		cin >> sex;
		if (sex == 0 || sex == 1)
		{
			abs->contactArray[i].m_Sex = sex;
			break;
		}
		cout << "����������������룺 " << endl;
	}
	//����
	int age;
	cout << "�������޸ĺ�����䣺 " << endl;
	cin >> age;
	abs->contactArray[i].m_Age = age;
	//�绰����
	string phone;
	cout << "�������޸ĺ�ĵ绰���룺 " << endl;
	cin >> phone;
	abs->contactArray[i].m_Phone = phone;
	//��ͥסַ
	string address;
	cout << "�������޸ĺ�ļ�ͥסַ�� " << endl;
	cin >> address;
	abs->contactArray[i].m_Addr = address;

	cout << "�޸ĳɹ���" << endl;
}

//6�������ϵ��
void cleanContact(Adressbooks* abs)
{
	int i = 0;
	cout << "��ȷ���Ƿ����������ϵ��(0��ȡ�� 1��ȷ��)" << endl;
	cin >> i;
	if (i == 0)
	{
		system("cls");
		return;
	}
	else
	{
		abs->m_Size = 0;
		cout << "��ǰͨѶ¼����գ�" << endl;
	}
	system("pause");
	system("cls");
}

int main()
{
	//����ͨѶ¼�ṹ�����
	Adressbooks abs;
	//��ʼ��ͨѶ¼��ǰ��Ա����
	abs.m_Size = 0;

	while (true)
	{
		showMenu();

		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1: //1�������ϵ��
			addContact(&abs);
			system("pause");
			system("cls");
			break;
		case 2: //2����ʾ��ϵ��
			showContact(&abs);
			system("pause");
			system("cls");
			break;
		case 3: //3��ɾ����ϵ��
		{
			string name;
			cout << "����������Ҫɾ������ϵ�ˣ�";
			cin >> name;
			int num = isExist(&abs, name);
			if (num == -1)
				cout << "δ�ҵ�����ϵ��" << endl;
			else
				deleteContact(&abs, num);
			system("pause");
			system("cls");
			break;
		}
		case 4: //4��������ϵ��
		{
			string name;
			cout << "����������Ҫ���ҵ���ϵ�ˣ�" << endl;
			cin >> name;
			int num = isExist(&abs, name);
			if (num == -1)
				cout << "δ�ҵ�����ϵ��" << endl;
			else
				findContact(&abs, num);
			system("pause");
			system("cls");
			break;
		}
		case 5: //5���޸���ϵ��
		{
			string name;
			cout << "����������Ҫ�޸ĵ���ϵ�ˣ�" << endl;
			cin >> name;
			int num = isExist(&abs, name);
			if (num == -1)
				cout << "δ�ҵ�����ϵ��" << endl;
			else
				modifyContact(&abs,num);
			system("pause");
			system("cls");
			break;
		}
		case 6: //6�������ϵ��
			cleanContact(&abs);
			break;
		case 0: //0���˳�ͨѶ¼
			cout << "����Ϊ���ر�ͨѶ¼����ӭ�´�ʹ�á�" << endl;
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