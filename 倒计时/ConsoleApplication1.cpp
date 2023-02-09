#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main()
{
	int time_a;
	system("color 0a");   //指定倒计时在运行时的颜色
	printf("请输入倒计时（单位：秒）：");
	scanf_s("%d", &time_a);
	
	for (int i = time_a; i >= 0; i--)
	{
		
		Sleep(1000);
		system("cls");
		printf("倒计时剩余：%d\n", i);
		fflush(stdout);
	}
	//do {
	//	Sleep(1000);
	//	time_a = time_a - 1;
	//	printf("倒计时剩余：%d\n", time_a);
	//} while (time_a == 0);
	
}