#include<Windows.h>
#include<stdio.h>
#include "face.h"
#include"switch.h"

void faceFirst()
{
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setface1();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setTextcolor();
	printf("\t\t\t\t      1.播放列表\t\t\t2.使用说明\n\n");
	printf("\t\t\t\t      3.开发信息\t\t\t4.更换皮肤\n\n");
	printf("\t\t\t\t      0.退出程序\n\n");
}
void faceList()
{
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setface2();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *x.切换播放模式       *t.我的歌单   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *p.选曲播放           *q.搜索曲目   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *l.返回菜单                         ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");

	switch (mode)
	{
	case 1:printf("当前播放模式：单曲循环\n"); break;
	case 2:printf("当前播放模式：顺序播放\n"); break;
	case 3:printf("当前播放模式：随机播放\n"); break;
	}
}



void myFaceList()
{
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setface2();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *x.新建歌单           *t.删除歌单   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *p.展示歌单           *q.选曲播放   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *l.添加歌曲           *d.删除歌曲   ║\n");
	printf("\t\t\t\t\t║                                     ║\n");
	printf("\t\t\t\t\t║ *a.所有歌单           *e.返回菜单   ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
}



void facePlayer()
{
	system("CLS");
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setface2();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setCursorPosition(45, 9);
	printf("\t\t\t\t╔══════════════════════════════════════╗\n");
	setCursorPosition(45, 10);
	printf("\t\t\t\t║                                      ║\n");
	setCursorPosition(45, 11);
	printf("\t\t\t\t║ *tab.选曲播放        *space.播放/暂停║\n");
	setCursorPosition(45, 12);
	printf("\t\t\t\t║                                      ║\n");
	setCursorPosition(45, 13);
	printf("\t\t\t\t║ *↑.上一曲           *↓.下一曲      ║\n");
	setCursorPosition(45, 14);
	printf("\t\t\t\t║                                      ║\n");
	setCursorPosition(45, 15);
	printf("\t\t\t\t║ *←.快退             *→.快进        ║\n");
	setCursorPosition(45, 16);
	printf("\t\t\t\t║                                      ║\n");
	setCursorPosition(45, 17);
	printf("\t\t\t\t║ *+.音量+             *-.音量-        ║\n");
	setCursorPosition(45, 18);
	printf("\t\t\t\t║                                      ║\n");
	setCursorPosition(45, 19);
	printf("\t\t\t\t║            *enter.退出播放           ║\n");
	setCursorPosition(45, 20);
	printf("\t\t\t\t║                                      ║\n");
	setCursorPosition(45, 21);
	printf("\t\t\t\t╚══════════════════════════════════════╝\n");

	setCursorPosition(45, 22);
	printf("\t\t\t\t进度条\n\n");
}




void state()
{
	system("CLS");
	//setbkcolor();
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t使用说明\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t 1.请将要播放的.mp3歌曲文件放入默认路径\" D:\\music\\ \"下\n\t\t  (若要更改路径，直接修改function.c文件开头PATH的宏定义即可)\n\n\n");
	printf("\t\t 2.部分.mp3由于文件帧率过高无法播放，请更换源文件\n\n\n");
	printf("\t\t 3.播放器默认播放模式为单曲循环，可更改\n\n\n");
	printf("\t\t 4.允许向默认文件夹加入新的.mp3文件，请使用\"选项更新文件\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
	printf("\t\t 5.如果歌曲播放时需要删除歌曲，请先按p停止播放，删除文件后使用选曲播放更新文件。移动正在播放的文件可能会产生bug\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t 6.系统颜色为界面、提示等颜色，文本颜色为歌单列表，歌词等\n\n\n");
	system("pause");
}

void info()
{
	system("CLS");
	//setbkcolor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t版权说明\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t本项目是四川大学软件学院2020级2021年实训第二十组项目Podcast音乐播放器");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t\t\t\t\t 四川大学软件学院：韩笑，沈宜璇，张悦\n");
	printf("\t\t\t\t\t\t\t\t\t\t2020.7.22\n");
	system("pause");
}

void facemode()
{
	system("CLS");
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setface2();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t╔══════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║                                      ║\n");
	printf("\t\t\t\t\t║  *1.循环播放         *2.顺序播放     ║\n");
	printf("\t\t\t\t\t║                                      ║\n");
	printf("\t\t\t\t\t║             *3.随机播放              ║\n");
	printf("\t\t\t\t\t╚══════════════════════════════════════╝\n");
}