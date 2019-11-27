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
string user_name = "пользователь N";
int qual = 32;
int qual_ch = 8;

void menu_choice();

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int checkdigit()
{
	while (true)
	{
		int value;
		// вводим число, которое хотим представить в двоичной форме
		cin >> value; // число целое
		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			cout << "Недопустимое заданное число. Введите число правильно" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
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

	for (int number_of_bit = 0; number_of_bit < qual; number_of_bit++) // номер бита для сдвига, сравниваем номер бита с допустимым значением диапазона массива, добавляем 1 после каждой итерации
	{
		result = dig & (1U << number_of_bit); // производим сдвиг числа и записываем бит в переменную
		revers_array[number_of_bit] = result; // записываем в массив полученное значение 
	}
	for (int i = qual - 1; i >= 0; i--)
	{
		if (revers_array[i] == 0 and counter == false) // проверяем выводим бит является ли значащим и вместе с ним равен ли параметр ЛОЖЬ. Необходимо для того, чтобы найти значащие биты и выделить их цветом
		{
			cout << revers_array[i]; // вывод значения бита
		}
		else
		{
			counter = true; // устанавливаем в истину, как только получили первый значащий разряд
			SetColor(14, 7); // устанавливаем цвет шрифта в желтый
			cout << revers_array[i]; //вывод значения бита
		}
	}
	SetColor(0, 7);
}
void ch_digit(int digit)
{
	vector<int> revers_array(qual_ch);
	bool result;
	bool counter = false;

	for (int number_of_bit = 0; number_of_bit < qual_ch; number_of_bit++) // номер бита для сдвига, сравниваем номер бита с допустимым значением диапазона массива, добавляем 1 после каждой итерации
	{
		result = digit & (1U << number_of_bit); // производим сдвиг числа и записываем бит в переменную
		revers_array[number_of_bit] = result; // записываем в массив полученное значение 
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

int checkparam() // функция проверки выбранного действия
{
	int par;
	char value[256]; // переменная, которая хранит выбранное значение
	cin >> value; // вводим выбранное значение 
	if (strlen(value) == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case 'y': // если соглашаемся
			par = 1;
			return par;
			break;
		case 'n': // если отказываемся
			par = 0;
			return par;
			break;
		default: // если число не подходит ни к одному из
			cout << "Значение введено неверно. Введите заново" << endl;
			checkparam();
			break;
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		checkparam();
	}
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
	cout << "Регистрация завершена, поздравляем!" << endl;
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
	cout << "Вход" << endl;
	cout << endl << "Введите имя пользователя: ";
	cin >> user_name;
	if (c != user_name)
	{
		cout << "Пользователь не найден. Попробуйте ввести еще раз" << endl;
		system("pause");
		sign();
	}
	fin >> c;
	cout << "Введите пароль: ";
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
		cout << endl << "Вход успешно выполнен!" << endl;
		t_reg = 1;
	}
	else
	{
		cout << endl << "Пароль не совпадает. Попробуйте ввести еще раз" << endl;
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
		cout << "Похоже, вы не произвели вход. Настоятельно рекомендуем это сделать?" << endl;
		cout << "Перейти в раздел вход? (y/n) ";
		if (checkparam() == 1)
			sign();
	}
	cout << "Приветствую тебя, " << user_name << "! Рад тебя видеть, проходи, присаживайся." << endl << endl;
	cout << "Эту программу написал студент группы 9894 Леушкин Сергей. Кстати, в памяти моего компьютера номер моей группы выглядит как: ";
	digit();
	cout << ", а Фамилия как ";
	second_name();
	cout << endl;
	system("pause");

	return;
}
void print_array(vector<int> arr)
{
	cout << endl << " Матрица " << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}
void fill_random_mat(vector<int>& arr) // функция для рандомного заполнения матрицы в зависимости от его размерности
{
	srand(time(0));
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i] = rand() % 20; // рандомим значения кратные 20
	}
}
void fill_mat(vector<int>& arr) // функция для ручного заполнения матрицы в зависимости от размерности
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << "arr[" << i << "]= ";
		arr[i] = checkdigit();
	}
}
void fill_mat_via_file(vector<int>& tab_2)
{
	ifstream in("input.txt"); // объявляем потоковую переменную и задаем название текстового файла. Он должен находится в каталоге исходного кода

	if (in.is_open()) //Если открытие файла прошло успешно
	{
		//Вначале посчитаем сколько чисел в файле
		int count = 0; // число чисел в файле
		int temp; //Временная переменная

		//Считаем маcсив из файла
		for (int i = 0; i < tab_2.size(); i++)
			in >> tab_2[i];
		in.close(); //под конец закроем файла
	}
	else
	{
		//Если открытие файла прошло не успешно
		cout << "Файл не найден." << endl;
		cout << "Файл читается из каталога исходного кода. Закиньте файл туда и следуйте дальнейшим указаниям " << endl;
		system("pause");
		fill_mat_via_file(tab_2);
	}

}

void choosefill(vector<int>& arr) // функция выбора заполнения матрицы
{
	int m;
	char value[256]; // переменная, которая хранит выбранное значение
	cin >> value; // считываем выбранное значение
	if (strlen(value) == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case '1': // рандомное заполнение
			fill_random_mat(arr);
			print_array(arr);
			break;

		case '2': // ручное заполнение
			fill_mat(arr);
			print_array(arr);
			break;
		case '3': // заполнение через текстовый файл
			fill_mat_via_file(arr);
			print_array(arr);
			break;
		default: // если число не подходит ни к одному из
			cout << "Число введено неверно. Введите заново" << endl;
			choosefill(arr);
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		choosefill(arr);
	}
}
void work_array()
{
	system("cls");
	vector<int> arr;
	int n;
	cout << "__Работа с целочисленным массивом__" << endl << endl;
	cout << "Введите размерность массива (положительное число арабскими цифрами - пример: 10, 3, 5): ";
	n = checkdigit();
	arr.resize(n);
	cout << "Как вы хотите заполнить данный массив:" << endl;
	cout << "1 - Значения элементов будут заданы рандомно (кратны 20)" << endl;
	cout << "2 - Самостоятельно заполнить значения элементов массива" << endl;
	cout << "3 - Загрузить массив с помощью текстового файла (размерность массива в файле должна совпадать с указанной Вами размерностью)" << endl << endl;
	cout << "Введите номер одного из вариантов: ";

	choosefill(arr); // функция для выбора варианта заполнения массива


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
		cout << right << "__МЕНЮ__" << endl;
		SetColor(5, 7);
		cout << "Регистрация" << endl;
		SetColor(0, 7);
		cout << "Вход" << endl;
		cout << "Приветствие" << endl;
		cout << "Работа с целочисленными массивами" << endl;
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		menu_choice();

	}
	if (m_count == 1)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Регистрация" << endl;
		SetColor(5, 7);
		cout << "Вход" << endl;
		SetColor(0, 7);
		cout << "Приветствие" << endl;
		cout << "Работа с целочисленными массивами" << endl;
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		menu_choice();

	}
	if (m_count == 2)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		SetColor(5, 7);
		cout << "Приветствие" << endl;
		SetColor(0, 7);
		cout << "Работа с целочисленными массивами" << endl;
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		menu_choice();

	}
	if (m_count == 3)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		cout << "Приветствие" << endl;
		SetColor(5, 7);
		cout << "Работа с целочисленными массивами" << endl;
		SetColor(0, 7);
		cout << "Флаг" << endl;
		cout << "Выход" << endl;
		menu_choice();

	}
	if (m_count == 4)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		cout << "Приветствие" << endl;
		cout << "Работа с целочисленными массивами" << endl;
		SetColor(5, 7);
		cout << "Флаг" << endl;
		SetColor(0, 7);
		cout << "Выход" << endl;
		menu_choice();

	}
	if (m_count == 5)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Регистрация" << endl;
		cout << "Вход" << endl;
		cout << "Приветствие" << endl;
		cout << "Работа с целочисленными массивами" << endl;
		cout << "Флаг" << endl;
		SetColor(5, 7);
		cout << "Выход" << endl;
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
		case 0x48: // стрелка вверх
			m_count--;
			if (m_count < 0) m_count = 0;
			menu();
			break;

		case 0x50: // стрелка вниз
			m_count++;
			if (m_count > 5) m_count = 5;
			menu();
			break;
		case 0xD: // подтвердить
			conf_val();
			break;
		default:
			menu_choice();
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		m_count--;
		if (m_count < 0) m_count = 0;
		menu();
		break;

	case 0x50: // стрелка вниз
		m_count++;
		if (m_count > 5) m_count = 5;
		menu();
		break;
	case 0xD: // подтвердить
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
	
	cout << "Всего доброго!." << endl;

	return 0;
}