//1.2.Положительные элементы массива А(N) переставить в конец массива, сохраняя порядок следования. 
//Отрицательные элементы расположить в порядке убывания. Дополнительный массив не использовать.
#include<iostream>
#include<time.h>
using namespace std;
int* giveMemory(int N) {
	int * pA = nullptr;
	pA = new(nothrow) int[N];
	if (!pA) {
		cout << "error";
		exit(0);
	}
	return pA;
}
void freeMemory(int *pA) {
	delete[] pA;
	pA = nullptr;
}
void initArr(int *arr, int n) {
	for (int i = 0; i < n; ++i) {
		*(arr + i) = i;
	}

}

void printArr(int *arr, int n) {
	for (int i = 0; i < n; ++i) {
		cout << *(arr + i) << " ";
	}

}void randomInit(int *arr, int n) {
	srand(time(0));
	for (int i = 0; i <n; ++i)
	{
		*(arr + i) = rand() % (10 - (-10) + 1) + (-10);
	}
}
void positivToTheEnd(int *pA, int N) {
	int cnt = 0;
	for (int i = N - 1; i >= 0; --i) {            //переставляет положительные элементы в конец не меняя порядок
		if (*(pA + i) > 0) {
			swap(*(pA + i), *(pA + N - 1 - cnt));
			cnt++;
		}
	}
}
void sortNegativ(int *pA, int N) {
	for (int j = 0; j < N - 1; ++j) {//расставляет отрицательные элементы в порядке убывания
		int flag = 0;
		for (int i = 0; i < N - j; ++i) {
			if (*(pA + i) < *(pA + i + 1))
				if (*(pA + i + 1) <= 0) {
					swap(*(pA + i), *(pA + i + 1));
					flag++;
				}
		}
		if (!flag) { break; }
	}
}
int main() {
	int N{ 0 };
	cout << "Enter array dimension\n";
	cin >> N;
	int * pA = nullptr;
	pA = giveMemory(N);
	randomInit(pA, N);cout << '\n';
	printArr(pA, N);cout << '\n';
	positivToTheEnd(pA, N);
	sortNegativ(pA, N);cout << '\n';
	printArr(pA, N);cout << '\n';
	freeMemory(pA);
	system("pause");
	return 0;
}
