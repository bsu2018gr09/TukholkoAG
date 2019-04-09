//Горизонтальный градиент с выбором цветов, количества шагов и ширины файла
//как то очень на Гапановича
//- Делал сам, на гит было добавлено раньше.
#include<iostream>
#include<fstream>  
#include<clocale>
#include<cmath>
using namespace std;
struct color { unsigned char b; unsigned char g; unsigned char r; } c;

int main() {
  setlocale(LC_ALL, "RUS");
  ifstream fff("C:\\file.bmp", ios::binary); //  ios::binary влияет ТОЛЬКО на endl.
  ofstream ggg("C:\\wrt.bmp", ios::binary);//сюда пишем (поток типа ofstream= output file stream)
  if (!fff) { cout << "No file d:\\1.bmp. Can't open\n"; exit(1); }
  if (!ggg) { cout << "No file d:\\rez.bmp. Can't create\n"; exit(1); }

  char buf[30];// куда читать байты
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
  cin >> step;
  fff.read((char *)&buf, 18);
  ggg.write((char *)&buf, 18);
  fff.read((char *)&w, 4);
  fff.read((char *)&h, 4);
  cout << "Введите ширину файла(кратную 4)\n";
  cin >> w; h = 256;
  ggg.write((char *)&w, 4);
  ggg.write((char *)&h, 4);
  fff.read((char *)&buf, 28);
  ggg.write((char *)&buf, 28);
  if (step > w){step = w; cout << "Шаг превышает ширину!!!";}//если шаг превышает ширину файла, нельзя корректно отобразить цвета, поэтому такое присваивание.
  float stepR = (rend - rstart) / step;
  float stepG = (gend - gstart) / step;
  float stepB = (bend - bstart) / step;
  c.r = rstart; c.g = gstart; c.b = bstart;
  float tmpR, tmpG, tmpB;
  tmpR = rstart; tmpG = gstart; tmpB = bstart;
  int k = 0;
  for (int i = 1; i <= h; ++i) {
    for (int j = 1; j <= w; ++j) {
      if (k < step) {//за заданнное количество шагов градиент меняет цвет и остается постоянным.
        tmpR += stepR;
        tmpG += stepG;
        tmpB += stepB;
        k++;
      }
      c.r = tmpR;
      c.g = tmpG;
      c.b = tmpB;
      ggg.write((char *)&c, 3);
    }
    tmpR = rstart;
    tmpG = gstart;
    tmpB = bstart;
    k = 0;
  }
  fff.close();
  ggg.close();
  system("pause");
}
