#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" ");
}
void clean_line(int y)
{
	gotoxy(0, y);
	for (int x = 0; x < 80; x++) {
		printf(" ");
	}
}
void bullet_ON(int x, int y)
{
	gotoxy(x, y);
	printf("o");
}
void bullet_OFF(int x, int y)
{
	gotoxy(x, y);
	printf(" ");
}
int main()
{
	char ch = ' ';
	int x = 38, y = 20, direction = 0, bullet = 0, bx = 0, by = 0,
		locy = 0;
	setcursor(0);
	draw_ship(x, y);
	direction = 0;// 0 = not move
	bullet = 0;// 0 = Bullet OFF
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				direction = -1;// -1 = move left
			}
			if (ch == 'd') {
				direction = 1;// 1 = move right
			}
			if (ch == 's') {
				direction = 0;
			}
			if (ch == ' ') {
				setcolor(7, 0);
				clean_line(locy);
				bx = x + 3;
				by = y - 1;
				bullet = 1;// 1 = Bullet ON
			}
			fflush(stdin);
		}
		if (direction != 0) {
			if (direction == -1) {
				setcolor(7, 0);
				erase_ship(x, y);
				setcolor(2, 4);
				if (x <= 0) draw_ship(0, y);
				else draw_ship(--x, y);
			}
			else if (direction == 1) {
				setcolor(7, 0);
				erase_ship(x, y);
				setcolor(2, 4); if (x >= 80) draw_ship(80, y);
				else draw_ship(++x, y);
			}
		}
		else if (direction == 0) {
			setcolor(7, 0);
			erase_ship(x, y);
			setcolor(2, 4);
			draw_ship(x, y);
		}
		if (bullet == 1) {
			setcolor(7, 0);
			bullet_OFF(bx, by);
			bullet_OFF(bx + 2, by);
			bullet_OFF(bx + 4, by);
			bullet_OFF(bx - 2, by);
			bullet_OFF(bx - 4, by);
			setcolor(11, 0);
			if (by > 0) {
				bullet_ON(bx, --by);
				bullet_ON(bx + 2, by);
				bullet_ON(bx + 4, by);
				bullet_ON(bx - 2, by);
				bullet_ON(bx - 4, by);
				locy = by;
			}
			else {
				clean_line(by);
				locy = 0;
				bullet = 0;
			}
		}
		Sleep(100);
	} while (ch != 'x');
	setcolor(7, 0);
	return 0;
}
