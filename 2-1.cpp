//В массиве А(N,M) расположить столбцы по возрастанию значений минимальных элементов столбцов.
#include<iostream>
#include<time.h>
#include<iomanip>
using namespace std;
void giveMemory2(int **&ptr,int N, int M) {
	ptr = new(nothrow) int*[N];
	if (!ptr)
	{
		cout << "Error!\n";
		exit(0);
	}
	for (int i = 0; i < N; ++i) {
		ptr[i] = new(nothrow) int[M];
		
	}
}
void initRandArray(int **ptr, int N, int M,int min, int max) {
	srand(time(0));
	for (int i = 0; i < N; ++i) {
		++ptr[i];
		for (int j = 0; j < M; ++j) {
			ptr[i][j] =rand()% (max - min  +1 ) - min;
		}
	}

}
void printArr2(int **ptr, int N, int M) {
		for (int j = 0; j < M; ++j) {
			for (int i = 0; i < N; ++i) {
			cout<<setw(2)<<ptr[i][j]<<" " ;
		}
		cout << endl;
	}
}

int min(int **ptr, int M,int i) {
	int min{20};
	for (int j = 0; j < M; ++j) {
		if(ptr[i][j]<min)
			min=ptr[i][j];
	}
	return min;
}
void sort(int **ptr, int N, int M) {
	for(int k = 0; k < N/2; ++k)
	for (int i = 0,i2 = 1; i < N, i2 < N ; ++i,++i2) {
		if(min(ptr,M,i)>min(ptr,M,i2))
		swap(ptr[i],ptr[i+1]);
	}
}
void free_array(int **&ptr, int N) {
	for (int i = 0; i < N; ++i) {
		delete ptr[i];
		ptr[i] = nullptr;
	}
	delete[] ptr;
	ptr = nullptr;
}
int main() {
		int N{ 0 },M{0};
		cout << "Enter N columns and number of elements in it\n";
		cin >> N>>M;
		int **ptr =nullptr;
		giveMemory2(ptr,N,M);
		initRandArray(ptr,N,M,0,20);
		printArr2(ptr,N,M);
		sort(ptr,N,M);
		cout<<'\n';
	    	printArr2(ptr, N, M);
		free_array(ptr,N);
		system("pause");
		return 0;
}

