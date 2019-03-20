//(7-8.) В строке найти все слова чётной длины, заканчивающиеся на заданную букву. 
//Вывести их на экран, и вставить после них заданную подстроку, например ”**”..
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<clocale>
using namespace std;
const int MAX = 255;
int k = 0; // количество слов
void printStr(char *s,int N) {
	for(int i = 0; i < N; ++i)
		cout<<s[i];
}
int wordsMass(char * str, char **mass) {
	char *p=str;
	char str1[] = ",.; \t";
	for (int i = 0; *p; ++i) {
		p+=strspn(p,str1);
		int len=strcspn(p,str1);
		if (len == 0) break;
		mass[i] = new(nothrow) char[len+1];
		strncpy(mass[i],p,len);
		mass[i][len]='\0';
		k++;
		p+=len;
		
	}
	return k;
}
int main() {
	setlocale(LC_ALL, "RUS");
	const int N{100};
	char buf[MAX],buf2[MAX];
	char *massOfWords[N];
	char letter;
	cout<<"Введите строку\n";
	cin.getline(buf, MAX);
	char * str = new(nothrow) char[strlen(buf) + 1];
	strcpy(str, buf);
	cout<<"Введите букву конца слова\n";
	cin >> letter;
	cout<<"Введите подстроку\n";
	cin>>buf2;
	char * Podstroka = new(nothrow) char[strlen(buf2) + 1];
	strcpy(Podstroka, buf2);
	wordsMass(str,massOfWords);
	cout<<"Слова четной длины, заканчивающиеся на letter:\n";
	for (int i = 0; i < k; ++i) {
		if(strlen(massOfWords[i])%2==0)
			if (massOfWords[i][strlen(massOfWords[i])-1]==letter)
				cout<<massOfWords[i]<<Podstroka<<'\n';
	}
	system("pause");
	return 0;
}