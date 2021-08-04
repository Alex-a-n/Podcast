#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"face.h"
#include"switch.h"
#include"function.h"
#include<windows.h>

//char choose;//定义选择变量
char ch1;//播放器菜单的选项变量，设为全局变量是为了方便在另一个函数中不传参使用
struct media* HEAD, * MYHEAD, * P;//定义头指针和工作指针
int inMyList = 0;
int mode = 1;

void Main_Switch()//第一个界面
{
	int flag = 1;
	int ch;
	while (flag) {
		faceFirst();
		ch = _getch() - 48;
		switch (ch)
		{
		case 1:List_Switch(); break;
		case 2:state(); break;
		case 3:info(); break;
		case 4:changeColor(); changeface1(); changeface2(); break;
		case 0:flag = 0; break;
		default:break;
		}
	}
}

void List_Switch()
{
	P = NULL;
	int flag = 1;
	while (flag) {
		HEAD = CreatHead();
		int max = Print_List(HEAD);
		inMyList = 0;
		int num = -1;
		faceList();
		ch1 = _getch();
		switch (ch1)
		{
		case 'x':Mode_Switch(); break;
		case 't':MYHEAD = NULL; myList_Switch(); break;
		case 'p':P = Choose_Song(HEAD, P, num, max); P = Player_Switch(HEAD, P, max);  break;
		case 'q':P = FindSong(HEAD, P, num, max); P = Player_Switch(HEAD, P, max); system("pause"); break;
		case 'l':flag = 0; break;
		default:break;
		}
	}
}

void myList_Switch() 
{
	system("cls");
	if (MYHEAD != NULL) {
		Print_List(MYHEAD);
	}
	P = NULL;
	//print_all_list();
	//printf("请选择操作");
	int flag = 1;
	int max;
	int num = -1;
	while (flag) {
		myFaceList();

		ch1 = _getch();
		switch (ch1)
		{
		case 'x':new_list(); system("cls"); break;
		case 't': remove_list(); system("cls"); break;
		case 'p':
			MYHEAD = display_a_list(HEAD);
			if (MYHEAD != NULL)
				max = Print_List(MYHEAD);
			break;
		case 'q':
			if (MYHEAD == NULL) {
				system("cls");
				printf("请先选择要展示的歌单");
			}
			else {
				P = iChoose_Song(MYHEAD, P);
				P = Player_Switch(MYHEAD, P, max);
			}
			break;
		case 'l':Print_List(HEAD); myFaceList();
			add_to_List(HEAD); system("cls"); break;
		case 'd':MYHEAD = remove_in_list(HEAD); break;
		case 'a':print_all_list(); break;
		case 'e':flag = 0; break;
		default:system("cls");
		}
	}
}



struct media* Player_Switch(struct media* HEAD, struct media* P, int max)
{
	//关闭歌曲之后自动跳回上一个页面
	facePlayer();
	play(HEAD, P, max);
	if (inMyList == 0) {
		List_Switch();
	}
	else if (inMyList == 1) {
		myList_Switch();
	}
	return P;
}

void  Mode_Switch() {
	facemode();
	mode = _getch() - 48;
}