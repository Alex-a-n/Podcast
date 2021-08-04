#include"function.h"
#include"face.h"
#include<stdio.h>
#include<conio.h>
#include<io.h>
#include<conio.h>
#include<windows.h>
#include"function.h"
#include"switch.h"
#include<string.h>
#include<time.h>
#include <mmsystem.h>	         //mci库头文件
#include "LRC.h"
#pragma warning(disable:4996)
#pragma comment(lib, "winmm.lib")
#define PATH "D:\\music\\"      //路径宏定义，默认文件存放路径

int K = 0;//判断当前播放状态
int bkcolor = 0;
int textcolor = 0;
int syscolor = 0;//颜色定义为全局变量，syscolor包括界面提示，logo，歌词高亮部分等，
                                    //textcolor包括歌词，打印歌曲列表，歌单列表等
int isFir = 0;  //用于判断是否已经是第一曲
int isEnd = 0;  //用于判断是否已经是最后一曲
int face1 = 0;  //定义主菜单(第一个界面）logo样式
int face2 = 0;  //定义其他界面logo样式

struct media            //歌曲信息结构体，包括：序号，文件名
{
	int num;
	char name[100];
	struct media* next;
};

/*
* 功能：创建所有歌曲链表
* 返回值：所有歌曲链表头
*/
struct media* CreatHead()//创建结构体链表，加载所有文件信息，返回链表头指针
{
	struct media* head, * p, * q;
	head = (struct media*)malloc(sizeof(struct media));
	long Handle;
	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\music\\*.mp3", &FileInfo)) == -1L)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
		printf("\n\t没有找到匹配的项目\n\t请将.mp3文件放入D:\\music\\文件夹中,再重新选曲播放\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		system("pause");
		head = NULL;
		return head;
	}
	else
	{
		int i = 1;
		p = (struct media*)malloc(sizeof(struct media));
		q = head;
		p->num = i;
		strcpy(p->name, FileInfo.name);
		q->next = p;
		q = p;

		while (_findnext(Handle, &FileInfo) == 0)
		{
			i++;
			p = (struct media*)malloc(sizeof(struct media));
			p->num = i; strcpy(p->name, FileInfo.name);
			q->next = p;
			q = p;
		}
		p->next = NULL;
		_findclose(Handle);
	}
	return head;
}

/*
* 功能：打印某个链表内所有信息
* 参数：某个链表头
* 返回值：该链表中节点总数
*/
int Print_List(struct media* head)//打印文件下所有.mp3文件名，并返回文件数目（传参：歌曲信息链表头节点）
{
	system("CLS");
	struct media* p1;
	p1 = head->next;
	int i = 0;
	setTextcolor();
	printf("\t  ╔══════════════════════════════════════════════════════\n");
	while (p1 != NULL)
	{
		printf("\t  ║   %d. %s\n", p1->num, p1->name);
		p1 = p1->next;
		i++;
	}
	return i;
}

/*
* 功能：显示正在播放的歌曲
* 参数：某个链表工作指针
* 返回值：空
*/
void SongPlaying(struct media* p)//当前播放歌曲
{
	if (p == NULL)return;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setCursorPosition(25, 27);
	printf("\r%*c\r", 60, ' ');
	printf("\t\t\t\t当前正在播放歌曲：%s 请欣赏", p->name);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

/*
* 功能：从所有歌曲选择播放歌曲
* 参数：某个链表的链表头，工作指针，最小值，该链表所含节点总数
* 调用函数：play
* 返回值：选择歌曲的指针
*/
struct media* Choose_Song(struct media* HEAD, struct media* P, int num, int max)//选择歌曲选项。传参：列表头指针，工作指针,返回值：工作指针
{
	if (HEAD == NULL)//文件夹为空，头指针设为空
		return HEAD;
	else
	{
		struct media* p;//返回该工作指针
		p = HEAD->next;
		do
		{
			printf("\n\t请输入歌曲序号: ");

			scanf("%d", &num);
			while (getchar() != '\n')continue;//清除缓冲区，如果用户输入字符将会死循环
			if (!(num > 0 && num <= max))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
				setSyscolor();
				printf("\t请输入歌曲对应序号1~ %d ！\n", max);
				fflush(stdin);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		} while (!(num > 0 && num <= max));//得到合法的序号

		while (p->num != num) p = p->next;
		if (P != NULL)Close_Play(P);
		return p;
	}

}

/*
* 功能：默认列表内查找歌曲（可联想搜索）
* 参数：默认列表链表的链表头，工作指针，最小值，歌曲总数
* 调用函数：Choose_Song
* 返回值：搜索歌曲的工作指针
*/
struct media* FindSong(struct media* head, struct media* p, int num, int max)
{
	char str[100] = { 0 };
	int i = 0;
	char choice;
	struct media* pCur = head->next;

	system("CLS");
	Print_List(head);
	printf("请输入您想搜索的歌曲:");
	fflush(stdin);
	while ((choice = getchar()) != '\n' && choice != EOF)
		continue;
	gets(str);
	strcat(str, "\0");
	if (head != NULL)
	{
		pCur = head->next;
		while (pCur != NULL)
		{
			if (strstr(pCur->name, str) != NULL)  //检索到的歌曲	
			{
				printf("\t%d.%s\n", pCur->num, pCur->name);
				i++;
			}
			pCur = pCur->next;
		}

	}

	if (i == 0)
	{
		printf("\n未找到该歌曲");
		system("pause");
	}
	else
	{
		num = -1;
		p = Choose_Song(head, p, num, max);
	}
	return p;

}

/*
* 功能：播放歌曲
* 参数：某个链表的链表头，工作指针，该链表所含节点总数
* 调用函数：SongPlaying ,progress_Display
* 返回值：空
*/
void play(struct meida* head, struct media* p, int max)
{
	char cmd[100];
	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//获取短名
	sprintf(cmd, "open %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);
	sprintf(cmd, "play %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);

	K = 1;
	SongPlaying(p);
	progress_Display(head, p, max);
}

/*
* 功能：停止播放
* 参数：某个链表的工作指针
* 返回值：空
*/
void Close_Play(struct media* p)//停止播放（其实是关闭文件）
{
	if (p == NULL)
	{
		if (ch1 != 'l')//进播放器不做操作退出时，删掉这个判断会误显示下面的提示语，所以将ch1设置为全局变量
		{
			setSyscolor();
			printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
			Sleep(500);
		}

		return;
	}

	char cmd[100];
	char pathname[100];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	sprintf(cmd, "close %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);

	K = 0;//修改文件状态为暂停
}

/*
* 功能：暂停/继续播放歌曲
* 参数：某个链表的工作指针
* 返回值：空
*/
void Pause_Play(struct media* p)//暂停和播放合并
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return;
	}

	char pathname[200];
	char cmd[200];

	if (K == 1)//播放状态，执行暂停
	{
		sprintf_s(pathname, sizeof(pathname), "%s%s", PATH, p->name); //获取地址
		GetShortPathName(pathname, pathname, 50);     //获取短名
		sprintf_s(cmd, sizeof(cmd), "pause %s", pathname);     //获取命令
		mciSendString(cmd, NULL, 0, NULL);     //执行
		K = 0;
	}
	else if (K == 0)//暂停/停止状态，执行播放
	{
		sprintf_s(pathname, sizeof(pathname), "%s%s", PATH, p->name);
		GetShortPathName(pathname, pathname, 50);
		sprintf_s(cmd, sizeof(cmd), "play %s", pathname);
		mciSendString(cmd, NULL, 0, NULL);
		K = 1;
	}

}

/*
* 功能：播放上一曲歌曲
* 参数：某个链表的链表头，工作指针
* 返回值：工作指针
*/
struct media* Last_Play(struct media* head, struct media* p)//上一曲
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return p;
	}
	if (p != head->next) {
		Close_Play(p);//关闭当前歌曲
		struct media* q;
		q = (struct media*)malloc(sizeof(struct media));
		q = head->next;
		while (q->next != p)q = q->next;//将指针指向上一曲
		p = q;
		isFir = 0;
	}
	else
	{
		if (isFir == 1) {
			return p;
		}
		isFir = 1;
		printf("\n");		
		printf("\t\t\t当前是第一首！");
		Sleep(500);
		printf("\r");
		printf("\t\t\t                ");
		printf("\r");
		printf("\n");
	}
	return p;//返回工作指针
}

/*
* 功能：播放下一曲歌曲
* 参数：某个链表的链表头，工作指针
* 返回值：工作指针
*/
struct media* Next_Play(struct media* head, struct media* p)//下一曲
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return p;
	}
	if (p->next != NULL)
	{
		Close_Play(p);//关闭播放文件
		p = p->next;//指针指向下一曲
		isEnd = 0;
	}
	else
	{
		if (isEnd == 1) {
			return p;
		}
		isEnd = 1;
		printf("\n");
		printf("\t\t\t当前是最后一首！");
		Sleep(500);
		printf("\r");
		printf("\t\t\t                 ");
		printf("\r");
		printf("\n");
	}
	return p;//返回工作指针

}


/*
* 功能：减小音量
* 参数：某个链表的工作指针
* 返回值：空
*/
void VolDown(struct media* p)//音量减小（文件开始播放时默认音量为1000，每次可更改50）
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return;
	}
	TCHAR cmd[256]; // 媒体命令
	TCHAR volume[256]; // 音量(字符串)
	int nVolume; // 音量(整型)

	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);

	sprintf(cmd, "status %s volume", pathname); //pathname2为音乐的路径
	mciSendString(cmd, volume, sizeof(volume), 0); // 获取当前音量至 volume 字符串中

	nVolume = atoi(volume); // 字符串转化为整型

	sprintf(cmd, "setaudio %s volume to %i", pathname, nVolume - 50); // 生成媒体命令，设置音量减 50
	mciSendString(cmd, NULL, 0, NULL); // 执行媒体命令
}

/*
* 功能：增大音量
* 参数：某个链表的工作指针
* 返回值：空
*/
void VolUp(struct media* p)//音量增大
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return;
	}
	TCHAR cmd[256]; // 媒体命令
	TCHAR volume[256]; // 音量(字符串)
	int nVolume; // 音量(整型)

	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);

	sprintf(cmd, "status %s volume", pathname); //pathname2为音乐的路径
	mciSendString(cmd, volume, sizeof(volume), 0); // 获取当前音量至 volume 字符串中

	nVolume = atoi(volume); // 字符串转化为整型

	sprintf(cmd, "setaudio %s volume to %i", pathname, nVolume + 50); // 生成媒体命令，设置音量减 50
	mciSendString(cmd, NULL, 0, NULL); // 执行媒体命令
}

/*
* 功能：快进5s
* 参数：某个链表的工作指针
* 返回值：空
*/
void go(struct media* p)
{
	if (p == NULL)
	{
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return;
	}
	int time = Progress(p) * 1000;
	int nPosition;
	char position[200];
	char pathname[200];
	char cmd[200];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//获取短名
	sprintf(cmd, "status %s position", pathname);
	mciSendString(cmd, position, sizeof(position), 0);
	nPosition = atoi(position) + 5 * 1000;//当前位置

	if (nPosition > time) {
		nPosition = time;
	}
	sprintf(cmd, "play %s from %d", pathname, nPosition);
	mciSendString(cmd, NULL, 0, NULL); // 后加5000ms
}

/*
* 功能：快退5s
* 参数：某个链表的工作指针
* 返回值：空
*/
void back(struct media* p)
{
	if (p == NULL)
	{
		printf("\n\t\t\t当前无歌曲正在播放,请选曲播放\n");
		Sleep(500);
		return;
	}

	int itime;
	int nPosition;
	char position[200];
	char pathname[200];
	char cmd[200];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//获取短名
	sprintf(cmd, "status %s position", pathname);
	mciSendString(cmd, position, sizeof(position), 0);
	nPosition = atoi(position) - 5 * 1000;//当前位置

	if (nPosition < 0) {
		nPosition = 0;
	}
	sprintf(cmd, "play %s from %d", pathname, nPosition);
	mciSendString(cmd, NULL, 0, NULL); // 后加5000ms
}

/*
* 功能：设置系统文字颜色和文本文字颜色
* 参数：空
* 返回值：空
*/
void changeColor() {
	system("CLS");
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\t\t\t\t\t\t0--------------系统颜色\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	printf("\t\t\t\t\t\t1--------------深蓝\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("\t\t\t\t\t\t2--------------深绿\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("\t\t\t\t\t\t3--------------草绿\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("\t\t\t\t\t\t4--------------深红\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("\t\t\t\t\t\t5--------------紫红\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("\t\t\t\t\t\t6--------------深黄\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\t\t\t\t\t\t7--------------白色\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	printf("\t\t\t\t\t\t8--------------深灰\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("\t\t\t\t\t\t9--------------蓝色\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\t\t\t\t\t\t10-------------浅绿\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("\t\t\t\t\t\t11-------------浅蓝\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\t\t\t\t\t\t12-------------红色\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("\t\t\t\t\t\t13-------------玫红\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("\t\t\t\t\t\t14-------------黄色\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\t\t\t\t\t\t15-------------亮白\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║    请输入您想要改变的系统字体颜色   ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
	scanf("%d", &syscolor);
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║    请输入您想要改变的文本字体颜色   ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
	scanf("%d", &textcolor);
}
/*
* 功能：根据全局变量syscolor定义系统文字颜色
* 参数：空
* 返回值：空
*/
void setSyscolor()
{
	switch (syscolor) {
	case 0:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); break;
	case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); break;
	case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); break;
	case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); break;
	case 5:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); break;
	case 6:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;
	case 7:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); break;
	case 8:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); break;
	case 9:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); break;
	case 10:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); break;
	case 11:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break;
	case 12:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break;
	case 13:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); break;
	case 14:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break;
	case 15:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
	}
}
/*
* 功能：根据全局变量syscolor定义文本文字颜色
* 参数：空
* 返回值：空
*/
void setTextcolor()
{
	switch (textcolor) {
	case 0:	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); break;
	case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); break;
	case 3:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); break;
	case 4:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); break;
	case 5:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); break;
	case 6:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); break;
	case 7:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); break;
	case 8:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); break;
	case 9:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9); break;
	case 10:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); break;
	case 11:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); break;
	case 12:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); break;
	case 13:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); break;
	case 14:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); break;
	case 15:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
	}
}
/*
* 功能：根据全局变量face1设置主菜单logo
* 参数：空
* 返回值：空
*/
void  changeface1() {
	system("CLS");
	printf("\n\n\n");
	setSyscolor();
	printf("\t\t\t\t界面 0（默认） \n");
	printf("\t\t\t\t╔═════════════════════════════════════════════════════════════╗\n");
	printf("\t\t\t\t║          __  _______ _____                                  ║\n");
	printf("\t\t\t\t║         /  |/  / __ \\__  /                                  ║\n");
	printf("\t\t\t\t║        / /|_/ / /_/ //_ <                                   ║\n");
	printf("\t\t\t\t║       / /  / / ____/__/ /                                   ║\n");
	printf("\t\t\t\t║      /_/__/_/_/__ /___ /_ ___________      _____ ______     ║\n");
	printf("\t\t\t\t║     / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/     ║\n");
	printf("\t\t\t\t║    / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /        ║\n");
	printf("\t\t\t\t║   / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /         ║\n");
	printf("\t\t\t\t║  /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          ║\n");
	printf("\t\t\t\t║                                                             ║\n");
	printf("\t\t\t\t╚═════════════════════════════════════════════════════════════╝\n");
	printf("\t\t\t\t界面 1 \n");
	printf("\t\t\t\t /$$$$$$$                 /$$                                 /$$  \n ");
	printf("\t\t\t\t| $$__  $$               | $$                                | $$  \n  ");
	printf("\t\t\t\t| $$  \\ $$ /$$$$$$   /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$ \n");
	printf("\t\t\t\t| $$$$$$$//$$__  $$ /$$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  \n");
	printf("\t\t\t\t| $$____/| $$  \\ $$| $$  | $$| $$        /$$$$$$$|  $$$$$$   | $$    \n");
	printf("\t\t\t\t| $$     | $$  | $$| $$  | $$| $$       /$$__  $$ \\____  $$  | $$ /$$\n");
	printf("\t\t\t\t| $$     |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/\n");
	printf("\t\t\t\t|__/      \\______/  \\_______/ \\_______/ \\_______/|_______/    \\___/  \n");
	printf("\n");
	printf("\t\t\t\t界面 2 \n");
	printf("\n");
	printf("         \t\t        ██████╗  ██████╗ ██████╗  ██████╗ █████╗ ███████╗████████  \n");
	printf("         \t\t        ██╔══██╗██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝╚══██╔══╝  \n");
	printf("         \t\t 	██████╔╝██║   ██║██║  ██║██║     ███████║███████╗   ██║      \n");
	printf("         \t\t 	██╔═══╝ ██║   ██║██║  ██║██║     ██╔══██║╚════██║   ██║      \n");
	printf("         \t\t 	██║     ╚██████╔╝██████╔╝╚██████╗██║  ██║███████║   ██║    \n");
	printf("         \t\t 	╚═╝      ╚═════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝      \n\n");
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║    请输入您想要改变的系统界面样式   ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
	scanf("%d", &face1);
}
/*
* 功能：根据全局变量face1打印主菜单logo
* 参数：空
* 返回值：空
*/
void setface1() {
	switch (face1) {
	case 0:
		printf("\n\n\n");
		printf("\t\t\t\t╔═════════════════════════════════════════════════════════════╗\n");
		printf("\t\t\t\t║          __  _______ _____                                  ║\n");
		printf("\t\t\t\t║         /  |/  / __ \\__  /                                  ║\n");
		printf("\t\t\t\t║        / /|_/ / /_/ //_ <                                   ║\n");
		printf("\t\t\t\t║       / /  / / ____/__/ /                                   ║\n");
		printf("\t\t\t\t║      /_/__/_/_/__ /___ /_ ___________      _____ ______     ║\n");
		printf("\t\t\t\t║     / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/     ║\n");
		printf("\t\t\t\t║    / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /        ║\n");
		printf("\t\t\t\t║   / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /         ║\n");
		printf("\t\t\t\t║  /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          ║\n");
		printf("\t\t\t\t║                                                             ║\n");
		printf("\t\t\t\t╚═════════════════════════════════════════════════════════════╝\n\n\n");
		break;
	case 1:
		printf("\n\n\n\n\n");
		printf("\t\t\t\t /$$$$$$$                 /$$                                 /$$  \n ");
		printf("\t\t\t\t| $$__  $$               | $$                                | $$  \n  ");
		printf("\t\t\t\t| $$  \\ $$ /$$$$$$   /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$ \n");
		printf("\t\t\t\t| $$$$$$$//$$__  $$ /$$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  \n");
		printf("\t\t\t\t| $$____/| $$  \\ $$| $$  | $$| $$        /$$$$$$$|  $$$$$$   | $$    \n");
		printf("\t\t\t\t| $$     | $$  | $$| $$  | $$| $$       /$$__  $$ \\____  $$  | $$ /$$\n");
		printf("\t\t\t\t| $$     |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/\n");
		printf("\t\t\t\t|__/      \\______/  \\_______/ \\_______/ \\_______/|_______/    \\___/  \n");
		printf("\n\n\n\n");
		break;
	case 2:
		printf("\n\n\n\n\n\n\n");

		printf("         \t\t        ██████╗  ██████╗ ██████╗  ██████╗ █████╗ ███████╗████████  \n");
		printf("         \t\t        ██╔══██╗██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝╚══██╔══╝  \n");
		printf("         \t\t 	██████╔╝██║   ██║██║  ██║██║     ███████║███████╗   ██║      \n");
		printf("         \t\t 	██╔═══╝ ██║   ██║██║  ██║██║     ██╔══██║╚════██║   ██║      \n");
		printf("         \t\t 	██║     ╚██████╔╝██████╔╝╚██████╗██║  ██║███████║   ██║    \n");
		printf("         \t\t 	╚═╝      ╚═════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝      \n\n\n\n\n");
		break;
	}
}
/*
* 功能：根据全局变量face2设置其他界面logo
* 参数：空
* 返回值：空
*/
void  changeface2() {
	system("CLS");
	printf("\n\n\n");
	setSyscolor();
	printf("\t\t\t\t界面 0（默认） \n");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	printf("\t\t\t\t界面 1 \n");
	printf("\n");
	printf("\t\t\t\t /$$$$$$$                 /$$                                 /$$  \n ");
	printf("\t\t\t\t| $$__  $$               | $$                                | $$  \n  ");
	printf("\t\t\t\t| $$  \\ $$ /$$$$$$   /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$ \n");
	printf("\t\t\t\t| $$$$$$$//$$__  $$ /$$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  \n");
	printf("\t\t\t\t| $$____/| $$  \\ $$| $$  | $$| $$        /$$$$$$$|  $$$$$$   | $$    \n");
	printf("\t\t\t\t| $$     | $$  | $$| $$  | $$| $$       /$$__  $$ \\____  $$  | $$ /$$\n");
	printf("\t\t\t\t| $$     |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/\n");
	printf("\t\t\t\t|__/      \\______/  \\_______/ \\_______/ \\_______/|_______/    \\___/  \n");
	printf("\n");
	printf("\t\t\t\t界面 2 \n");
	printf("\n");
	printf("         \t\t        ██████╗  ██████╗ ██████╗  ██████╗ █████╗ ███████╗████████  \n");
	printf("         \t\t        ██╔══██╗██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝╚══██╔══╝  \n");
	printf("         \t\t 	██████╔╝██║   ██║██║  ██║██║     ███████║███████╗   ██║      \n");
	printf("         \t\t 	██╔═══╝ ██║   ██║██║  ██║██║     ██╔══██║╚════██║   ██║      \n");
	printf("         \t\t 	██║     ╚██████╔╝██████╔╝╚██████╗██║  ██║███████║   ██║    \n");
	printf("         \t\t 	╚═╝      ╚═════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝      \n");
	printf("\t\t\t\t\t╔═════════════════════════════════════╗\n");
	printf("\t\t\t\t\t║    请输入您想要改变的播放界面样式   ║\n");
	printf("\t\t\t\t\t╚═════════════════════════════════════╝\n");
	scanf("%d", &face2);
}
/*
* 功能：根据全局变量face2打印其他界面logo
* 参数：空
* 返回值：空
*/
void setface2() {
	switch (face2) {
	case 0:
		printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
		printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
		printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
		printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
		printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
		printf("\n\n");
		break;
	case 1:
		printf("\t\t\t\t /$$$$$$$                 /$$                                 /$$  \n ");
		printf("\t\t\t\t| $$__  $$               | $$                                | $$  \n  ");
		printf("\t\t\t\t| $$  \\ $$ /$$$$$$   /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$ \n");
		printf("\t\t\t\t| $$$$$$$//$$__  $$ /$$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  \n");
		printf("\t\t\t\t| $$____/| $$  \\ $$| $$  | $$| $$        /$$$$$$$|  $$$$$$   | $$    \n");
		printf("\t\t\t\t| $$     | $$  | $$| $$  | $$| $$       /$$__  $$ \\____  $$  | $$ /$$\n");
		printf("\t\t\t\t| $$     |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/\n");
		printf("\t\t\t\t|__/      \\______/  \\_______/ \\_______/ \\_______/|_______/    \\___/  \n");
		break;
	case 2:
		printf("\n");
		printf("         \t\t        ██████╗  ██████╗ ██████╗  ██████╗ █████╗ ███████╗████████  \n");
		printf("         \t\t        ██╔══██╗██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔════╝╚══██╔══╝  \n");
		printf("         \t\t 	██████╔╝██║   ██║██║  ██║██║     ███████║███████╗   ██║      \n");
		printf("         \t\t 	██╔═══╝ ██║   ██║██║  ██║██║     ██╔══██║╚════██║   ██║      \n");
		printf("         \t\t 	██║     ╚██████╔╝██████╔╝╚██████╗██║  ██║███████║   ██║    \n");
		printf("         \t\t 	╚═╝      ╚═════╝ ╚═════╝  ╚═════╝╚═╝  ╚═╝╚══════╝   ╚═╝      \n\n");
		break;
	}
}

/*
* 功能：定位光标位置
* 参数：横竖坐标x,y
* 返回值：空
*/
void setCursorPosition(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
* 功能：获取歌曲总时长
* 参数：工作指针
* 返回值：歌曲总时长（秒）
*/
int Progress(struct media* p) {

	int time;
	char len[100];
	char pathname[100];
	char cmd[100];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//获取短名
	sprintf(cmd, "status %s length", pathname);
	mciSendString(cmd, len, sizeof(len), NULL);//获取时间，单位为毫秒
	time = atoi(len) / 1000;
	return time;
}

/*
* 功能：时间/进度条/歌词显示，播放中功能接入和页面跳转
* 参数：某链表头，工作指针，链表中歌曲数量
* 调用函数：所有播放功能函数，获取时间函数，歌词生成相关函数
* 返回值：空
*/
void progress_Display(struct media* head, struct media* p, int max) {

	srand((unsigned)time(NULL));
	if (p == NULL) return;
	int time = Progress(p); //获取歌曲总秒数	
	//进度条相关定义
	int x = 68; 
	int y = 24;
	double pro = 1 / (double)37;
	int min = 0;
	int second = 0;
	int mtime = time / 60;
	int stime = time % 60;
	int xp = x + 6;
	//歌词相关定义
	LRC* heads = NULL, * p_new = NULL, * ps1 = NULL, * ps0 = NULL, * ps2 = NULL, * ps = NULL;
	char* str = NULL, * lrc_buf = NULL;
	char file_name[20];
	int i, j, k, len;
	int time_buf[5];
	char* q[200];

	//定位定样式打印进度条
	setSyscolor();
	setCursorPosition(x + 5, y);
	printf("%c", '|');
	setTextcolor();
	for (int i = 0; i < 37; i++) {
		printf("%c", '-');
	}
	setSyscolor();
	setCursorPosition(x + 43, y);
	printf("%c", '|');
	setCursorPosition(x + 44, y);
	printf("%02d:%02d", mtime, stime);
	
	lrc_buf = read_file(p); //获取所有歌词指针
	len = msg_deal(lrc_buf, q, "\r\n"); //分割歌词，获取每行歌词和总行数


	//分割每行歌词的时间和歌词
	for (int t = 0; (t >= 0) && (t <= time); t++) {

		for (k = 0; k < len; k++)
		{
			str = q[k];
			i = 0;
			while (*str == '[')//把时间记录在数组里
			{
				time_buf[i++] = atoi(str + 1) * 60 + atoi(str + 4);
				str += 10;
			}
			for (j = 0; j < i; j++)
			{
				p_new = (LRC*)malloc(sizeof(LRC));//申请新的节点
				p_new->m_time = time_buf[j];
				strcpy(p_new->lrc_buf, str);
				heads = link_insert(heads, p_new);
			}
		}
		if (t < heads->next->m_time + 1) {

			fflush(stdout);//输出刷新
			ps2 = link_search(heads, t);
			if (ps2 != NULL) {
				//printf("1\n");
				setCursorPosition(80, 20);
				setSyscolor();
				printf("\r%*c\r", 60, ' ');
				printf(" \t\t%s\n", ps2->lrc_buf);//打印所有时间
				setCursorPosition(80, 15);
				if (ps1 != NULL) {
					setTextcolor();
					printf("\r%*c\r", 60, ' ');
					printf(" \t\t%s\n", ps1->lrc_buf);//打印所有时间
					//printf("22\n");
				}
				setCursorPosition(80, 10);
				if (ps0 != NULL) {
					setTextcolor();
					printf("\r%*c\r", 60, ' ');
					printf(" \t\t%s\n", ps0->lrc_buf);//打印所有时间
				}
				ps0 = ps1;
				ps1 = ps2;
			}
		}

		
		setCursorPosition(x, y);
		setSyscolor();
		printf("%02d:%02d", min, second);
		second++;
		if (second == 60) {
			second = 0;
			min++;
		}
		double num = 0;
		double pro1 = ((double)t / (double)time);
		for (; num < 37; num++) {
			if ((pro1 >= (num * pro)) && (pro1 <= ((num + 1) * pro))) {
				setCursorPosition(xp + num, y);
				
				printf("%c", '>');
				break;
			}
		}
		for (int j = 0; j < 5; j++) {
			Sleep(190);
			if (GetKeyState(VK_SPACE) < 0) {//暂停
				Pause_Play(p);
				setbuf(stdin, NULL);
				setCursorPosition(x, y + 1);
				char a = getchar();
				Pause_Play(p);
			}
			else if (GetKeyState(VK_RETURN) < 0) { //停止
				Close_Play(p);
				return;
			}
			else if (GetKeyState(VK_UP) < 0) { //上一曲
				p = Last_Play(head, p);
				if (isFir == 0) {
					play(head, p, max);
				}			
			}
			else if (GetKeyState(VK_DOWN) < 0) { //下一曲
				p = Next_Play(head, p);
				if (isEnd == 0) {
					play(head, p, max);
				}
			}
			else if (GetKeyState(VK_OEM_PLUS) < 0) { //音量+
				VolUp(p);
			}
			else if (GetKeyState(VK_OEM_MINUS) < 0) { //音量-
				VolDown(p);
			}
			else if (GetKeyState(VK_TAB) < 0) { //跳到另一个页面
				chooseSong2(head, p);
			}
			else if (GetKeyState(VK_RIGHT) < 0) { //快进
				go(p);
				second += 5;
				if (second >= 60) {
					second = second - 60;
					min++;
					if ((min == mtime && second > stime) || (min > mtime)) {
						min = mtime;
						second = stime;
					}
				}
				t += 5;
				if (t > time) {
					t = time;
				}
				pro1 = ((double)t / (double)time);
				for (; num < 37; num++) {
					if ((pro1 >= (num * pro)) && (pro1 <= ((num + 1) * pro))) {
						setCursorPosition(xp + num, y);
						setSyscolor();
						printf("%c", '>');
						break;
					}
				}
			}
			else if (GetKeyState(VK_LEFT) < 0) { //快退               //新加
				back(p);
				second -= 5;
				if (second <= 0) {
					second = 60 + second;
					min--;
					if (min < 0) {
						min = 0;
						second = 0;
					}
				}
				t -= 5;
				if (t < 0) {
					t = 0;
				}
				pro1 = ((double)t / (double)time);
				for (; num >= 0; num--) {
					if ((pro1 >= (num * pro)) && (pro1 <= ((num + 1) * pro))) {
						setCursorPosition(xp + num, y);
						setSyscolor();
						printf("%c", '>');
						setTextcolor();
						printf("%c", '-');
						printf("%c", '-');
						break;
					}
				}
			}
		}
	}
	Sleep(1500);                                       //新增，播放模式
	if (mode == 1) { //单曲循环
		Close_Play(p);
		play(head, p, max);
	}
	else if (mode == 2) {//列表循环
		if (p->next == NULL) {
			p = head->next;
		}
		else {
			p = p->next;
		}
		play(head, p, max);
	}
	else if (mode == 3) {//随机
		int r = rand() % max + 1;
		for (int i = 0; i < r; i++) {
			if (p->next == NULL) {
				p = head->next;
			}
			else {
				p = p->next;
			}
		}
		play(head, p, max);
	}
}

/*
* 功能：在播放界面选取任意歌曲播放，与前面ChooseSong不同
* 参数：某个链表的链表头，工作指针
* 调用函数：play
* 返回值：工作指针
*/
struct media* chooseSong2(struct media* HEAD, struct media* P)//选择歌曲选项。传参：列表头指针，工作指针,返回值：工作指针,与前面选择函数不同的是打印歌曲列表不同
{
	if (HEAD == NULL)//文件夹为空，头指针设为空
		return HEAD;
	else
	{
		int max = Print_List(HEAD);
		int num = -1;
		int ch;
		struct media* p;//返回该工作指针
		p = HEAD->next;
		do
		{
			setSyscolor();
			printf("\n\t请输入歌曲序号: ");
			setbuf(stdin, NULL);
			scanf("%d", &num);
			//fflush(stdin);
			while ((ch = getchar()) != EOF && ch != '\n')continue;//清除缓冲区
				//printf("ceshi:%d\n", num);
			if (!(num > 0 && num <= max))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
				setSyscolor();
				printf("\t请输入歌曲对应序号1~ %d ！\n", max);
				fflush(stdin);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		} while (!(num > 0 && num <= max));//得到合法的序号

		while (p->num != num)p = p->next;
		setSyscolor();
		if (P != NULL)Close_Play(P);
		facePlayer();
		play(HEAD, p, max);
		return p;
	}
}

/*
* 功能：切割歌词
* 参数：所有歌词字符串指针，字符串数组——储存分句歌词，分隔符字符
* 返回值：歌词行数
*/
int msg_deal(char* msg_src, char* msg_done[], char* str)//分割字符串为一组字符串
{
	int i = 0;
	msg_done[i] = strtok(msg_src, str);
	while (msg_done[i] != NULL)
	{
		i++;
		msg_done[i] = strtok(NULL, str);
	}
	return i;
}
/*
* 功能：将分句后的歌词插入双向歌词链表
* 参数：歌词链表头，工作指针
*/
LRC* link_insert(LRC* head, LRC* p_new)
{
	LRC* pb;
	if (head == NULL)//空链表时
	{
		head = p_new;
		head->next = p_new;
		head->front = p_new;
	}
	else//有一个或以上节点时
	{
		pb = head->next;
		head->next = p_new;
		p_new->next = pb;
		p_new->front = head;
		pb->front = p_new;
	}
	return head;
}
/*
* 功能：根据播放时当前时长搜索对应时长的歌词
* 参数：歌词链表头，工作指针
* 返回值：工作指针或NULL
*/
LRC* link_search(LRC* head, int num)
{
	LRC* p_mov = head;
	if (head == NULL)
	{
		return NULL;
	}
	else
	{
		while (p_mov->next != head)
		{
			if (p_mov->m_time == num)
			{
				return p_mov;
				break;
			}
			p_mov = p_mov->next;
		}
		if (p_mov->m_time == num)
		{
			return p_mov;
		}
		return NULL;
	}
}
/*
* 功能：根据当前播放的歌曲检索对应歌词文件
* 参数：当前播放歌曲的指针
* 返回值：对应歌词文件中的全部字符
*/
char* read_file(struct media* p)
{
	FILE* fp = NULL;
	char* buf;
	unsigned long int file_length;
	char pathname[100];
	int len = 0;
	char ric[100];
	char* name;
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);
	name = strtok(pathname, ".");
	strcat(name, ".lrc");
	//printf("%s", name);
	//system("pause");
	//sprintf(ric, "%s%s", PATH, name);
	fp = fopen(name, "rb");
	if (fp == NULL) {
		printf("null\n");
		return NULL;
	}
	fseek(fp, 0, SEEK_END);//计算文件长度
	file_length = ftell(fp);
	rewind(fp);//指针移回开头
	buf = malloc(file_length);
	fread(buf, 1, file_length, fp);
	fclose(fp);
	return buf;
}





//歌单
/*
* 功能：读取.txt文件内容生成链表
* 参数：.txt文件指针，所有歌曲链表头
* 调用函数：findp_by_num
* 返回值：某个歌单内部所有歌曲所形成链表的头
*/
struct media* Creat_MyLitsHead(FILE* fp, struct media* head)
{
	struct media* myhead, * p, * q;
	int num;
	char temp[100];
	char str[200];

	p = (struct media*)malloc(sizeof(struct media));
	myhead = (struct media*)malloc(sizeof(struct media));
	q = myhead;

	while (fgets(str, 200, fp)) {        //读取一行
		for (int i = 0; (str[i] != '\n') && (str[i] != '\0'); i++) {
			if (str[i] != ',') {
				temp[i] = str[i];       //分割'，'前内容
			}
			else {
				temp[i + 1] = '\0';
				num = atoi(temp);       //歌曲序号
				p = (struct media*)malloc(sizeof(struct media));
				if (p && q) {
					p->num = num;
					strcpy_s(p->name,     //总歌单内检索，生成链表
						sizeof((findp_by_num(head, num))->name),
						(findp_by_num(head, num))->name);
					q->next = p;
					q = p;               
					break;                   
				}
			}
		}
	}
	if (p) {
		p->next = NULL;
	}
	inMyList = 1;      //全局变量设为1，表明现在在歌单内
	return myhead;
}

/*
* 功能：按序号在所有歌曲链表内检索歌曲
* 参数：所有歌曲链表头，要检索的歌曲的序号
* 返回值：指向该歌曲节点的指针
*/
struct media* findp_by_num(struct media* head, int num)
{
	struct media* p = head;
	while (p->next) {
		p = p->next;
		if (p->num == num) {
			break;
		}
	}
	return p;
}

/*
* 功能：请用户输入，判断歌单是否存在或为空并做相应处理
* 参数：所有歌曲链表头
* 调用函数：Creat_MyLitsHead
* 返回值：该歌单链表头
*/
struct media* display_a_list(struct media* head)
{
	FILE* fp;
	char listname[100];
	char pathname[100];

	//获取路径，打开文件
	printf("展示歌单（输入名称）：");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //不存在
		printc(30, "歌单不存在，请先创建歌单！");
		system("cls");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //歌单为空
		fclose(fp);
		system("CLS");
		printf("\n\t歌单为空\n");
		return NULL;
	}
	else {
		struct media* myhead = Creat_MyLitsHead(fp, head);
		fclose(fp);
		inMyList = 1;
		return myhead;
	}
}

/*
* 功能：新建歌单
*/
void new_list()
{
	FILE* fp;
	char listname[100];
	char pathname[100];

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("请输入新建的歌单名称：");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //打开失败，不存在，新建		
		fopen_s(&fp, pathname, "w");
		if (fp) {
			fclose(fp);
		}
		printf("新建歌单成功！");
		Sleep(3000);
	}
	else {         //打开成功，返回信息已存在
		printc(15, "歌单已存在！");
		fclose(fp);
	}
}

/*
* 功能：删除歌单
*/
void remove_list()
{
	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("删除歌单：");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {
		printc(20, "歌单不存在!");     
	}
	else {
		fclose(fp);
		int i = remove(pathname);
		if (i == 0) {
			printf("删除成功！");
			Sleep(3000);
		}
		else{
			printf("失败");
			Sleep(3000);
		}
		
	}
	
}
/*
* 功能：打印所有歌单
*/
void print_all_list()
{
	system("CLS");
	int i = 0;
	long Handle;

	//与检索.mp3文件操作相同，检索一个文件夹下.txt文件
	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\music\\*.txt", &FileInfo)) == -1L)
	{
		printf("\n\t暂无歌单，请创建歌单");
	}
	else
	{
		i++;
		printf("%s\n", FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			i++;
			printf("%s\n", FileInfo.name);
		}
		printf("共有%d个歌单\n", i);
	}
}

/*
* 功能：批量添加歌曲到歌单
* 参数：所有歌曲的链表头
*/
void add_to_List(struct media* head)
{
	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;
	int isFound = 0;

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("添加到歌单：");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {                //不存在则自动创建一个
		printc(50, "歌单不存在，已创建该歌单！");
		fopen_s(&fp, pathname, "w");
	}
	else if(fgetc(fp) == EOF) {	   //存在为空，用w打开
		fclose(fp);
		fopen_s(&fp, pathname, "w");
	}
	else if (fgetc(fp) != EOF) {    //存在不为空，用a打开，先追加一个换行到末尾
		fclose(fp);
		fopen_s(&fp, pathname, "a");
		fputc('\n', fp);
	}

	if (fp) {
		printf("添加的歌曲序号：");
		scanf_s("%s", str, sizeof(str));  //用户输入一个或多个序号，中间用','隔开
		sprintf(str, "%s,", str);

		//把输入的字符串变成一个个合适的int用head检索信息并输入
		int j = 0;
		int first = 0;

		if (str[0] > '9' || str[0] < '0') {
			printc(20, "退出添加");
			return;
		}
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] <= '9' && str[i] >= '0') { //连着的数字视为一个，赋给承接数组str1
				str1[j] = str[i];
				j++;
			}
			else {
				str1[j] = '\0';  //不连着了就算做一个字符串结束
				numb = atoi(str1);

				//写入文件，一些格式的调整
				struct media* p;
				for (p = head; p; p = p->next) {
					if (p->num == numb) {
						if (fp) {
							if (first == 0) {
								fprintf(fp, " %d, %s", p->num, p->name);
								first = 1;
							}
							else
								fprintf(fp, "\n %d, %s", p->num, p->name);
							isFound = 1;
							break;
						}
					}
				}
				if (isFound == 0) {
					printf("未找到编号为%d的歌曲\n", numb);
				}
				memset(str1, 0, j); //承接数组str1清0
				j = 0;
			}
		}		
	}
	if (fp) {
		fclose(fp);
	}	
	printf("\n");
	printf("添加成功");
	Sleep(3000);
}

/*
* 功能：删除歌单内歌曲(一次一个)
* 参数：所有歌曲的链表头
* 返回值：删改后歌单的链表头
*/
struct media* remove_in_list(struct media* head)
{
	FILE* fp;
	struct media* myhead, *p, *q;
	char listname[100], pathname[100];
	int num;

	//用户输入，获取路径，用r打开检测歌单是否存在
	printf("删改歌单：");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {
		printc(20,"歌单不存在！");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //歌单为空
		system("CLS");
		printf("\n\t歌单为空\n");
		fclose(fp);
		return NULL;
	}
	else {
		myhead = Creat_MyLitsHead(fp, head);   //生成歌单链表
		int n = Print_List(myhead);
		myFaceList();
		printf("删除的歌曲序号：");
		scanf("%d", &num);

		//歌单内检索歌曲
		p = myhead->next;
		if (p->num == num) {
			myhead->next = p->next;    
		}
		else {
			//找到后把该节点的前一节点指向后一节点
			q = (struct media*)malloc(sizeof(struct media));
			while (p->num != num) {
				q = p;                             
				if (p->next == NULL) {
					printf("未找到对应歌曲");
					Sleep(2500);
					fclose(fp);
					system("CLS");
					return myhead;
				}
				p = p->next;
			}
			q->next = p->next;
		}
		fclose(fp);

		//用w打开并清空文件，把删改过的链表信息按格式写进去
		p = myhead->next;
		fopen_s(&fp, pathname, "w");
		if (fp) {
			if (p == NULL) {
				fclose(fp);
				printf("删除成功");
				Sleep(2500);
				system("CLS");
				return NULL;
			}
			else {
				fprintf(fp, " %d, %s", p->num, p->name);
				while (p->next != NULL) {
					p = p->next;
					fprintf(fp, "\n %d, %s", p->num, p->name);
				}
				fclose(fp);
				printf("删除成功");
				Sleep(2500);
				system("CLS");
			}			
			
		}	
	}
	return myhead;
}

/*
* 功能：歌单内选曲播放
* 参数：所有歌曲的链表头，工作指针
* 返回值：歌曲指针
*/
struct media* iChoose_Song(struct media* myhead, struct media* P)
{
	if (myhead == NULL)//文件夹为空，头指针设为空
		return myhead;
	else
	{
		int num;
		int right = 1;
		struct media* p;//返回该工作指针
		p = myhead->next;
		do
		{
			printf("\n\t请输入歌曲序号: ");
			scanf("%d", &num);

			//清除缓冲区，如果用户输入字符将会死循环
			while (getchar() != '\n')
				continue;

			//检测输入序号是不是歌单内有的歌曲序号
			while (p->num != num) {
				p = p->next;
				if (p == NULL) {
					right = 0;
					break;
				}
			}
			if (right == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
				setSyscolor();
				printf("\t请输入歌曲对应序号！\n");
				fflush(stdin);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		} while (right == 0);

		if (P != NULL) Close_Play(P); //有正在播放的先退出
		return p;
	}

}

/*
* 功能：显示红色带下划线的警示信息，三秒后消失
* 参数：字符串长度，字符串内容
*/
void printc(int len, char* str)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
	printf("%s", str);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Sleep(3000);
	printf("\r");
	for (int i = 0; i < len; i++) {
		printf(" ");
	}
	printf("\r");
}



