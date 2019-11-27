#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
const int NotUsed = system("color 70");

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
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
	cout << "Флаг Панамы (Вариант 18)" << endl << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i <= 14 and j >= 5)
			{
				SetColor(4, 4); // красный правый куб
				cout << flag[i][j] << " " << '\t';
			}
			else if (i >= 15 and j <= 4)
			{
				SetColor(1, 1);// синий левый куб
				cout << flag[i][j] << " " << '\t';
			}
			else if (((j == 1 or j == 3) and (i >= 6 and i <= 8)) or ((i >= 2 and i <= 12) and j == 2))
			{
				SetColor(1, 1); // синий звездочка
				cout << flag[i][j] << " " << '\t';
			}
			else if (((j == 6 or j == 8) and (i >= 21 and i <= 23)) or ((i >= 17 and i <= 27) and j == 7))
			{
				SetColor(4, 4); // красный звездочка
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

void print_ok()
{
	system("cls");
	cout << "OK";
}

void registration()
{
	system("cls");
	ofstream fout;
	string s1;
	cout << "Приветствую" << endl;
	cout << "Введите имя пользователя: ";
	fout.open("data.txt");
	getline(cin, s1);
	fout << s1;
	fout << '\n';
	s1.clear();
	cout << "Введите пароль: ";
	getline(cin, s1);
	fout << s1;
	fout << '\n';
	fout.close();
	system("pause");
}

void sign()
{
	fstream fin;
	string c;
	fin.open("data.txt", ios::in);
	fin.seekg(0, ios::beg);
	fin >> c;
	if (c == "Sam")
		cout << "1 ok" << endl;
	else
	{
		cout << "Некорректно" << endl;
	}
	fin.seekg(-6, ios::end);
	fin >> c;
	if (c == "Long")
		cout << "2 ok" << endl;
	else
	{
		cout << "Некорректно" << endl;
	}
	system("pause");
}
int menu_inter(int count)
{
	char c;
	system("cls");
	if (count == 0)
	{
		SetColor(5, 7);
		cout << "Меню" << endl;
		SetColor(0, 7);
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		c = _getch();
		if (c == 0x20)
		{
			print_ok();
			return 0;
		}
	}
	if (count == 1)
	{
		cout << "Меню" << endl;
		SetColor(5, 7);
		cout << "Регистрация" << endl;
		SetColor(0, 7);
		cout << "Вход" << endl;
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		c = _getch();
		if (c == 0x20)
		{
			registration();
			return 0;
		}
	}
	if (count == 2)
	{
		cout << "Меню" << endl;
		cout << "Регистрация" << endl;
		SetColor(5, 7);
		cout << "Вход" << endl;
		SetColor(0, 7);
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		c = _getch();
		if (c == 0x20)
		{
			sign();
			return 0;
		}
	}
	if (count == 3)
	{
		cout << "Меню" << endl;
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		SetColor(5, 7);
		cout << "Флаг" << endl;
		SetColor(0, 7);
		cout << "Выход" << endl;
		c = _getch();
		if (c == 0x20)
		{
			print_flag();
			return 0;
		}
	}
	if (count == 4)
	{
		cout << "Меню" << endl;
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		cout << "Флаг" << endl;
		SetColor(5, 7);
		cout << "Выход" << endl;
		SetColor(0, 7);
		c = _getch();
		if (c == 0x20)
		{
			print_ok();
			return 0;
		}
	}

}
int main(int argc, const char* argv[])
{
	setlocale(0, "");

	int count = 0;
	int param = 0;
	menu_inter(count);
	char c;
	

	int k1, k2;
	
	while(_getch() != 0x1B)
	{
		k1 = _getch();
		if (k1 == 0xE0 || k1 == 0x00)
		{
			k2 = _getch();
			switch (k2)
			{
			case 0x48: 
				count--;
				if (count < 0)
					count = 0;
				menu_inter(count);
				break;
			case 0x50:
				count++;
				if (count > 4)
					count = 4;
				menu_inter(count);
				break;
			}
		}
	}

	cout << "Всего доброго!." << endl;

	return 0;
}