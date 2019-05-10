//	В строке удалить слова, заключённые в круглые скобки. Отсортировать строки по количеству удалённых слов.
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<iostream>
#include<fstream>
#include<clocale>
using namespace std;
const int N = 1000000;
const int MAX = 255;
void giveMemory2(char **&ptr, int N, int M) {
	ptr = new(nothrow) char*[N];
	if (!ptr)
	{
		cout << "Error!\n";
		exit(0);
	}
	for (int i = 0; i < N; ++i) {
		ptr[i] = new(nothrow) char[M];
		if (!ptr[i])
		{
			cout << "Error!\n";
			exit(0);
		}
	}
}
int WordsCount(char* tmp)
{
	int k = 0;
	char * p = strtok(tmp, ")");
	while (p != nullptr) {
		p = strtok(NULL, ")");
		k++;
	}
	return k-1;
}
void initStr(char *&str) {
	char buf[MAX];
	cin.getline(buf, MAX);
	str = new(nothrow) char[strlen(buf) + 1];
	if (!str) { cout << " Error!"; exit(1); }
	strcpy(str, buf);
}
void freeMemory2(char **&s, int k) {
	for (int i = 0; i < k; ++i) {
		delete s[i];
		s[i] = nullptr;
	}
	delete[] s;
	s = nullptr;
}
void delWords(char **&strings,int cnt) {
	char str1[] = "(";
	char str2[] = ")";
	char*p = new(nothrow) char[MAX]; if (!p) {cout << "Error";exit(1);}
	char*start = new(nothrow) char[MAX]; if (!start) {cout << "Error";exit(1);}
	char*end = new(nothrow) char[MAX]; if (!end) {cout << "Error";exit(1);}
	char*tmp = new(nothrow) char[MAX]; if (!tmp) {cout << "Error";exit(1);}
	for (int j = 0; j<cnt; ++j) {
		strcpy(tmp, *(strings + j));
		int k = WordsCount(tmp);
		if (!k)j++;
		if (j>cnt)break;
		for (int i = 0; i < k; ++i) {
			strcpy(p, *(strings + j));
			strcpy(start, p);
			strcpy(end, p);
			end += strcspn(p, str2) + 1;
			start[strcspn(p, str1)] = '\0';
			strcat(start, end);
			strcpy(*(strings + j), start);
		}
	}
}
void sortRows(char **&strings, int cnt) {
	char*tmp = new(nothrow) char[MAX]; if (!tmp) { cout << "Error";exit(1); }
	char*tmp2 = new(nothrow) char[MAX]; if (!tmp) { cout << "Error";exit(1); }
	for (int i = 0; i < cnt - 1; ++i) {
		int flag = 0;
		for (int j = 0; j < cnt - 1 - i; ++j) {
			strcpy(tmp, *(strings + j));
			strcpy(tmp2, *(strings + j + 1));
			if (WordsCount(tmp) < WordsCount(tmp2)) {
			swap(*(strings + j), *(strings + j + 1));
			flag = 1;
			}
		}
		if (!flag) {
			break;
		}
	}
}
int main()
{
	char **strings = nullptr;
	giveMemory2(strings,N,MAX);
	ifstream in("d:\\date1.txt");
	ofstream out("d:\\date2.txt");
	if (!in) { cout << "No file d:\\date1.txt. Can't open\n"; exit(1); }
	if (!out) { cout << "No file d:\\date2.txt. Can't create\n"; exit(1); }
	int	cnt = 0;
	while(1){//получили массив строк
		in.getline(*(strings + cnt), MAX);
		if (in.fail()) in.clear();
		cnt++;
		if (in.eof()) break;
	}
	sortRows(strings, cnt);
	delWords(strings,cnt);
	for (int i = 0; i < cnt; ++i) {//записываем в файл
		out<<*(strings + i);
		out << '\n';
	}
	freeMemory2(strings,cnt);
	in.close();//закрыли файл
	out.close();//закрыли файл
	cout<<"Done!\n";
	system("pause");м
}
