// Интерактивное меню с пунктами (Регистрация, Вход, Приветствие, Работа с целочисленным массивом, Флаг)
/*
	В регистрации - ввод логина и пароля и дальнейшая запись в файл
	В входе - ввод логина и пароля и дальнейшая проверка его с данными после регистрации (отдельная проверка по логину и по паролю - по заданию)
	Приветствие - просто текст, который ориентирован на вводимый логин пользователя. Если пользователь не регистрировался, в приветствии будет обозначен, как "пользователь N". Дальше обычное
	приветствие, где номер группы выводится в двоичной форме, так же и происходит с фамилией - по заданию
	Работа с целочисленным массивом - построена на векторе, пользователю предоставляется выбор заполнения массива - самостоятельно, рандомно, через файл, а также предоставляется выбор из 5 сортировок Bubble, Shaker, Comb, Insert, Quick. 
	После сортировки идет поиск 15 чисел Фибоначчи (если размерность меньше, то предел - размерность).
	Для этих чисел создан отдельный вектор arr_fib(). После этого выводится среднее значение в массиве, медиана массива и мода.
	В Флаге - флаги выполнены на векторах - флаг Панамы и флаг РФ. На разных ПК выглядят они по-разному.
	Программа - по большей степени не оптимизирована и больше похожа на костыль.
*/
 
#include <iostream> // для ввода/вывода в консоль
#include <Windows.h> // для изменения цвета в консоли
#include <conio.h> // для меню (считывание символов напрямую из консоли без использования буфера и echo-вывода (getch(void))
#include <vector> // для массивов
#include <string> // для строковых переменных
#include <fstream> // для потокового ввода/вывода из/в файл/а
#include <ctime> // для рандома
#include <chrono> // для подсчета времени выполнения сортировки

using namespace std; // пространство имен std - для быстроты не стал каждой приписывать
const int NotUsed = system("color 70"); // изменения цвета консоли в серый 

int m_count = 0; // значения для меню - это значение изменяется при нажатии стрелок вверх или вниз
int t_reg = 0; // параметр, который определяет прошел ли пользователь регистрацию перед выполнением приветствия
string user_name = "пользователь N"; // если пользователь отказывается от регистрации, то имени присваивается эта строка
int qual = 32; // количество бит, выделяемое на инт значение
int qual_ch = 8; // количество бит, выделяемое на чар значение

void menu_choice(); // прототип меню

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

int checkdigit() // проверка числа на корректность ввода (отрицательные значения принимает)
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

void digit() // для получения номера группы в двоичной форме
{
	vector<int> revers_array(qual); // создаем вектор с необходимым размером
	int dig = 9894; // указываем значению номер группы
	bool result; // переменная, на вход получает каждый бит числа и заносит его в массив
	bool counter = false; // параметр, который позволяет включить цвет для вывода значащих разрядов

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
	SetColor(0, 7); // возвращаем цвет на серый
}
void ch_digit(int digit) // для получения букв фамилии в двоичной форме
{
	vector<int> revers_array(qual_ch); // создаем вектор с необходимым размером
	bool result; // переменная, на вход получает каждый бит числа и заносит его в массив

	for (int number_of_bit = 0; number_of_bit < qual_ch; number_of_bit++) // номер бита для сдвига, сравниваем номер бита с допустимым значением диапазона массива, добавляем 1 после каждой итерации
	{
		result = digit & (1U << number_of_bit); // производим сдвиг числа и записываем бит в переменную
		revers_array[number_of_bit] = result; // записываем в массив полученное значение 
	}
	for (int i = qual_ch - 1; i >= 0; i--) // выводим
		cout << revers_array[i];
	cout << " ";
}

void second_name() // для получения фамилии в двоичной форме
{
	char ch; // инициализируем переменную чар
	string s_names = "Leushkin"; // задаем строке фамилии
	vector<char> s_name; // инициализируем вектор для каждой буквы фамилии

	for (int i = 0; i < s_names.size(); i++)// цикл для записи букв в массив
		s_name.push_back(s_names[i]);
	for (int i = 0; i < s_name.size(); i++)// цикл для вывода каждой буквый фамилии в двоичной форме
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

void registration() // пункт меню - регистрация
{
	system("cls"); // очищаем консоль
	ofstream fout; // инициализируем поток
	string s1; // инициализируем строку 
	cout << "Приветствую" << endl;
	cout << "Введите имя пользователя: ";
	fout.open("data.txt"); // открываем файл для записи
	getline(cin, s1); // считываем строку
	fout << s1;
	fout << '\n';
	s1.clear(); // очищаем переменную
	cout << "Введите пароль: ";
	getline(cin, s1); // считываем строку
	fout << s1;
	fout << '\n';
	fout.close(); // закрываем файл после записи
	cout << "Регистрация завершена, поздравляем!" << endl;
	system("pause");
	menu_choice(); // возвращаемся в раздел меню
}

void sign() // пункт меню - вход
{
	system("cls"); // очищаем консоль
	fstream fin; // инициализируем входной поток
	string c; // инициализируем строку
	vector<char> password; // создаем вектор для пароля, что б при вводе можно было заменить вводимые символы на звездочки
	char ch;
	int param = 1; // параметр для проверки правильности ввода логина/пароля
	fin.open("data.txt", ios::in); // открываем поток для чтения
	fin.seekg(0, ios::beg); // переносим указатель на начало файла
	fin >> c; // считываем строку
	cout << "Вход" << endl; 
	cout << endl << "Введите имя пользователя: ";
	cin >> user_name;
	if (c != user_name) // проверяем на корректность ввода логина
	{
		cout << "Пользователь не найден. Попробуйте ввести еще раз" << endl;
		system("pause");
		sign(); // заново просим выполнить вход полностью
	}
	fin >> c; // считываем строку
	cout << "Введите пароль: ";
	while ((ch = _getch()) != '\r')// каждый вводимый символ меняем на "*" до подтверждения ввода - к сожалению удалить символ в момент ввода не получится
	{
		password.push_back(ch); // загоняем в массив
		_putch('*'); // ставим * 
	}
	for (int i = 0; i < c.size(); i++) // проверяем каждый символ строки и массива на корректность
	{
		if (c[i] != password[i])
		{
			param = 0;
			break;
		}
	}
	if (param == 1) // если успешно
	{
		cout << endl << "Вход успешно выполнен!" << endl;
		t_reg = 1;
	}
	else // иначе пароль не совпал
	{
		cout << endl << "Пароль не совпадает. Попробуйте ввести еще раз" << endl;
		system("pause");
		sign(); // заново просим выполнить вход полностью
	}
	fin.close(); // закрываем файл
	system("pause");
	menu_choice(); // возвращаемся в раздел меню
}

void say_hello() // Пункт меню - приветствие
{
	system("cls"); // очищаем консоль
	if (t_reg != 1) // есди вход не был выполнен, предлагаем зайти
	{
		cout << "Похоже, вы не произвели вход. Настоятельно рекомендуем это сделать?" << endl;
		cout << "Перейти в раздел вход? (y/n) ";
		if (checkparam() == 1) // если соглашается - входим
			sign();
	}
	cout << "Приветствую тебя, " << user_name << "! Рад тебя видеть, проходи, присаживайся." << endl << endl;
	cout << "Эту программу написал студент группы 9894 Леушкин Сергей. Кстати, в памяти моего компьютера номер моей группы выглядит как: ";
	digit(); // двоичный вывод номера группы
	cout << ", а Фамилия как ";
	second_name(); // двоичный вывод фамилии
	cout << endl;
	system("pause");
	
	menu_choice(); // возвращаемся в раздел меню
}
void print_array(vector<int> arr) // вывод массива
{
	cout << endl << "__Массив__" << endl;
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << " ";
	cout << endl;
}
void fill_random_mat(vector<int>& arr) // функция для рандомного заполнения матрицы в зависимости от его размерности
{
	srand(time(0));
	for (int i = 0; i < arr.size(); i++)
	{
		arr[i] = rand() % 50; // рандомим значения кратные 20
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

void choosefill(vector<int>& arr) // функция выбора заполнения массива
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

void swap(int* first_p, int* second_p) // смена переменных между собой
{
	int temp = *first_p;
	*first_p = *second_p;
	*second_p = temp;
}

void BubbleSort(vector<int>& arr) // пузырьковая сортировка
{
	int temp;
	for (int i = 0; i < arr.size() - 1; i++)
		for (int j = 0; j < arr.size() - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]); // меняем местами, если искомое значение больше следующего 
			}
}

void ShakerSort(vector<int>& arr) // шейкерная сортировка
{
	int i, j, k;
	int m = arr.size();
	for (i = 0; i < m;) {
		for (j = i + 1; j < m; j++) {
			if (arr[j] < arr[j - 1])
				swap(arr[j], arr[j - 1]);
		}
		m--;
		for (k = m - 1; k > i; k--) {
			if (arr[k] < arr[k - 1])
				swap(arr[k], arr[k - 1]);
		}
		i++;
	}
}

int getNextGap(int gap) // для Comb Sort
{
	// Shrink gap by Shrink factor 
	gap = (gap * 10) / 13;

	if (gap < 1)
		return 1;
	return gap;
}

void CombSort(vector<int>& arr) // сортировка комбинированием
{
	int gap = arr.size();

	// Initialize swapped as true to make sure that 
	// loop runs 
	bool swapped = true;

	// Keep running while gap is more than 1 and last 
	// iteration caused a swap 
	while (gap != 1 || swapped == true)
	{
		// Find next gap 
		gap = getNextGap(gap);

		// Initialize swapped as false so that we can 
		// check if swap happened or not 
		swapped = false;

		// Compare all elements with current gap 
		for (int i = 0; i < arr.size() - gap; i++)
		{
			if (arr[i] > arr[i + gap])
			{
				swap(arr[i], arr[i + gap]);
				swapped = true;
			}
		}
	}
}

void InsertSort(vector<int>& arr) // сортировка вставками
{
	// сортируем массив вставками --  insertion sort
	int min_value;	// переменная, принимающая минимальное значение минимальное значение
	int j = 0; // объявление переменной, котороая используется для выбора иного от i элемента массива
	for (int i = 1; i < arr.size(); i++)
	{
		min_value = arr[i]; // задаем текущему минимальному значению массива текущий элемент массива
		j = i - 1; // задаем значение j на 1 меньше, чем i, для того, чтобы работать с предыдушем элементом массива 
		while (j >= 0 and arr[j] > min_value) //пока текущий элемент меньше предыдущего и j не присвоилось
		{									// отрицательное значение, присваиваем последнему значению предыдущее 
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = min_value; // присваеваем следующему элементу минимальное значения массива
	}
}

int partition(vector<int> &arr, int low, int high) // для QuickSort
{
	int pivot = arr[high];    // pivot
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		//if current element is smaller than pivot, increment the low element
		//swap elements at i and j
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

void QuickSort(vector<int>& arr, int low, int high) // быстрая сортировка
{
	if (low < high)
	{
	//partition the array
		int pivot = partition(arr, low, high);

		//sort the sub arrays independently
		QuickSort(arr, low, pivot - 1);
		QuickSort(arr, pivot + 1, high);
	}
}

void choosesort(vector<int>& arr) // выбор сортировки
{
	chrono::steady_clock sc;   // create an object of `steady_clock` class
	double seconds; // переменная, которая хранит в себе время исполнения события

	int m;
	char value[256]; // переменная, которая хранит выбранное значение
	cin >> value; // считываем выбранное значение

	if (strlen(value) == 1) // проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям дальше
	{
		switch (value[0]) // проверям, взяв первый символ переменной value
		{
		case '1': // сортировка пузырьком
		{
			auto start = sc.now();     // устанавливаем начало отсчета времени события
			BubbleSort(arr);
			auto end = sc.now();       // устанавливаем конец отсчета времени события
			auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
			print_array(arr);
			cout << "Время, затраченное на сортировку пузырьком: " << time_span.count() << " секунд" << endl;
			break;
		}
		case '2': // сортировка шейкерная
		{
			auto start_1 = sc.now();     // устанавливаем начало отсчета времени события
			ShakerSort(arr);
			auto end_1 = sc.now();       // устанавливаем конец отсчета времени события
			auto time_span_1 = static_cast<chrono::duration<double>>(end_1 - start_1);   // высчитываем время, затраченное на событие
			print_array(arr);
			cout << "Время, затраченное на шейкерную сортировку: " << time_span_1.count() << " секунд" << endl;
			break;
		}
		case '3': // сортировка комбинированием
		{
			auto start_2 = sc.now();     // устанавливаем начало отсчета времени события
			CombSort(arr);
			auto end_2 = sc.now();       // устанавливаем конец отсчета времени события
			auto time_span_2 = static_cast<chrono::duration<double>>(end_2 - start_2);   // высчитываем время, затраченное на событие
			print_array(arr);
			cout << "Время, затраченное на сортировку комбинированием: " << time_span_2.count() << " секунд" << endl;
			break;
		}
		case '4': // сортировка вставками
		{
			auto start_3 = sc.now();     // устанавливаем начало отсчета времени события
			InsertSort(arr);
			auto end_3 = sc.now();       // устанавливаем конец отсчета времени события
			auto time_span_3 = static_cast<chrono::duration<double>>(end_3 - start_3);   // высчитываем время, затраченное на событие
			print_array(arr);
			cout << "Время, затраченное на сортировку вставками: " << time_span_3.count() << " секунд" << endl;
			break;
		}
		case '5': // сортировка быстрая
		{
			auto start_4 = sc.now();     // устанавливаем начало отсчета времени события
			QuickSort(arr, 0, arr.size() - 1);
			auto end_4 = sc.now();       // устанавливаем конец отсчета времени события
			auto time_span_4 = static_cast<chrono::duration<double>>(end_4 - start_4);   // высчитываем время, затраченное на событие
			print_array(arr);
			cout << "Время, затраченное на быструю сортировку: " << time_span_4.count() << " секунд" << endl;
			break;
		}
		default: // если число не подходит ни к одному из
		{
			cout << "Число введено неверно. Введите заново" << endl;
			choosefill(arr);
			break;
		}
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		choosefill(arr);
	}
}
int fib(int digit) // поиск числа фибоначчи - "1" - если подходит, "0" - если не подходит
{
	int f1 = 1, f2 = 1, it = 2;
	while (f2 < digit) {
		int tmp = f2;
		f2 += f1;
		f1 = tmp;
		it++;
	}
	if (f2 == digit)
		return 1;
	else
		return -1;
}
void work_array() // Пункт меню - Работа с целочисленным массивом
{
	system("cls"); // очищаем консоль
	vector<int> arr; // инициализирование массива для чисел
	vector<int> arr_fib; // инициализирование массива для чисел Фибоначчи
	int size; // размерность для Фибоначчи
	int n; // размерность для массива
	int middle, middle_i, med, mod; // среднее значение, серединное значение, медиана, мода

	cout << "__Работа с целочисленным массивом__" << endl << endl;
	cout << "Введите размерность массива (положительное число арабскими цифрами - пример: 10, 3, 5): ";
	n = checkdigit(); // считываем проверяем значение
	arr.resize(n); // изменяем размерность массива
	cout << "Как Вы хотите заполнить данный массив:" << endl;
	cout << "1 - Значения элементов будут заданы рандомно (кратны 20)" << endl;
	cout << "2 - Самостоятельно заполнить значения элементов массива" << endl;
	cout << "3 - Загрузить массив с помощью текстового файла (размерность массива в файле должна совпадать с указанной Вами размерностью)" << endl << endl;
	cout << "Введите номер одного из вариантов: ";

	choosefill(arr); // функция для выбора варианта заполнения массива

	cout << "Какой сортировкой Вы хотите отсортировать данный массив:" << endl;
	cout << "1 - Bubble Sort" << endl;
	cout << "2 - Shaker Sort" << endl;
	cout << "3 - Comb Sort" << endl;
	cout << "4 - Insert Sort" << endl;
	cout << "5 - Quick Sort" << endl << endl;
	cout << "Введите номер одного из вариантов: ";

	choosesort(arr); // функция сортировки массива
	/// Фибоначчи
	if (arr.size() > 15) // если размер массива больше 15, ищем только из первых 15
		size = 15;
	else
		size = arr.size(); // меньше - прогоняем по всему размеру массива

	for (int i = 0; i < size; i++)
		if (fib(arr[i]) == 1)
		{
			arr_fib.push_back(arr[i]);
		}
	cout << endl << "Числа Фибоначчи, представленные в массиве";
	print_array(arr_fib); // выводим массив чисел Фибоначчи
	
	// среднее значение значений массива
	middle = (arr[0] + arr[arr.size() - 1]) / 2;
	cout << endl << "Среднее значение значений массива = " << middle;
	//медиана массива
	middle_i = arr.size() / 2;
	if (arr.size() % 2 == 0) // если четное - среднее между двумя средними , если нечетное - срединное значение
	{
		med = (arr[middle_i - 1] + arr[middle_i + 1]) / 2;
	}
	else
		med = arr[middle_i];
	cout << endl << "Медиана массива = " << med;

	// мода массива
	int max = arr[0];
	int cmax = 0;
	int rmax = 0;
	for (int i = 0; i < arr.size(); i++) 
	{
		if (cmax > rmax) 
		{
			rmax = cmax;
			max = arr[i - 1];
		}
		cmax = 0;
		for (int j = i; j < arr.size(); j++)
			if (arr[j] == arr[i])
				cmax++;
	}
	//Вывод результатов поиска
	cout << endl << "Мода массива = " << max << " Встречается в массиве " << rmax << " раз" << endl;

	system("pause");
	return;
}

void print_flag() // вывод флага
{
	system("cls"); //очищаем консоль
	unsigned int n = 10; // размерность столбцов
	unsigned int m = 30; // размерность строк
	vector<vector <int> > flag(m); // инициализация вектора
	for (int i = 0; i < m; i++) // создаем матрицу
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
	SetColor(0, 7); // возващаем цвет

	cout << endl << "Флаг Российской Федерации " << endl << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i <= 10)
			{
				SetColor(15, 15);// ,белая полоса
				cout << flag[i][j] << " " << '\t';
			}
			else if (i <= 20 and i >= 11)
			{
				SetColor(1, 1);// синия полоса
				cout << flag[i][j] << " " << '\t';
			}
			else
			{
				SetColor(4, 4);// красная полоса
				cout << flag[i][j] << " " << '\t';
			}
		}
		cout << endl;
	}
	SetColor(0, 7);
}

void conf_val() // выбор после подтверждения в зависимости от значения текущего
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

void menu() // меню
{
	system("cls"); // очищаем консоль

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

void menu_choice() // в зависимости от стрелок изменяем меню
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
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
	setlocale(0, ""); // локализация

	menu(); // меню
	
	cout << "Всего доброго!." << endl;

	return 0;
}