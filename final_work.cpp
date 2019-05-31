/*
	Объект содержит информацию о местожитольстве студентов факультет: фамилия и имя студента,
	курс, группа, место проживания.
	Не доработана функция с удалением студента, поэтому в списке не должно быть студентов с одинаковым именем.
	Файл для тестирования в репозитории Students.txt
	Для удобства файлы сохранить в корне диска d
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "windows.h"
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

const int BUFF{ 100 };

int countN(ifstream &stream);

class Student
{
public:
	Student() : name("незаполнено"), course(0), group(0), home(new(nothrow)char[13])
	{
		if (!home) { cout << "Error"; exit(1); }
		strcpy(home, "незаполнено");
	//	cout << "---Стандартный конструктор---\n";
	}
	Student(const char* _name) : name(_name), course(0), group(0), home(0)
	{
	//		cout << "---Конструктор с одним параметром---\n";
	}
	Student(const char* _name, int _course, int _group, const char *_home) : name(_name), course(_course), group(_group), home(new (nothrow) char[strlen(_home) + 1])
	{
		if (!home)
		{
			cout << "Ошибка выделения памяти.";
			exit(0);
		}
		strcpy(home, _home);
		//	cout << "---Конструктор с параметрами---\n";
	}
	Student(const Student &other) : name(other.name), course(other.course), group(other.group), home(new (nothrow) char[strlen(other.home) + 1])
	{
		strcpy(home, other.home);
	//	cout << "---Копирующий конструктор---\n";
	}
	~Student()
	{
	//	cout << "---Деструктор---\n";
		delete[]home;
		home = nullptr;
	}
	string getName() const
	{
		return name;
	}
	int getCourse() const
	{
		return course;
	}
	int getGroup() const
	{
		return group;
	}
	char* getHome() const
	{
		return home;
	}
	friend ostream& operator << (ostream & stream, const Student& tmp)
	{
		stream << tmp.name << setw(25 - tmp.name.length()) << tmp.course << '\t' << tmp.group << '\t' << tmp.home << '\n';
		return stream;
	}
	friend istream& operator >> (istream & stream, Student& tmp)
	{
		char buff[BUFF];
		stream.getline(buff, 100);
		tmp.name = buff;
		stream >> tmp.course >> tmp.group;
		stream.ignore(1, '\n');
		stream.getline(buff, 100);
		tmp.home = new (nothrow) char[strlen(buff) + 1];
		if (!tmp.home)
		{
			cout << "Ошибка выделения памяти.";
			exit(0);
		}
		strcpy(tmp.home, buff);
		return stream;
	}
	Student& operator = (const Student& right) {
		this->name = right.name;
		this->course = right.course;
		this->group = right.group;
		this->home = new (nothrow) char[strlen(right.home) + 1];
		strcpy(home, right.home);
		return *this;
	}
	friend int getMaxCourse(Student *arr, int N)
	{
		int max = arr[0].course;
		for (int i = 0; i < N - 1; i++)
		{
			if (arr[i].course > arr[i + 1].course)
			{
				max = arr[i].course;
				swap(arr[i], arr[i + 1]);
			}
			else
				max = arr[i + 1].course;
		}
		return max;
	}
	friend int getMaxGroup(Student *arr, int N)
	{
		int max = arr[0].group;
		for (int i = 0; i < N - 1; i++)
		{
			if (arr[i].group > arr[i + 1].group)
			{
				max = arr[i].group;
				swap(arr[i], arr[i + 1]);
			}
			else
				max = arr[i + 1].group;
		}
		return max;
	}
	friend void editStudent(Student &edit)
	{
		int  tmp;
		char a;
		char buff[BUFF];
		cout << "\nРедактирование студента:\n1 - Изменить имя\n2 - Изменить курс\n3 - Изменить группу\n4 - Изменить место проживания\nq - Выход из редактирования\n";
		while (1) {
		tryAgain:
			cin >> a;
			switch (a)
			{
			case 'q':
				goto Exit;
				break;
			case '1':
				cout << "Текущее имя - " << edit.name << "\nВведите новое имя.Имя и фамилия через пробел\n";
				cin.ignore();
				cin.getline(buff, BUFF);
				edit.name = buff;
				goto tryAgain;
				break;
			case '2':
				cout << "Текущий курс - " << edit.course << "\nВведите новый курс\n";
				cin >> tmp;
				edit.course = tmp;
				goto tryAgain;
				break;
			case '3':
				cout << "Текущая группа - " << edit.group << "\nВведите новую группу\n";
				cin >> tmp;
				edit.group = tmp;
				goto tryAgain;
				break;
			case '4':
				cout << "Текущее место проживания - " << edit.home << "\nВведите новое место проживания\n";
				cin.ignore();
				cin.getline(buff, BUFF);
				edit.home = new (nothrow) char[strlen(buff) + 1];
				strcpy(edit.home, buff);
				edit.home[strlen(buff)] = '\0';
				goto tryAgain;
				break;
			default:
				cout << "Неверное значение. Введите заново\n";
				goto tryAgain;
				break;
			}
		Exit:
			break;
		}
	}
	friend void sortAlfabet(ofstream &list2,Student *arr, int N)
	{
		list2.open("d:\\Students.txt");
		if (!list2) { cout << "No file d:\\Students.txt"; system("pause"); }
		for (int i = 0; i < N - 1; i++)
		{
			int flag = 0;
			for (int j = 0; j < N - 1 - i; j++)
			{
				if (arr[j].getName() > arr[j+1].getName())
				{
					swap(arr[j], arr[j + 1]);
					flag = 1;
				}
			}
			if (!flag) break;
		}
		for (int i = 0; i < N; ++i)
		{
			list2 << arr[i];
		}
		cout << "Отсортировано\n";
		list2.close();
		
	}
	friend void getListOfHomes(ofstream &rez, Student *arr, int N)
	{
		char a;
		int c, g;
		cout << "0 - Проживающие в квартире\n1 - Проживающие в общежитии\n2 - Проживающие в доме\n";
		tryAgain:
		cin >> a;
		cout << "Введите курс и группу\n";
		cin >> c >> g;
		rez << "Имя Фамилия" << setw(14) << "\tКурс" << "\tГруппа" << "\tМесто проживания\n\n";
		switch (a)
		{
			case 'q':
				break;
			case '0':
				for (int i = 0; i < N; i++) {
					if (!strcmp(arr[i].home, "квартира"))
					{
						if(arr[i].course==c && arr[i].group==g)
						rez << arr[i];
					}
				}
				cout << "Готово\n";
				break;
			case '1':

				for (int i = 0; i < N; i++) {
					if (!strcmp(arr[i].home, "общежитие"))
					{
						if (arr[i].course == c && arr[i].group == g)
						rez << arr[i];
					}
				}
				cout << "Готово\n";
				break;
			case '2':

				for (int i = 0; i < N; i++) {
					if (!strcmp(arr[i].home, "дом"))
					{
						if (arr[i].course == c && arr[i].group == g)
						rez << arr[i];
					}
				}
				cout << "Готово\n";
				break;
			default:
				cout << "Неверное значение. Введите заново\n";
				goto tryAgain;
				break;
		}
	}
	friend void readStudents(ifstream&list, Student *arr, int N)
	{
		char* tmp = new (nothrow)char[255];
		if (!tmp) { cout << "Error"; exit(1); }
		string tmp2[5];
		char * writable = nullptr;
		for (int i = 0; i<N; i++)
		{
			list.getline(tmp, 255);
			char * ptr = strtok(tmp, " \t");
			int j = 0;
			while (ptr != NULL)                    
			{
				tmp2[j] = ptr;
			//	cout << tmp2[j] << '\n';
				j++;
				ptr = strtok(NULL, " \t");
				
			}
			writable = new(nothrow) char[tmp2[4].size() + 1];
			for (int k = 0; k < tmp2[4].size(); k++)
			{
				writable[k] = tmp2[4][k];
			}
			
			writable[tmp2[4].size()] = '\0';
			arr[i].name = tmp2[0] + " " + tmp2[1];
			arr[i].course = int(tmp2[2][0])-48;
			arr[i].group = int(tmp2[3][0])-48;
			strcpy(arr[i].home, writable);
			delete[]writable;
			writable = nullptr;
			if (list.eof()) break;
		}
		delete[] tmp;
		tmp = nullptr;
	}
	friend void menu(Student *arr, int N, ofstream &stream,ofstream &list2)
	{
		char a{ 0 };
		cout << "0 - Добавить студента\n1 - Удалить студента\n2 - Отсортировать по алфавиту\n3 - Получить список студентов с конкретным местом жительства\n4 - Получить справку о количестве студентов, проживающих в общежитии, в квартире, в доме\nq - для выхода\n";
		Again:
		cin >> a;
		switch (a)
		{
		case 'q':
			break;
		case '0':
			addStudent(list2, arr, N);
			goto Again;
			break;
		case '1':
			delStudent(list2, arr, N);
			goto Again;
			break;
		case '2':
			sortAlfabet(list2,arr, N);
			goto Again;
			break;
		case '3':
			getListOfHomes(stream, arr, N);
			stream << '\n';
			goto Again;
			break;
		case '4':
			certificaitOfStudents(stream, arr, N);
			stream << '\n';
			goto Again;
			break;
		default:
			cout << "Неверное значение, попробуйте заново\n";
			goto Again;
			break;
		}
	}
	friend int countQuantity(Student *arr, int N,int c, int g, const char*h)
	{
		int cnt = 0;
		for (int i = 0; i < N; ++i)
			if (arr[i].course == c && arr[i].group == g && !strcmp(arr[i].home,h))
				cnt++;
		return cnt;
	}
	friend int countQuantity(Student *arr, int N, int c, int g)
	{
		int cnt = 0;
		for (int i = 0; i < N; ++i)
			if (arr[i].course == c && arr[i].group == g)
				cnt++;
		return cnt;
	}
	friend void certificaitOfStudents(ofstream &rez, Student *arr, int N)
	{
		rez << "Курс	Группа	Общежитие	Квартира	Дом"<<'\n';
		for (int i = 1; i <= getMaxCourse(arr, N); ++i)
		{
			for (int j = 1; j <= getMaxGroup(arr,N); ++j)
			{
				if(countQuantity(arr,N,i,j))
				rez<< i << '\t'<<j<<'\t'<<countQuantity(arr,N,i,j,"общежитие") << "\t\t"<< countQuantity(arr, N, i, j, "квартира") << "\t\t"<< countQuantity(arr, N, i, j, "дом")<<"\n";
			}
		}
		cout << "Справка готова\n";
	}
	friend void addStudent(ofstream &list2,Student *&arr,int & N)
	{
		list2.open("d:\\Students.txt",ios_base::app);
		if (!list2) { cout << "No file d:\\Students.txt"; system("pause"); }
		N++;
		Student *tmp = new (nothrow) Student[N];
		for (int i = 0; i < N-1; ++i)
		{
			tmp[i] = arr[i];
		}
		editStudent(tmp[N - 1]);
		arr = new (nothrow) Student[N];
		for (int i = 0; i < N; ++i)
		{
			arr[i] = tmp[i];
		}
		list2 << arr[N-1];
		list2.close();
	}
	friend void delStudent(ofstream &list2, Student *&arr, int & N)
	{
		list2.open("d:\\Students.txt");	
		if (!list2) { cout << "No file d:\\Students.txt"; system("pause"); }
		string str;
		cout<<"Введите имя студента, которого хотите удалить\n";
		cin.ignore();
		getline(std::cin,str);
		int i=0;
		N--;
		Student *tmp = new (nothrow) Student[N];
		for (int i = 0,j = 0; i < N; ++j)
		{
			if (arr[j].name != str)
			{
				tmp[i] = arr[j];
				i++;
			}
		}

		delete[]arr;
		arr = nullptr;
		arr = new (nothrow) Student[N];
		for (int i = 0; i < N; ++i)
		{
			arr[i] = tmp[i];
		}
		for (int i = 0; i < N; ++i)
		{
			list2 << arr[i];
		}
		list2.close();

	}
private:
	string name;
	int course;
	int group;
	char* home;
};

int main()
{
	int N = 14;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream list;
	ifstream listForCount("d:\\Students.txt");
	if (!listForCount) { cout << "No file d:\\Students.txt"; system("pause"); }
	ofstream list2;
	ofstream rez("d:\\rez.txt");
	if (!rez) { cout << "No file d:\\Students.txt"; system("pause"); }
	int count = 0;
	while (listForCount.ignore((numeric_limits<streamsize>::max)(), '\n')) count++;
	listForCount.close();
	N = count-1; cout << N<<"\n";
	list.open("d:\\Students.txt");
	if (!list) { cout << "No file d:\\Students.txt"; system("pause"); }
	Student *Students = new (nothrow) Student[N];
	readStudents(list, Students, N);
	menu(Students, N, rez,list2);
	delete[]Students;
	Students = nullptr; 
	list.close();
	rez.close();
	system("pause");
}






int countN(ifstream& stream)
{
	int cnt = 0;
	char *str = new char[1024];
	while (!stream.eof())
	{
		stream.getline(str, 1024);
		cnt++;
	}
	return cnt;
}
