#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>
using namespace std;

int charToNum(char);
bool DimArr(int&);
bool GetFile(int*&);
void sortinfo(int&, int, int*&);

class datetime
{
	public:
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;
	void Out();
	void NextDate(int& i, int n, int*& arr, int key);
	void PrevDate(int& i, int n, int*& arr);
	void SysTime();
};

void datetime::SysTime()
{
	auto const time = chrono::system_clock::now();
	time_t seconds = chrono::system_clock::to_time_t(time);

	stringstream ss;
	ss << ctime(&seconds);
	string sysDate = ss.str();

	if (charToNum(sysDate[8]) != 404) day = charToNum(sysDate[8]);
	else day = 0;
	day = day * 10 + charToNum(sysDate[9]);

	if (sysDate[4] == 'J')
	{
		if (sysDate[5] == 'a') month = 1;
		else
		{
			if (sysDate[6] == 'n') month = 6;
			else month = 7;
		}
	}
	else if (sysDate[4] == 'F') month = 2;
	else if (sysDate[4] == 'M')
	{
		if (sysDate[6] == 'r') month = 3;
		else month = 5;
	}
	else if (sysDate[4] == 'A')
	{
		if (sysDate[5] == 'p') month = 4;
		else month = 8;
	}
	else if (sysDate[4] == 'S') month = 9;
	else if (sysDate[4] == 'O') month = 10;
	else if (sysDate[4] == 'N') month = 11;
	else if (sysDate[4] == 'D') month = 12;

	year = charToNum(sysDate[20]) * 10;
	year = (year + charToNum(sysDate[21])) * 10;
	year = (year + charToNum(sysDate[22])) * 10;
	year += charToNum(sysDate[23]);

	hour = charToNum(sysDate[11]) * 10;
	hour += charToNum(sysDate[12]);

	minute = charToNum(sysDate[14]) * 10;
	minute += charToNum(sysDate[15]);

	second = charToNum(sysDate[17]) * 10;
	second += charToNum(sysDate[18]);
}

void datetime::Out()
{
	cout << "Дата: " << day << "." << month << "." << year << " Время: " << hour << ":" << minute << ":" << second;
}

void datetime::NextDate(int& i, int n, int*& arr, int key)
{
	datetime temp;
	if (key == 1)
	{
		i = i + 6;
		if (i < n)
		{
			cout << " - ";
			day = arr[i];
			month = arr[i + 1];
			year = arr[i + 2];
			hour = arr[i + 3];
			minute = arr[i + 4];
			second = arr[i + 5];
			Out();
		}
	}
	if (key == 2)
	{
		temp.day = arr[i];
		temp.month = arr[i + 1];
		temp.year = arr[i + 2];
		temp.hour = arr[i + 3];
		temp.minute = arr[i + 4];
		temp.second = arr[i + 5];
		i = i + 6;
		if (i < n)
		{
			day = arr[i];
			month = arr[i + 1];
			year = arr[i + 2];
			hour = arr[i + 3];
			minute = arr[i + 4];
			second = arr[i + 5];
			if (temp.year < year || temp.year > year)
			{
				temp.Out();
				cout << " - ";
				Out();
				cout << endl;
			}
		}
	}
}

void datetime::PrevDate(int& i, int n, int*& arr)
{
	if (i - 6 != 0)
	{
		i = i - 12;
		cout << " - ";
		day = arr[i];
		month = arr[i + 1];
		year = arr[i + 2];
		hour = arr[i + 3];
		minute = arr[i + 4];
		second = arr[i + 5];
		i = i + 12;
		Out();
	}
}

class timedelta
{
	public:
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;

	void Out();
	void minus(datetime t1, datetime t2);
	datetime timePlus(datetime t1);
	void DeltaPlusDelta(timedelta d);
};

void timedelta::minus(datetime t1, datetime t2)
{
	second = t1.second - t2.second;
	minute = t1.minute - t2.minute;
	hour = t1.hour - t2.hour;
	day = t1.day - t2.day;
	month = t1.month - t2.month;
	year = t1.year - t2.year;
}

datetime timedelta::timePlus(datetime t1)
{
	t1.second -= second;
	t1.minute -= minute;
	t1.hour -= hour;
	t1.day -= day;
	t1.month -= month;
	t1.year -= year;
	return t1;
}

void timedelta::DeltaPlusDelta(timedelta t2)
{
	second += t2.second;
	minute += t2.minute;
	hour += t2.hour;
	day += t2.day;
	month += t2.month;
	year += t2.year;
}

void timedelta::Out()
{
	cout << "Дата: " << day << "." << month << "." << year << " Время: " << hour << ":" << minute << ":" << second;
}

int main()
{
	setlocale(LC_ALL, "ru");
	datetime data;
	datetime d1, d2;
	timedelta delta, t2;
	int n = 0, i = 0;
	DimArr(n);
	int* arr = new int[n];
	GetFile(arr);
	int key = 0;
	do
	{
		cout << "1) Вывод информации в формате:" << endl
			<< "2) Дата системы" << endl
			<< "0) Выход" << endl;
		cout << endl << "Выбирите действие: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			i = 0;
			sortinfo(i, n, arr);
			cout << endl;
			break;
		case 2:
			data.SysTime();
			data.Out();
			cout << "\n\n";
			break;
		default:
			if (key != 0)
			{
				cout << "Такого действия нет !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
}

int charToNum(char str)
{
	if (str == '0') return 0;
	else if (str == '1') return 1;
	else if (str == '2') return 2;
	else if (str == '3') return 3;
	else if (str == '4') return 4;
	else if (str == '5') return 5;
	else if (str == '6') return 6;
	else if (str == '7') return 7;
	else if (str == '8') return 8;
	else if (str == '9') return 9;

	return 404;
}


void sortinfo(int& i, int n, int*& arr)
{
	datetime data;
	while (i < n)
	{
		data.NextDate(i, n, arr, 2);
	}
}

bool DimArr(int& n)
{
	datetime data;
	int temp;
	ifstream F("Date.txt");
	if (!F)
	{
		cout << "Файл не найден" << endl;
		return false;
	}
	while (F >> temp)
	{
		n++;
	}
	F.close();
	return true;
}

bool GetFile(int*& arr)
{
	datetime data;
	int temp, i = 0;
	ifstream F("Date.txt");
	if (!F)
	{
		cout << "Файл не найден" << endl;
		return false;
	}
	while (F >> temp)
	{
		arr[i] = temp;
		i++;
	}
	F.close();
	return true;
}
