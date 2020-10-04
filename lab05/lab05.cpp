#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void draw_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(2, 4);
    printf("<-0->");
}
void draw_bullet(int x, int y)
{
    gotoxy(x, y);
    setcolor(7, 0);
    printf("|");
}
void del(int a, int b)
{
    gotoxy(a, b);
    setcolor(7, 0);
    printf("     ");
}
void delbullet(int a, int b)
{
    gotoxy(a, b);
    setcolor(7, 0);
    printf(" ");
}
int main()
{
    char ch = '.';
    int x = 38, y = 20;
    int walk = 0; //0 = no walk
    int bullet[5] = { 0 };
    int keep = 0;
    int i[5], o[5];
    int check = 0;

    setcursor(0);
    draw_ship(x, y);

    do {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'a')
            {
                walk = 1;
            }
            if (ch == 'd')
            {
                walk = 2;
            }
            if (ch == 's')
            {
                walk = 0;
            }
            if (ch == ' ' && check < 5)
            {
                bullet[keep % 5] = 1;
                i[keep % 5] = x + 2;
                o[keep % 5] = y - 1;
                check++;
                keep++;
            }
        }
        if (walk == 1 && x > 0)
        {
            del(x, y);
            draw_ship(--x, y);
        }
        if (walk == 2 && x < 75)
        {
            del(x, y);
            draw_ship(++x, y);
        }
        for (int a = 0; a < 5; a++)
        {
            if (bullet[a] == 1)
            {
                delbullet(i[a], o[a]);
                if (o[a] == 0)
                {
                    bullet[a] = 0;
                    check--;
                }
                if (o[a] > 0)
                {
                    draw_bullet(i[a], --(o[a]));
                }
            }
        }
        fflush(stdin);
        Sleep(100);
    } while (ch != 'x');
    return 0;
}