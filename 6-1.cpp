//6-1.Класс точка в двумерном пространстве. Хранить декартовы прямоугольные и полярные координаты.
#include<iostream>

using namespace std;

const double PI = 3.141592653589;

class Coords {
public:// не хватает геттеров по моему. - Добавил
	Coords() : x(0), y(0), r(radius(x, y)), fi(angle(x, y)) { cout << "Default constructor is working!\n"; }
	Coords(double tmp) : x(tmp), y(0), r(radius(x, y)), fi(angle(x, y)) { cout << "Constructor for one coordinate is working\n"; }
	Coords(double tmp1, double tmp2) : x(tmp1), y(tmp2), r(radius(x, y)), fi(angle(x, y)) { cout << "Constructor for two coordinates is working\n"; }
	Coords(double tmp1, double tmp2, double tmp3, double tmp4) : x(tmp1), y(tmp2), r(tmp3), fi(tmp4) {
		double tmp_r = radius(x, y), tmp_fi = angle(x, y);
		if (tmp_r != r && tmp_fi != fi) {
			cout << "Coordinates entered incorrectly\n";
			r = tmp_r;
			fi = tmp_fi;
		}
		cout << "Constructor for all coordinates is working\n"; 
	}
	Coords(Coords const &t) : x(t.x), y(t.y), r(radius(x, y)), fi(angle(x, y)) { cout << "copy constructor\n"; }
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
	double get_x() const {// не хватает геттеров по моему . - Добавил
		return x;
	}
	double get_y() const {
		return y;
	}
	double get_r() const {
		return r;
	}
	double get_fi() const {
		return fi;
	}
	const Coords operator + (const Coords& right) {
		return Coords(x + right.x, y + right.y, radius(x + right.x, y + right.y), angle(x + right.x, y + right.y));
	}
	const Coords operator - (const Coords& right) {
		return Coords(x - right.x, y - right.y, radius(x - right.x, y - right.y), angle(x - right.x, y - right.y));
	}
	Coords& operator = (const Coords& right) {
		this->x = right.x;
		this->y = right.y;
		this->r = radius(this->x, this->y);
		this->fi = angle(this->x, this->y);
		return *this;
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
	bool operator == (const Coords& tmp) {
		if (this->x == tmp.x && this->y == tmp.y)
			return true;
		else
			return false;
	}
	friend ostream& operator << (ostream & stream, const Coords& tmp)
	{
		stream << "(" << tmp.x << "," << tmp.y << ") polar: (" << tmp.r << "," << tmp.fi << ")\n";
		return stream;
	}
	friend istream& operator >> (istream & stream, Coords& tmp)
	{
		stream >> tmp.x >> tmp.y;
		tmp.r = tmp.radius(tmp.x, tmp.y);
		tmp.fi = tmp.angle(tmp.x, tmp.y);
		return stream;
	}
	;
private:

	double x;
	double y;
	double radius(const double _x, const double _y) {
		return sqrt(_x*_x + _y * _y);
	}
	double r = radius(x, y);
	double angle(const double _x, const double _y) {
		if (_x != 0 || _y != 0) {
			if (_x < 0 && _y < 0)
				return atan(_y / _x) - PI;
			else if (_x < 0 && _y >= 0)
				return  atan(_y /_x) + PI;
			else
				return atan(_y / _x);

		}
		else return 0;
	}
	double fi = angle(x, y);


};
int main() {

	Coords A , B = { 2, 2 }, C = { 3, 3 };
	cout << "Enter the coordinates of the point A:\n";
	cin >> A;
	cout << "A = " << A << "B = " << B << "C = " << C;
	cout << "A + B = " << A + B << "A - B = " << A - B;
	A += C;
	cout << "A += C: " << A;
	A -= C;
	cout << "A -= C: " << A << '\n';

	Coords *ptr1, *ptr2;
	ptr1 = &A;
	cout << "ptr1 = " << *ptr1;
	cout << "ptr1 + A = " << *ptr1 + A;
	cout << "ptr1 - B = " << *ptr1 - B;
	*ptr1 += C;
	cout << "ptr1 += C: " << *ptr1;
	ptr1->set_x(5);
	ptr1->set_y(5);
	cout << "ptr1->(5,5) = " << *ptr1 << '\n';

	int N{ 3 };
	ptr2 = new (nothrow) Coords[N]; if (!ptr2) { cout << "Error"; exit(1); }
	ptr2[0] = A; ptr2[1] = B; ptr2[2] = C;
	cout << "ptr2[1] + *ptr1 = " << ptr2[1] + *ptr1;
	cout << "ptr2[2] - A = " << ptr2[2] - A;
	delete[] ptr2;
	ptr2 = nullptr;
	system("pause");
	return 0;
}
