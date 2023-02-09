#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <windows.h>				//用到了定时函数sleep()
#include <math.h>
#include <string.h>
#define PI 3.1416
int r[3][4] = { {30,20,130,60},{170,20,220,60},{260,20,310,60} };//三个按钮的二维数组
float alpha, R, h0, sim_t;//碰撞时的能量损失率，球的半径、初始高度、仿真时间
//按钮判断函数
int button_judge(int x, int y)
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	return 0;
}
//初始化图像
void init_figure()
{
	int i;
	setrop2(R2_COPYPEN);//当前颜色
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID);//实线
	rectangle(30, 100, 420, 330);//外框线
	setlinestyle(PS_DOT);//点线
	for (i = 30 + 39; i < 420; i += 39)
	{
		line(i, 100, i, 330);//竖直辅助线
	}
	for (i = 100 + 23; i < 330; i += 23)
	{
		line(30, i, 420, i);//水平辅助线
	}
}
//仿真运行
int simulation()
{
	char t[3];//百分值的字符
	char* out_text;
	float dt = 0.01;//仿真间隔10ms
	float dy = 230 / h0;//单位纵坐标
	long int N = (long int)(sim_t / dt);//迭代次数
	float* h = (float*)calloc(N, sizeof(float));//高度
	float* v = (float*)calloc(N, sizeof(float));//速度（竖直方向）
	long int i;//迭代变量
	float process_duty;//进度
	RECT r = { 370,35,400,65 };//百分值显示区域的矩形指针
	init_figure();//初始化图像网格
	setrop2(R2_COPYPEN);//当前颜色
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	fillrectangle(354, 19, 411, 81);//覆盖原进度条区域
	setlinestyle(PS_NULL);//无线条
	setbkmode(TRANSPARENT);//设置文字填充背景为透明
	//计算步骤
	h[0] = h0; v[0] = 0;
	BeginBatchDraw();//开始缓存区
	for (i = 1; i < N; i++)
	{
		if (h[i - 1] > R)//未发生碰撞
		{
			v[i] = v[i - 1] - 9.8 * dt;//速度计算
		}
		else//发生碰撞，动能损失alpha，速度损失alpha的开方
		{
			v[i] = -sqrt(alpha) * v[i - 1];
		}
		setfillcolor(WHITE);
		setlinecolor(WHITE);
		fillrectangle(354, 19, 416, 81);//覆盖原进度条区域
		h[i] = h[i - 1] + v[i] * dt;//高度计算
		process_duty = (i + 1) / (float)(N);
		setlinestyle(PS_SOLID);
		putpixel(30 + (int)(process_duty * 390), 330 - (int)(h[i] * dy), RED);
		setfillcolor(BLUE);
		setlinestyle(PS_NULL);
		fillpie(355, 20, 415, 80, 0, process_duty * 2 * PI);
		setfillcolor(WHITE);
		fillcircle(385, 50, 20);
		sprintf_s(t, "%d", (int)(process_duty * 100.0));//整型转换为字符串
		out_text = strcat(t, "%");//添加一个百分号
		drawtext(out_text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Sleep(dt * 1000);
		FlushBatchDraw();//刷新缓存区
	}
	EndBatchDraw();//结束缓存区
	free(h);
	free(v);
	return 0;
}

int main()
{
	int i, event = 0;
	char s[30];//输入字符串变量
	short win_width, win_height;//定义窗口的宽度和高度
	win_width = 480; win_height = 360;
	initgraph(win_width, win_height);//初始化窗口（黑屏）
	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		Sleep(30);//延时30ms
	}
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	_tcscpy(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);				//BLACK在graphic.h头文件里面被定义为黑色的颜色常量
	drawtext("输入参数", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R1内输入文字，水平居中，垂直居中，单行显示
	drawtext("运行", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R2内输入文字，水平居中，垂直居中，单行显示
	drawtext("退出", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//在矩形区域R3内输入文字，水平居中，垂直居中，单行显示
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	MOUSEMSG m;//鼠标指针

	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息

		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(20);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			//按照按钮判断左键单击后的操作
			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 1:
				InputBox(s, 30, "请输入碰撞时的能量损失率、球的半径、初始高度、仿真时间");
				sscanf(s, "%f%f%f%f", &alpha, &R, &h0, &sim_t);//将输入字符串依次扫描到全局变量里面
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			case 2:
				simulation();//仿真运行
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				break;
			case 3:
				closegraph();//关闭绘图环境
				exit(0);//正常退出
			default:
				FlushMouseMsgBuffer();//单击事件后清空鼠标消息
				//printf("\r\n(%d,%d)",m.x,m.y);//打印鼠标坐标，方便调试时确定区域
				break;
			}
			break;
		}
	}
	return 0;
}

