//Горизонтальный градиент с выбором цветов, количества шагов и ширины файла
//как то очень на Гапановича похоже
#include<iostream>
#include<fstream>  
#include<clocale>
#include<cmath>
using namespace std;
struct color { unsigned char b; unsigned char g; unsigned char r; } c;

int main() {
	setlocale(LC_ALL, "RUS");
	ifstream fff("d:\\1.bmp", ios::binary); //  ios::binary влияет ТОЛЬКО на endl.
	ofstream ggg("d:\\rez.bmp", ios::binary);//сюда пишем (поток типа ofstream= output file stream)
	if (!fff) { cout << "No file d:\\1.bmp. Can't open\n"; exit(1); }
	if (!ggg) { cout << "No file d:\\rez.bmp. Can't create\n"; exit(1); }

	char buf[30];// куда читать байты
	unsigned char r, g, b;//компоненты цвета
	color c;
	unsigned int w, h;//надеемся. что тут 4 байта
	float rstart, gstart, bstart;
	cout << "Введите R G B для начального цвета:\n";
	cin >> rstart >> gstart >> bstart;
	float rend, gend, bend;
	cout << "Введите R G B для конечного цвета:\n";
	cin >> rend >> gend >> bend;
	float step = 0;
	cout << "Количество шагов:\n";
	cin >> step;//не увидел разницу если ввожу 2 и ввожу 200. что то не то!
	float stepR = abs((rend - rstart) / step);
	float stepG = abs((gend - gstart) / step);
	float stepB = abs((bend - bstart) / step);
	float stepR2 = (rend - rstart) / step;
	float stepG2 = (gend - gstart) / step;
	float stepB2 = (bend - bstart) / step;
	fff.read((char *)&buf, 18);
	ggg.write((char *)&buf, 18);
	fff.read((char *)&w, 4);
	fff.read((char *)&h, 4);
	cout << "Введите ширину файла(кратную 4)\n";
	cin >> w;h = 256;
	ggg.write((char *)&w, 4);
	ggg.write((char *)&h, 4);
	fff.read((char *)&buf, 28);
	ggg.write((char *)&buf, 28);
	float truestepR, truestepG, truestepB;
	if (step >= 255) {
		truestepR = (rend - rstart)*stepR / w;
		truestepG = (gend - gstart)*stepG / w;
		truestepB = (bend - bstart)*stepB / w;
	}
	else {
		truestepR = stepR2*step / w;
		truestepG = stepG2*step / w;
		truestepB = stepB2*step / w;
	}
	c.r = rstart;c.g = gstart;c.b = bstart;
	float tmpR, tmpG, tmpB;
	tmpR = rstart;tmpG = gstart;tmpB = bstart;
	for (int i = 1;i <= h;++i) {
		for (int j = 1;j <= w;++j) {
			tmpR += truestepR;
			tmpG += truestepG;
			tmpB += truestepB;
			c.r = tmpR;
			c.g = tmpG;
			c.b = tmpB;
			ggg.write((char *)&c, 3);
		}
		tmpR = rstart;
		tmpG = gstart;
		tmpB = bstart;
	}
	fff.close();
	ggg.close();
	return 1;
}
