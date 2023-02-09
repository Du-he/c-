#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#define N 50
#define M 50
void Show(char str[][M], int n);
void UpdateWithInput(char[][M], int n);
int main(void)
{
	char str[N][M] =
	{
		"************",
		"*o         *",
		"* **********",
		"* *    *  **",
		"* * * * * **",
		"* * * * *  *",
		"* * * * *  *",
		"* * * * ** *",
		"* * * * ** *",
		"* * * * ** *",
		"*   *  **  *",
		"************",
	};
	system("color 1F");
	int n = 12;
	Show(str, n);
	UpdateWithInput(str, n);
	return 0;
}
//函数功能：显示迷宫地图
void Show(char str[][M], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		puts(str[i]);
	}
}
//函数功能：完成与用户输入有关的迷宫更新
void UpdateWithInput(char str[][M], int n)
{
	int x = 1, y = 1;
	int exitX = 10, exitY = 10;
	char input;
	while (x != exitX || y != exitY)
	{
		if (kbhit())////如果有按键按下，则_kbhit()函数返回真<conin.h>
		{
			input = getch();//getch函数：获取键盘输入，无需回车（非标准函数<conio.h>)
			if (input == 'a' && str[x][y - 1] != '*')
			{
				str[x][y] = ' ';
				y--;
				str[x][y]='a';

			}
			if (input == 'd' && str[x][y + 1] != '*')
			{
				str[x][y] = ' ';
				y++;
				str[x][y] = 'a';
			}
			if (input == 'w' && str[x-1][y] != '*')
			{
				str[x][y] = ' ';
				x--;
				str[x][y] = 'a';
			}
			if (input == 's' && str[x + 1][y] != '*')
			{
				str[x][y] = ' ';
				x++;
				str[x][y] = 'a';
			}
		}
		system("cls");
		Show(str, n);
		Sleep(10);
		
	}
	printf("You win!\n");
	//system("PAUSE");
	system("PAUSE");
	
}