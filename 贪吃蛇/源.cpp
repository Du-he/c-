#include "one.h"
//将光标移动到指定位置 
void gotoxy(HANDLE hout, int x, int y) {
    //COORD是WindowsAPI中定义的一种结构，表示一个字符在控制台屏幕上的坐标
    COORD pos;
    pos.X = x;
    pos.Y = y;
    //SetConsoleCursorPosition是API中定位光标位置的函数。
    SetConsoleCursorPosition(hout, pos);
}
//游戏封面
void cover(HANDLE hout) {
    gotoxy(hout, framex + wide, framey);
    printf("snake——贪吃蛇游戏");
    gotoxy(hout, framex + wide, framey + 5);
    printf("开始游戏前请关闭中文输入法");
    gotoxy(hout, framex + wide * 2, framey + 20);
    printf("游戏制作者：Joe");
    gotoxy(hout, framex + wide * 2, framey + 22);

    char a;
    a = getchar();
    system("cls");
}
//定义蛇的结构体 
struct  Snake {
    int x[100];
    int y[100];
    int speed;
    int length;
    int count;
};
//定义食物的结构体 
struct Food {
    int x;
    int y;
};
//制作框架 
void makeframe(struct Snake snake) {
    //定义显示器变量句柄 
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(hout, framex + wide * 2 + 5, framey);
    printf("   贪吃蛇游戏");
    gotoxy(hout, framex + wide * 2 + 5, framey + 3);
    printf("使用方向键或wasd移动");
    gotoxy(hout, framex + wide * 2 + 5, framey + 5);
    printf("长按方向键可加速");
    gotoxy(hout, framex + wide * 2 + 5, framey + 7);
    printf("按任意键暂停,方向键继续");
    //打印上边框 
    for (i = 0; i < wide * 2 + 1; i++) {
        gotoxy(hout, framex + i, framey);
        printf("*");
    }
    //打印下边框 
    for (i = 0; i < wide * 2 + 2; i++) {
        gotoxy(hout, framex + i, framey + high);
        printf("*");
    }
    //打印左边框 
    for (i = 0; i < high; i++) {
        gotoxy(hout, framex, framey + i);
        printf("■");
    }
    //打印右边框 
    for (i = 0; i < high; i++) {
        gotoxy(hout, framex + wide * 2 + 1, framey + i);
        printf("■");
    }
}
//游戏信息
void infor(HANDLE hout, struct Snake* snake) {
    gotoxy(hout, framex + wide * 2 + 5, framey + 15);
    printf("当前速度:%d", -snake->speed + 500);
    gotoxy(hout, framex + wide * 2 + 5, framey + 17);
    printf("当前得分:%d", snake->count);
    gotoxy(hout, framex + wide * 2 + 5, framey + 19);
    printf("当前长度:%d", snake->length);
}
//初始化蛇 
void initsnake(struct Snake* snake) {
    snake->x[0] = framex + 2;
    snake->y[0] = framey + high / 2;
    snake->count = 0;
    snake->length = 3;
    snake->speed = 400;
    //初始化由蛇尾至蛇头的坐标 
    for (i = 1; i < snake->length; i++) {
        snake->x[i] = snake->x[i - 1] + 1;
        snake->y[i] = snake->y[i - 1];
    }
}
//打印蛇 
void printsnake(HANDLE hout, struct Snake* snake) {
    for (i = 0; i < snake->length; i++) {
        gotoxy(hout, snake->x[i], snake->y[i]);
        if (i == snake->length - 1)
            printf("■");
        else if (i == 0)
            printf("■");
        else
            printf("■");
    }
}
//移动蛇 
void movesnake(HANDLE hout, struct Snake* snake) {
    gotoxy(hout, snake->x[0], snake->y[0]);
    //清除蛇尾 
    printf("  ");
    //蛇的后一节坐标变成前一节的坐标 
    for (i = 1; i < snake->length; i++) {
        snake->x[i - 1] = snake->x[i];
        snake->y[i - 1] = snake->y[i];
    }
}
//打印食物 
void printfood(HANDLE hout, struct Snake* snake, struct Food* food) {
    //用计算机时间获取随机值 
    srand((unsigned)time(NULL));
    while (1) {
        //将食物的横纵坐标的大小限定在窗口大小内 
        food->x = rand() % (wide - 2) + 1;
        food->y = rand() % (high - 2) + 1;
        //避免食物出现在边框上 
        if (food->x == 0 && food->y == 0)
            continue;
        //将食物的坐标放置在窗口内 
        food->x = 2 * food->x + framex;
        food->y += framey;
        //如果食物出现在蛇上，重新产生食物 
        for (i = 0; i < snake->length; i++) {
            if (food->x == snake->x[i] && food->y == snake->y[i])
                break;
        }
        //食物不在蛇上，打印食物，结束循环 
        if (i == snake->length) {
            gotoxy(hout, food->x, food->y);
            printf("●");
            break;
        }
    }


}
//吃食物 
void eatfood(HANDLE hout, struct Snake* snake, struct Food* food) {
    //如果蛇头的坐标等于食物的坐标 
    if (snake->x[snake->length - 1] == food->x && snake->y[snake->length - 1] == food->y) {
        //蛇长加一 
        snake->length++;
        //蛇身（不包括蛇尾）整体像前移动一格 
        for (i = snake->length - 1; i > 0; i--) {
            snake->x[i] = snake->x[i - 1];
            snake->y[i] = snake->y[i - 1];
        }
        //得到蛇尾的坐标（即蛇移动前的蛇尾坐标） 
        snake->x[0] = a[0];
        snake->y[0] = a[1];
        printfood(hout, snake, food);
        snake->count++;
        if (snake->count % 3 == 0)
            snake->speed -= 50;
    }
}
//死亡判断 
int ifdead(struct Snake* snake) {
    //如果碰到左边界 返回0；
    if (snake->x[snake->length - 1] == framex)
        return 0;
    //如果碰到右边界 返回0；
    if (snake->x[snake->length - 1] == framex + wide * 2)
        return 0;
    //如果碰到上边界 返回0；
    if (snake->y[snake->length - 1] == framey)
        return 0;
    //如果碰到下边界 返回0；
    if (snake->y[snake->length - 1] == framey + high)
        return 0;
    //如果碰到自己身体 返回0； 
    for (i = 0; i < snake->length - 1; i++)
        if (snake->x[snake->length - 1] == snake->x[i] && snake->y[snake->length - 1] == snake->y[i])
            return 0;
    //否则返回1； 
    return 1;
}
//开始游戏 
int main() {
    unsigned char ch = 77;
    //定义显示器句柄 
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cover(hout);
    struct Snake s, * snake = &s;
    struct Food  f, * food = &f;
    makeframe(*snake);
    initsnake(snake);
    printfood(hout, snake, food);
    Sleep(500);
    while (1) {
        infor(hout, snake);
        //保存蛇尾横纵坐标 
        a[0] = snake->x[0];
        a[1] = snake->y[0];
        j = 0;
        //如果用户敲击键盘
        if (kbhit()) {
            //用ch接收输入 ，注意是getch()，不需敲击回车
            ch = getch();
            if (kbhit()) {
                //长按时间
                Sleep(20);
                j = 1;
            }
        }
        switch (ch) {
            //向上移动 
        case'W':
        case 'w':
        case 72: {
            movesnake(hout, snake);
            //蛇头纵坐标减一 
            snake->y[snake->length - 1] -= 1;
            break;
        }
               //向下移动 
        case'S':
        case 's':
        case 80: {
            movesnake(hout, snake);
            //蛇头纵坐标加一 
            snake->y[snake->length - 1] += 1;
            break;
        }
               //向左移动 
        case'A':
        case 'a':
        case 75: {
            movesnake(hout, snake);
            //蛇头横坐标减二 
            snake->x[snake->length - 1] -= 2;
            break;
        }
               //向右移动 
        case'D':
        case 'd':
        case 77: {
            movesnake(hout, snake);
            //蛇头横坐标加二 
            snake->x[snake->length - 1] += 2;
            break;
        }
        }


        eatfood(hout, snake, food);
        printsnake(hout, snake);
        //如果判断蛇死亡，跳出循环 
        if (ifdead(snake) == 0 || ch == 27 || snake->speed == 0) {
            gotoxy(hout, framex + wide / 2, framey - 2);
            if (snake->speed == 0)
                printf("恭喜你通关了！！!");
            else
                printf("糟糕 T_T");
            break;
        }


        if (j == 0)
            //如果没有长按，蛇滞留的时间为 
            Sleep(snake->speed);
        //如果长按，蛇滞留的时间为 20ms，即加速 
        else
            Sleep(20);
    }
    //跳出循环时 ，滞留死亡场景一段时间
    Sleep(3000);
    //清屏 
    system("cls");
    //显示结束界面 
    if (snake->speed == 0)
        printf("\n\n\n\n\n\t\t\t哈哈，你赢了\n\n\t\t\t你得到了满分：24\n\n\n");
    else
        printf("\n\n\n\n\n\t\t\t哈哈，你输了\n\n\t\t\t你的最终得分是：%d\n\n\n", snake->count);
    Sleep(3000);
    return 0;
}
