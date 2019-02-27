//1.2.ѕоложительные элементы массива ј(N) переставить в конец массива, сохран€€ пор€док следовани€. 
//ќтрицательные элементы расположить в пор€дке убывани€. ƒополнительный массив не использовать.
#include<iostream>
#include<time.h>
using namespace std;
int * pA = nullptr;
int* giveMemory(int N) {
	pA = new(nothrow) int[N];
	if (!pA) {
		cout << "error";
		return 0;
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
int main() {
	int N{0},cnt{0};
	cout << "Enter array dimension\n";
	cin >> N;
	giveMemory(N);
	randomInit(pA, N);cout << endl;
	printArr(pA, N);cout << endl;
	for (int i = N-1; i >= 0; --i) {            //переставл€ет положительные элементы в конец не мен€€ пор€док
		if (*(pA + i) > 0) {
			swap(*(pA + i),*(pA + N - 1 - cnt));
			cnt++;
		}
	}
	for (int j = 0; j < N ; ++j)				//расставл€ет отрицательные элементы в пор€дке убывани€
	for (int i = 0; i < N ; ++i) {
			if (*(pA + i) < *(pA + i + 1)) 
				if (*(pA + i + 1) <= 0)
				swap(*(pA + i), *(pA + i+ 1));	
}	
	cout<<endl;
	printArr(pA, N);cout << endl;
	freeMemory(pA);
	system("pause");
	return 0;
}