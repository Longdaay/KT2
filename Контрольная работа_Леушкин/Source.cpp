#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
const int NotUsed = system("color 70");

int m_count = 0;
int t_reg = 0;
string user_name = "������������ N";
int qual = 32;
int qual_ch = 8;

void menu_choice();

void SetColor(int text, int bg) //������� ����� �����, ������ �� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int checkdigit()
{
	while (true)
	{
		int value;
		// ������ �����, ������� ����� ����������� � �������� �����
		cin >> value; // ����� �����
		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			cout << "������������ �������� �����. ������� ����� ���������" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
			return value;
		}
	}
}

void digit()
{
	vector<int> revers_array(qual);
	int dig = 9894;
	bool result;
	bool counter = false;

	for (int number_of_bit = 0; number_of_bit < qual; number_of_bit++) // ����� ���� ��� ������, ���������� ����� ���� � ���������� ��������� ��������� �������, ��������� 1 ����� ������ ��������
	{
		result = dig & (1U << number_of_bit); // ���������� ����� ����� � ���������� ��� � ����������
		revers_array[number_of_bit] = result; // ���������� � ������ ���������� �������� 
	}
	for (int i = qual - 1; i >= 0; i--)
	{
		if (revers_array[i] == 0 and counter == false) // ��������� ������� ��� �������� �� �������� � ������ � ��� ����� �� �������� ����. ���������� ��� ����, ����� ����� �������� ���� � �������� �� ������
		{
			cout << revers_array[i]; // ����� �������� ����
		}
		else
		{
			counter = true; // ������������� � ������, ��� ������ �������� ������ �������� ������
			SetColor(14, 7); // ������������� ���� ������ � ������
			cout << revers_array[i]; //����� �������� ����
		}
	}
	SetColor(0, 7);
}
void ch_digit(int digit)
{
	vector<int> revers_array(qual_ch);
	bool result;
	bool counter = false;

	for (int number_of_bit = 0; number_of_bit < qual_ch; number_of_bit++) // ����� ���� ��� ������, ���������� ����� ���� � ���������� ��������� ��������� �������, ��������� 1 ����� ������ ��������
	{
		result = digit & (1U << number_of_bit); // ���������� ����� ����� � ���������� ��� � ����������
		revers_array[number_of_bit] = result; // ���������� � ������ ���������� �������� 
	}
	for (int i = qual_ch - 1; i >= 0; i--)
		cout << revers_array[i];
	cout << " ";
}

void second_name()
{
	char ch;
	string s_names = "Leushkin";
	vector<char> s_name;

	for (int i = 0; i < s_names.size(); i++)
		s_name.push_back(s_names[i]);
	for (int i = 0; i < s_name.size(); i++)
		ch_digit((int)(s_name[i]));

}

int checkparam() // ������� �������� ���������� ��������
{
	int par;
	char value[256]; // ����������, ������� ������ ��������� ��������
	cin >> value; // ������ ��������� �������� 
	if (strlen(value) == 1) // ��������� ���������� ��������� ��������. ���� �����, �� ������ ������ ��� ���, ����� �������� ������
	{
		switch (value[0]) // ��������, ���� ������ ������ ���������� value
		{
		case 'y': // ���� �����������
			par = 1;
			return par;
			break;
		case 'n': // ���� ������������
			par = 0;
			return par;
			break;
		default: // ���� ����� �� �������� �� � ������ ��
			cout << "�������� ������� �������. ������� ������" << endl;
			checkparam();
			break;
		}
	}
	else // ���� ������� �������� ������ ������������
	{
		cout << "���������� ������ ���� ������. ���������� ������ ������" << endl;
		checkparam();
	}
}

void registration()
{
	system("cls");
	ofstream fout;
	string s1;
	cout << "�����������" << endl;
	cout << "������� ��� ������������: ";
	fout.open("data.txt");
	getline(cin, s1);
	fout << s1;
	fout << '\n';
	s1.clear();
	cout << "������� ������: ";
	getline(cin, s1);
	fout << s1;
	fout << '\n';
	fout.close();
	cout << "����������� ���������, �����������!" << endl;
	system("pause");
	menu_choice();
}

void sign()
{
	system("cls");
	fstream fin;
	string c;
	vector<char> password;
	char ch;
	int param = 1;
	fin.open("data.txt", ios::in);
	fin.seekg(0, ios::beg);
	fin >> c;
	cout << "����" << endl;
	cout << endl << "������� ��� ������������: ";
	cin >> user_name;
	if (c != user_name)
	{
		cout << "������������ �� ������. ���������� ������ ��� ���" << endl;
		system("pause");
		sign();
	}
	fin >> c;
	cout << "������� ������: ";
	while ((ch = _getch()) != '\r')
	{
		password.push_back(ch);
		_putch('*');
	}
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i] != password[i])
		{
			param = 0;
			break;
		}
	}
	if (param == 1)
	{
		cout << endl << "���� ������� ��������!" << endl;
		t_reg = 1;
	}
	else
	{
		cout << endl << "������ �� ���������. ���������� ������ ��� ���" << endl;
		system("pause");
		sign();
	}
	fin.close();
	system("pause");
}

void say_hello()
{
	system("cls");
	if (t_reg != 1)
	{
		cout << "������, �� �� ��������� ����. ������������ ����������� ��� �������?" << endl;
		cout << "������� � ������ ����? (y/n) ";
		if (checkparam() == 1)
			sign();
	}
	cout << "����������� ����, " << user_name << "! ��� ���� ������, �������, ������������." << endl << endl;
	cout << "��� ��������� ������� ������� ������ 9894 ������� ������. ������, � ������ ����� ���������� ����� ���� ������ �������� ���: ";
	digit();
	cout << ", � ������� ��� ";
	second_name();
	cout << endl;
	system("pause");

	return;
}
void print_array(vector<int> arr)
{
	cout << endl << " ������� " << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}
void fill_random_mat(vector<int>& arr) // ������� ��� ���������� ���������� ������� � ����������� �� ��� �����������
{
	srand(time(0));
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i] = rand() % 20; // �������� �������� ������� 20
	}
}
void fill_mat(vector<int>& arr) // ������� ��� ������� ���������� ������� � ����������� �� �����������
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << "arr[" << i << "]= ";
		arr[i] = checkdigit();
	}
}
void fill_mat_via_file(vector<int>& tab_2)
{
	ifstream in("input.txt"); // ��������� ��������� ���������� � ������ �������� ���������� �����. �� ������ ��������� � �������� ��������� ����

	if (in.is_open()) //���� �������� ����� ������ �������
	{
		//������� ��������� ������� ����� � �����
		int count = 0; // ����� ����� � �����
		int temp; //��������� ����������

		//������� ��c��� �� �����
		for (int i = 0; i < tab_2.size(); i++)
			in >> tab_2[i];
		in.close(); //��� ����� ������� �����
	}
	else
	{
		//���� �������� ����� ������ �� �������
		cout << "���� �� ������." << endl;
		cout << "���� �������� �� �������� ��������� ����. �������� ���� ���� � �������� ���������� ��������� " << endl;
		system("pause");
		fill_mat_via_file(tab_2);
	}

}

void choosefill(vector<int>& arr) // ������� ������ ���������� �������
{
	int m;
	char value[256]; // ����������, ������� ������ ��������� ��������
	cin >> value; // ��������� ��������� ��������
	if (strlen(value) == 1) // ��������� ���������� ��������� ��������. ���� �����, �� ������ ������ ��� ���, ����� �������� ������
	{
		switch (value[0]) // ��������, ���� ������ ������ ���������� value
		{
		case '1': // ��������� ����������
			fill_random_mat(arr);
			print_array(arr);
			break;

		case '2': // ������ ����������
			fill_mat(arr);
			print_array(arr);
			break;
		case '3': // ���������� ����� ��������� ����
			fill_mat_via_file(arr);
			print_array(arr);
			break;
		default: // ���� ����� �� �������� �� � ������ ��
			cout << "����� ������� �������. ������� ������" << endl;
			choosefill(arr);
		}
	}
	else // ���� ������� �������� ������ ������������
	{
		cout << "���������� ������ ���� ������. ���������� ������ ������" << endl;
		choosefill(arr);
	}
}
void work_array()
{
	system("cls");
	vector<int> arr;
	int n;
	cout << "__������ � ������������� ��������__" << endl << endl;
	cout << "������� ����������� ������� (������������� ����� ��������� ������� - ������: 10, 3, 5): ";
	n = checkdigit();
	arr.resize(n);
	cout << "��� �� ������ ��������� ������ ������:" << endl;
	cout << "1 - �������� ��������� ����� ������ �������� (������ 20)" << endl;
	cout << "2 - �������������� ��������� �������� ��������� �������" << endl;
	cout << "3 - ��������� ������ � ������� ���������� ����� (����������� ������� � ����� ������ ��������� � ��������� ���� ������������)" << endl << endl;
	cout << "������� ����� ������ �� ���������: ";

	choosefill(arr); // ������� ��� ������ �������� ���������� �������


	system("pause");
	return;
}

void print_flag()
{
	system("cls");
	unsigned int n = 10;
	unsigned int m = 30;
	vector<vector <int> > flag(m);
	for (int i = 0; i < m; i++)
	{
		flag[i].resize(n);
		for (int j = 0; j < n; j++)
		{
			flag[i][j] = 0;
		}
	}
	SetColor(0, 7);
	cout << "���� ������ (������� 18)" << endl << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i <= 14 and j >= 5)
			{
				SetColor(4, 4); // ������� ������ ���
				cout << flag[i][j] << " " << '\t';
			}
			else if (i >= 15 and j <= 4)
			{
				SetColor(1, 1);// ����� ����� ���
				cout << flag[i][j] << " " << '\t';
			}
			else if (((j == 1 or j == 3) and (i >= 6 and i <= 8)) or ((i >= 2 and i <= 12) and j == 2))
			{
				SetColor(1, 1); // ����� ���������
				cout << flag[i][j] << " " << '\t';
			}
			else if (((j == 6 or j == 8) and (i >= 21 and i <= 23)) or ((i >= 17 and i <= 27) and j == 7))
			{
				SetColor(4, 4); // ������� ���������
				cout << flag[i][j] << " " << '\t';
			}
			else
			{
				SetColor(7, 7);
				cout << flag[i][j] << " " << '\t';
			}


		}
		cout << endl;
	}
	SetColor(0, 7);
}

void conf_val()
{
	switch (m_count)
	{
	case 0:
		registration();
		break;
	case 1:
		sign();
		break;
	case 2:
		say_hello();
		break;
	case 3:
		work_array();
		break;
	case 4:
		print_flag();
		break;
	case 5:
		SetColor(7, 7);
		exit(0);
		break;
	default:
		break;
	}
}

void menu()
{
	system("cls");

	if (m_count == 0)
	{
		
		cout.width(15);
		cout << right << "__����__" << endl;
		SetColor(5, 7);
		cout << "�����������" << endl;
		SetColor(0, 7);
		cout << "����" << endl;
		cout << "�����������" << endl;
		cout << "������ � �������������� ���������" << endl;
		cout << "����" << endl;
		cout << "�����" << endl;
		menu_choice();

	}
	if (m_count == 1)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "�����������" << endl;
		SetColor(5, 7);
		cout << "����" << endl;
		SetColor(0, 7);
		cout << "�����������" << endl;
		cout << "������ � �������������� ���������" << endl;
		cout << "����" << endl;
		cout << "�����" << endl;
		menu_choice();

	}
	if (m_count == 2)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "�����������" << endl;
		cout << "����" << endl;
		SetColor(5, 7);
		cout << "�����������" << endl;
		SetColor(0, 7);
		cout << "������ � �������������� ���������" << endl;
		cout << "����" << endl;
		cout << "�����" << endl;
		menu_choice();

	}
	if (m_count == 3)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "�����������" << endl;
		cout << "����" << endl;
		cout << "�����������" << endl;
		SetColor(5, 7);
		cout << "������ � �������������� ���������" << endl;
		SetColor(0, 7);
		cout << "����" << endl;
		cout << "�����" << endl;
		menu_choice();

	}
	if (m_count == 4)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "�����������" << endl;
		cout << "����" << endl;
		cout << "�����������" << endl;
		cout << "������ � �������������� ���������" << endl;
		SetColor(5, 7);
		cout << "����" << endl;
		SetColor(0, 7);
		cout << "�����" << endl;
		menu_choice();

	}
	if (m_count == 5)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "�����������" << endl;
		cout << "����" << endl;
		cout << "�����������" << endl;
		cout << "������ � �������������� ���������" << endl;
		cout << "����" << endl;
		SetColor(5, 7);
		cout << "�����" << endl;
		SetColor(0, 7);
		menu_choice();

	}
}

void menu_choice()
{
	int k1;
	k1 = _getch();
	if (k1 == 0xE0)
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			m_count--;
			if (m_count < 0) m_count = 0;
			menu();
			break;

		case 0x50: // ������� ����
			m_count++;
			if (m_count > 5) m_count = 5;
			menu();
			break;
		case 0xD: // �����������
			conf_val();
			break;
		default:
			menu_choice();
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		m_count--;
		if (m_count < 0) m_count = 0;
		menu();
		break;

	case 0x50: // ������� ����
		m_count++;
		if (m_count > 5) m_count = 5;
		menu();
		break;
	case 0xD: // �����������
		conf_val();
		break;
	default:
		menu_choice();
	}
}

int main()
{
	setlocale(0, "");

	menu();
	
	cout << "����� �������!." << endl;

	return 0;
}