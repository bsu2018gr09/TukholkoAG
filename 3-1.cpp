//(7-8.) В строке найти все слова чётной длины, заканчивающиеся на заданную букву. 
//Вывести их на экран, и вставить после них заданную подстроку, например ”**”..
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<clocale>
using namespace std;
const int MAX = 500;
void printStr(char *s, int N) {
	for (int i = 0; i < N; ++i)
		cout << s[i];
}
void wordsMass(char * str, char **mass) {
	char *p = str;
	char str1[] = ",.; \t";
	for (int i = 0; *p; ++i) {
		p += strspn(p, str1);
		int len = strcspn(p, str1);
		if (len == 0) break;
		mass[i] = new(nothrow) char[len + 1];
		strncpy(mass[i], p, len);
		mass[i][len] = '\0';
		p += len;

	}
}
void printEvenLenWords(char ** massOfWords, int k, char *Pstr, char letter) {
	for (int i = 0; i < k; ++i) {
		if (strlen(massOfWords[i]) % 2 == 0)
			if (massOfWords[i][strlen(massOfWords[i]) - 1] == letter)
				cout << massOfWords[i] << Pstr << '\n';
	}
}
int WordsCount(char* tmp)
{
	int k = 0;
	char * p = strtok(tmp, " ,.;");
	while (p != nullptr){
		p = strtok(NULL, " ,.");
		k++;}
	return k;
}
void initStr(char *&str) {
	char buf[MAX];
	cin.getline(buf, MAX);
	str = new(nothrow) char[strlen(buf) + 1];
	if (!str) { cout<<" Error!"; exit(1); }
	strcpy(str, buf);
}
void freeMemory(char **&s, int k) {
	for (int i = 0; i < k; ++i) {
		delete s[i];
		s[i]=nullptr;
	}
	delete[] s;
	s = nullptr;
}
int main() {
	setlocale(LC_ALL, "RUS");
	int k = 0;
	char*str=nullptr,*Pstr = nullptr;
	char letter;
	cout << "Введите строку\n";
	initStr(str);
	char * tmp = new(nothrow) char[strlen(str)+1];
	strcpy(tmp,str);
	k = WordsCount(tmp);
	char ** massOfWords = new(nothrow) char*[k];
	cout << "Введите подстроку\n";
	initStr(Pstr);
	cout << "Введите букву конца слова\n";
	cin >> letter;
	wordsMass(str, massOfWords);
	cout << "Слова четной длины, заканчивающиеся на letter:\n";
	printEvenLenWords(massOfWords,k,Pstr,letter);
	freeMemory(massOfWords,k);
	delete [] str;
	delete[] Pstr;
	str = nullptr;
	Pstr = nullptr;
	system("pause");
	return 0;
}
