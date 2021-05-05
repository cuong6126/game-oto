#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <fstream>
using namespace std;
•	Xây dựng các biến, mảng
char map[50][50];
int diem = 0;
int level = 0;
•	Xây dựng hàm
+ Thay đổi kích cỡ mà hình console
void resizeConsole(int width, int height)
{
HWND console = GetConsoleWindow();
RECT r;
GetWindowRect(console, &r);
MoveWindow(console, r.left, r.top, width,
height, TRUE);
}
+ Màu chữ hiển thị
void textcolor(int x)
{
HANDLE mau;
mau = GetStdHandle
(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(mau, x);
}
+ Nhảy đến tọa độ trong khung console
void gotoxy(int x, int y)
{
HANDLE hConsoleOutput;
COORD Cursor_an_Pos = { x - 1,y - 1 };
hConsoleOutput = GetStdHandle

(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hConsoleOutput,
Cursor_an_Pos);
}
+ Vẽ đường đua
void VeDuongDua_1()
{
// Dài 30, rộng 30.
for (int i = 0; i < 30; i++)
{
map[i][0] = '|';
map[i][29] = '|';
if (i % 2 == 0)
{
map[i][14] = '|';
}

for (int j = 1; j < 29 && j != 14; j++)
{
map[i][j] = ' ';
}
}
}
void VeDuongDua_2()
{
// Dài 30, rộng 30.
for (int i = 0; i < 30; i++)
{
map[i][0] = '|';
map[i][29] = '|';
if (i % 2 != 0)
{
map[i][14] = '|';
}

for (int j = 1; j < 29 && j != 14; j++)
{
map[i][j] = ' ';
}
}
}
+ Vẽ xe player
void VeXePlayer(int x, int y)
{
map[x][y] = 'X'; // Thân xe.
map[x][y - 1] = '#'; // Bên trái thân xe.
map[x][y + 1] = '#'; // Bên phải thân xe.
map[x - 1][y - 1] = '@'; // Bánh xe trên bên trái.
map[x + 1][y - 1] = '@'; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = '@'; // Bánh xe trên bên phải.
map[x + 1][y + 1] = '@'; // Bánh xe dưới bên phải.
}
+ Vẽ xe vật cản
void VeXeChuongNgaiVat(int x, int y)
{
map[x][y] = '!'; // Thân xe.
map[x][y - 1] = '!'; // Bên trái thân xe.
map[x][y + 1] = '!'; // Bên phải thân xe.
map[x - 1][y - 1] = '!'; // Bánh xe trên bên trái.
map[x + 1][y - 1] = '!'; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = '!'; // Bánh xe trên bên phải.
map[x + 1][y + 1] = '!'; // Bánh xe dưới bên phải.
}
+Xóa xe vật cản
void XoaXeChuongNgai(int x, int y)
{
map[x][y] = ' '; // Thân xe.
map[x][y - 1] = ' '; // Bên trái thân xe.
map[x][y + 1] = ' '; // Bên phải thân xe.
map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.
}
+ Hiển thị : Đường đua, xe, vật cản
void InDuongDua()
{
// Dài 30, rộng 30.
for (int i = 0; i < 30; i++)
{
cout << " ";
for (int j = 0; j <= 30; j++)
{
/* ========= In Đường Đua ======== */
if (j == 0 || j == 29)
{
textcolor(191);
map[i][j] = ' ';
cout << map[i][j];
textcolor(7);
}
else if (j == 14)
{
textcolor(15);
cout << map[i][j];
textcolor(7);

map[i][j] = ' '; // Xóa lằn đi.
}
else if (j == 1 || j == 30)
{
textcolor(19);
cout << map[i][j];
textcolor(7);

}

/* IN XE PLAYER */
else if (map[i][j] == 'X' || map[i][j] == '@' || map[i][j] == '#')
{
textcolor(14); // Màu vàng.
cout << map[i][j];
textcolor(7); // Trở lại màu bình thường.
}

/* IN XE COMPUTER */
else if (map[i][j] == '!')
{
//map[i][j] = ' '; // Bỏ đi ký tự '!'
textcolor(200);
cout << map[i][j];
textcolor(7);
}
// Những ký tự không phải là xe.
else
{
cout << map[i][j];
}
}
cout << endl;
}
}
+ Đọc, ghi file

void ghidiem()
{
char data[100];
ofstream FileOut;
FileOut.open("oscore.txt", ios::app);

cout << "\n---------SAVE HIGH SCORE-----------\n\n";

cout << "\n Nhap Ten Cua Ban: ";
cin.getline(data, 100);
cout << "\n Score: \t" << diem << "\n Level: \t"<< level;
FileOut << "\n Score: \t" << diem<<"\n Level: \t"<< level << "\n PLAYER: " << data << endl;
cout << "\n-------------------------------\n\n";

FileOut.close();
}
void gameover()
{

ifstream FileGO;
FileGO.open("gameover.txt", ios::in);

while (!FileGO.eof())
{
char c;
FileGO.get(c);
Sleep(1);

textcolor(14);
cout << c;
textcolor(7);
}

FileGO.close();

VeHinh(20, 10, "SCORE: ", 15);
cout << diem;
VeHinh(20, 11, "LEVEL: ", 15);
cout << level;


VeHinh(20, 17, "F6. EXIT GAME ", 15);
VeHinh(20, 19, "F7. SAVE GAME ", 15);
VeHinh(20, 21, "F8. HIGH SCORE ", 15);

while (true)
{

if (GetAsyncKeyState(VK_F6))
{

VeHinh(20, 17, "F6..EXIT GAME ", 14);
system("cls");
exit(0);
}

if (GetAsyncKeyState(VK_F7))
{

VeHinh(20, 17, "F7..SAVE GAME ", 14);
system("cls");
ghidiem();
}

if (GetAsyncKeyState(VK_F8))
{

VeHinh(20, 17, "F7..SAVE GAME ", 14);
system("cls");
docdiem();
}
}

cout << "\n\n\n\n\n";

system("pause");
}
+ Điều khiển xe player
void DiChuyenXe(int &x, int &y) // x, y là tọa độ hiện tại của xe.
{
// qua trái.
if (GetAsyncKeyState(VK_LEFT))
{
if (y > 3)
{
// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
{

system("cls");
gameover();
while (_getch() != 13);
}

// Xóa xe đi.
map[x][y] = ' '; // Thân xe.
map[x][y - 1] = ' '; // Bên trái thân xe.
map[x][y + 1] = ' '; // Bên phải thân xe.
map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

y--; // Giảm cột xuống.
VeXePlayer(x, y); // Vẽ lại xe.
}

}

// qua phải.
else if (GetAsyncKeyState(VK_RIGHT))
{
if (y <= 26)
{
// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
{

system("cls");
gameover();
while (_getch() != 13);
}
// Xóa xe đi.
map[x][y] = ' '; // Thân xe.
map[x][y - 1] = ' '; // Bên trái thân xe.
map[x][y + 1] = ' '; // Bên phải thân xe.
map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

y++; // Tăng cột lên.
VeXePlayer(x, y); // Vẽ lại xe.
}
}

// Đi lên.
else if (GetAsyncKeyState(VK_UP))
{
if (x > 1)
{
// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
{

system("cls");
gameover();
while (_getch() != 13);
}

// Xóa xe đi.
map[x][y] = ' '; // Thân xe.
map[x][y - 1] = ' '; // Bên trái thân xe.
map[x][y + 1] = ' '; // Bên phải thân xe.
map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

x--; // Giảm số dòng.
VeXePlayer(x, y); // Vẽ lại xe.
}
}

// Đi xuống
else if (GetAsyncKeyState(VK_DOWN))
{
if (x <= 27)
{
// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
{
system("cls");
gameover();
while (_getch() != 13);
}

// Xóa xe đi.-
map[x][y] = ' '; // Thân xe.
map[x][y - 1] = ' '; // Bên trái thân xe.
map[x][y + 1] = ' '; // Bên phải thân xe.
map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.
x++; // Tăng số dòng.
VeXePlayer(x, y); // Vẽ lại xe.
}
}
}
+ Nhận diện phím
void option()
{
if (GetAsyncKeyState(VK_RETURN))
{
exit(0);
}
else if (GetAsyncKeyState(VK_F1))
{
system("pause");
}
}
+ Thân chạy chương trình
int main()
{

resizeConsole(1000, 420);
int x = 24, y = 17; // Tọa độ của xe Player.
int x1 = 2, y1; // Tọa độ xe chướng ngại vật động.
int x2 = 5, y2 = 10; // Tọa độ xe chướng ngại vật tĩnh.
int x3 = x - 2, y3 = y; // Tọa độ đạn
int x4 = 8, y4 = 6;
int a = 0;
while (true)
{
a++;
if (a % 2 != 0)
{
VeDuongDua_1();
}
else
{
VeDuongDua_2();
}
// Random tung độ cho xe computer.
/*
Muốn random 1 số nguyên trong đoạn [a, b]:
srand(time(0)); // Reset thời gian
int x = a + rand() % (b - a + 1); // Công thức
*/
srand(time(0)); // Reset thời gian
y1 = 2 + rand() % 26; // [2, 27]
if (x1>29 || x2>29 || x4 > 29)
{
gotoxy(56, 3);
cout << "" << diem++;
}
VeXePlayer(x, y);
VeXeChuongNgaiVat(x1, y1); // Xe động.
VeXeChuongNgaiVat(x2, y2); // Xe tĩnh.
VeXeChuongNgaiVat(x4, y4); // Xe tĩnh.
XoaManHinh();
InDuongDua();
DiChuyenXe(x, y);
option();
#pragma region Sleep


if (diem <= 20)
{
Sleep(100);
level = 1;
}
else if (diem>20 && diem<40)
{
Sleep(80);
level = 2;
}
else if (diem>40 && diem<70)
{
Sleep(50);
level = 3;
}
else if (diem>70 && diem<100)
{
Sleep(30);
level = 4;
}
else if (diem>100 && diem<150)
{
Sleep(20);
level = 5;
}
else if (diem>150 && diem<250)
{
Sleep(10);
level = 6;
}
else if (diem>250)
{
Sleep(5);
level = 7;
}

#pragma endregion

if (a >= 30)
{
a = 0;
}
// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
{
system("cls");
gameover();
while (_getch() != 13);
break;
}

XoaXeChuongNgai(x1, y1);
x1++; // Tăng dòng lên, tạo hiệu ứng di chuyển.
if (x1 == 31)
{
x1 = 3;
}
XoaXeChuongNgai(x2, y2);
x2++;
if (x2 == 31)
{
x2 = 5;
y2 = 3 + rand() % 26; // [2, 27]
}
XoaXeChuongNgai(x4, y4);
x4++;
if (x4 == 31)
{
x4 = 8;
y4 = 3 + rand() % 26;
}
if (map[x3][y3] == '!')
{
map[x1][y1] = ' '; // Thân xe.
map[x1][y1 - 1] = ' '; // Bên trái thân xe.
map[x1][y1 + 1] = ' '; // Bên phải thân xe.
map[x1 - 1][y1 - 1] = ' '; // Bánh xe trên bên trái.
map[x1 + 1][y1 - 1] = ' '; // Bánh xe dưới bên trái.
map[x1 - 1][y1 + 1] = ' '; // Bánh xe trên bên phải.
map[x1 + 1][y1 + 1] = ' '; // Bánh xe dưới bên phải.
}

if (GetAsyncKeyState(VK_F5))
{
system("cls");
docdiem();
cout << "\n\n";
while (_getch() != 13);
return 0;
}
gotoxy(50, 5);
textcolor(13);
cout << "Level:" << level;
textcolor(7);

gotoxy(50, 3);
textcolor(13);
cout << "Score:";
textcolor(7);

gotoxy(40, 20);
textcolor(12);
cout << "Enter - Exit";
textcolor(7);

gotoxy(40, 23);
textcolor(12);
cout << "F1 - Pause";
textcolor(7);
}

}

