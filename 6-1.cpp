//6-1.Класс точка в двумерном пространстве. Хранить декартовы прямоугольные и полярные координаты.
#include<iostream>

using namespace std;

const double PI = 3.141592653589;

double radius (double x, double y);// вообще вне класса???? Ну, странновато. Но ладно...
double angle (double x, double y);// вообще вне класса???? Ну, странновато. Но ладно...

class Coords {
	public:// не вижу const и не вижу списков инициализации!!!!!
	Coords() { cout << "Default constructor is working!\n"; }
	Coords(double tmp) { x = tmp; y = 0; r = radius(x,y); fi = angle(x,y); cout << "Constructor for one coordinate is working\n"; }
	Coords(double tmp1, double tmp2) { x = tmp1; y = tmp2; r = radius(x, y); fi = angle(x, y); cout << "Constructor for two coordinates is working\n";}
	Coords(double tmp1, double tmp2, double tmp3, double tmp4){ x = tmp1; y = tmp2; r = tmp3; fi = tmp4; cout << "Constructor for all coordinates is working\n"; }
	Coords(Coords const &t) { cout << "copy constructor\n"; }
	~Coords() { cout << "working destructor for " << x << ";" << y << '\n'; }
	void set_x(double tmp) { 
		x = tmp; 
		r = radius(x, y); 
		fi = angle(x, y);
	}
	void set_y(double tmp) { 
		y = tmp; 
		r = radius(x, y); 
		fi = angle(x, y);
	}
	double get_x(double tmp) { 
		return x; 
	}
	double get_y(double tmp) { 
		return y; 
	}
	friend Coords operator + ( Coords& left,const Coords& right){
		double tmp = left.x + right.x, tmp1 = left.y + right.y, tmp2 = radius(tmp,tmp1), tmp3 = angle(tmp,tmp1);// зачем столько временных переменных?????
		return Coords(tmp, tmp1, tmp2, tmp3);
	}
	friend Coords operator - ( Coords& left, const Coords& right){
		double tmp = left.x - right.x, tmp1 = left.y - right.y, tmp2 = radius(tmp,tmp1), tmp3 = angle(tmp,tmp1);// зачем столько временных переменных?????
		return Coords(tmp, tmp1, tmp2, tmp3);
	}
	Coords& operator += (const Coords& right) {
		this->x += right.x;
		this->y += right.y;
		this->r = radius(this->x, this->y);
		this->fi = angle(this->x, this->y);
		return *this;
	}
	Coords& operator -= (const Coords& right) {
		this->x -= right.x;
		this->y -= right.y;
		this->r = radius(this->x, this->y);
		this->fi = angle(this->x, this->y);
		return *this;
	}
	bool operator == (const Coords& tmp){
		if(this->x == tmp.x && this->y == tmp.y)
			return true;
		else
			return false;
	}
	friend ostream& operator << (ostream & stream, const Coords& tmp)
	{
		stream << "(" << tmp.x << "," << tmp.y << ") polar: (" << tmp.r << "," << tmp.fi << ")\n";
		return stream;
	}
	friend istream& operator >> (istream & stream,  Coords& tmp)
	{
		stream >> tmp.x >> tmp.y; tmp.r = radius(tmp.x, tmp.y); tmp.fi = angle(tmp.x, tmp.y);
		return stream;
	}
	;
	private:
	double x;
	double y;
	double r;
	double fi;
};
int main() {
	Coords A = {1, 0}, B = {2, 2}, C = {3, 3};
	cout<<"Enter the coordinates of the point A:\n";
	cin >> A;
	cout << "A = " <<A << "B = " <<B << "C = " << C;
	cout <<"A + B = "<<A + B<<"A - B = " << A - B;
	A += C;
	cout <<"A += C: " << A;
	A -= C;
	cout <<"A -= C: " << A << '\n';

	Coords *ptr1, *ptr2;
	ptr1 = &A;
	cout << "ptr1 = " << *ptr1;
	cout << "ptr1 + A = " << *ptr1 + A;
	cout << "ptr1 - B = " << *ptr1 - B;
	*ptr1 += C;
	cout << "ptr1 += C: " << *ptr1;
	ptr1->set_x(5);
	ptr1->set_y(5);
	cout <<"ptr1->(5,5) = " << *ptr1 << '\n';

	int N{3};
	ptr2 = new (nothrow) Coords[N];if(!ptr2){cout<<"Error"; exit(1); }
	ptr2[0] = A; ptr2[1] = B; ptr2[2] = C;
	cout <<"ptr2[1] + *ptr1 = " << ptr2[1] + *ptr1; 
	cout <<"ptr2[2] - A = " << ptr2[2] - A;
	delete[] ptr2;
	ptr2 = nullptr;
	system("pause");
	return 0;
}

double radius (double x, double y) {
		return sqrt(x*x + y*y); 
	}
	double angle (double x, double y) {
		if(x != 0 || y!= 0){
			if(x <= 0 && y < 0)
				return atan(y / x) - PI;
			else if(x <= 0 && y >= 0)
				return  atan(y / x) + PI;
			else
				return atan(y / x);

		}
		else return 0;
	}
