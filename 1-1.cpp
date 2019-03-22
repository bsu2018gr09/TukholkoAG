//1-1.Даны точки плоскости своими координатами в виде двух одномерных массивов (случайные числа).
//Точки плоскости рассортировать по возрастанию расстояния до прямой ax + by + c = 0.
#include <iostream>
#include <ctime>
using namespace std;
void initRandomCords(int * arr, int N) {
	for (int i = 0; i < N; ++i) {
		arr[i] = rand() % 10;
	}
}
void printArr(int * arr, int N) {
	for (int i = 0; i < N; ++i) {
		cout << arr[i] << " | ";
	}
}
void distance(int *d, int * X, int *Y, int A, int B, int C, int N) {
	for (int i = 0; i < N; ++i) {
		d[i] = abs((A * X[i] + B * Y[i] + C) / sqrt(A * A + B * B)); 
	}
}
void sortCoords(int * d, int * X, int * Y, int N) {
	int flag = 0;
	for (int j = 0; j < N - 1; ++j){
		for (int i = 0; i < N - j - 1; ++i) {
			if (d[i] > d[i + 1])
			{
				swap(d[i], d[i + 1]);
				swap(X[i], X[i + 1]);
				swap(Y[i], Y[i + 1]); 
				flag++;
			}
		}
	if(!flag){break;}	
	}
}
void free_Memory(int * arr) {
	delete[] arr;
	arr = nullptr;
}
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int N;
	cout << "Введите количество точек ";
	cin >> N;
	int *X = new int[N];if(!X){cout<<"Error"; return 0;}
	int *Y = new int[N];if(!Y){cout<<"Error"; return 0;}
	initRandomCords(X, N);
	initRandomCords(Y, N);
	cout<<"x: | ";printArr(X, N);cout << '\n';
	cout << "y: | ";printArr(Y, N);cout << '\n';
	int A = 0, B = 0, C = 0;
	cout << "Введите A , B , C , для уравнения прямой Ax+By+C = 0\n";
	cin >> A >> B >> C;cout << '\n';
	int *d = new int[N];
	distance(d, X, Y, A, B, C, N);
	sortCoords(d, X, Y, N);cout << '\n';
	cout << "x: | ";printArr(X, N);cout << '\n';
	cout << "y: | ";printArr(Y, N);cout << '\n';
	free_Memory(X);
	free_Memory(Y);
	free_Memory(d);
	system("pause");
	return 0;
}
