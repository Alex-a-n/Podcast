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
#include <mmsystem.h>	         //mci��ͷ�ļ�
#include "LRC.h"
#pragma warning(disable:4996)
#pragma comment(lib, "winmm.lib")
#define PATH "D:\\music\\"      //·���궨�壬Ĭ���ļ����·��

int K = 0;//�жϵ�ǰ����״̬
int bkcolor = 0;
int textcolor = 0;
int syscolor = 0;//��ɫ����Ϊȫ�ֱ�����syscolor����������ʾ��logo����ʸ������ֵȣ�
                                    //textcolor������ʣ���ӡ�����б��赥�б��
int isFir = 0;  //�����ж��Ƿ��Ѿ��ǵ�һ��
int isEnd = 0;  //�����ж��Ƿ��Ѿ������һ��
int face1 = 0;  //�������˵�(��һ�����棩logo��ʽ
int face2 = 0;  //������������logo��ʽ

struct media            //������Ϣ�ṹ�壬��������ţ��ļ���
{
	int num;
	char name[100];
	struct media* next;
};

/*
* ���ܣ��������и�������
* ����ֵ�����и�������ͷ
*/
struct media* CreatHead()//�����ṹ���������������ļ���Ϣ����������ͷָ��
{
	struct media* head, * p, * q;
	head = (struct media*)malloc(sizeof(struct media));
	long Handle;
	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\music\\*.mp3", &FileInfo)) == -1L)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
		printf("\n\tû���ҵ�ƥ�����Ŀ\n\t�뽫.mp3�ļ�����D:\\music\\�ļ�����,������ѡ������\n");
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
* ���ܣ���ӡĳ��������������Ϣ
* ������ĳ������ͷ
* ����ֵ���������нڵ�����
*/
int Print_List(struct media* head)//��ӡ�ļ�������.mp3�ļ������������ļ���Ŀ�����Σ�������Ϣ����ͷ�ڵ㣩
{
	system("CLS");
	struct media* p1;
	p1 = head->next;
	int i = 0;
	setTextcolor();
	printf("\t  �X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
	while (p1 != NULL)
	{
		printf("\t  �U   %d. %s\n", p1->num, p1->name);
		p1 = p1->next;
		i++;
	}
	return i;
}

/*
* ���ܣ���ʾ���ڲ��ŵĸ���
* ������ĳ��������ָ��
* ����ֵ����
*/
void SongPlaying(struct media* p)//��ǰ���Ÿ���
{
	if (p == NULL)return;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setCursorPosition(25, 27);
	printf("\r%*c\r", 60, ' ');
	printf("\t\t\t\t��ǰ���ڲ��Ÿ�����%s ������", p->name);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

/*
* ���ܣ������и���ѡ�񲥷Ÿ���
* ������ĳ�����������ͷ������ָ�룬��Сֵ�������������ڵ�����
* ���ú�����play
* ����ֵ��ѡ�������ָ��
*/
struct media* Choose_Song(struct media* HEAD, struct media* P, int num, int max)//ѡ�����ѡ����Σ��б�ͷָ�룬����ָ��,����ֵ������ָ��
{
	if (HEAD == NULL)//�ļ���Ϊ�գ�ͷָ����Ϊ��
		return HEAD;
	else
	{
		struct media* p;//���ظù���ָ��
		p = HEAD->next;
		do
		{
			printf("\n\t������������: ");

			scanf("%d", &num);
			while (getchar() != '\n')continue;//���������������û������ַ�������ѭ��
			if (!(num > 0 && num <= max))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
				setSyscolor();
				printf("\t�����������Ӧ���1~ %d ��\n", max);
				fflush(stdin);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		} while (!(num > 0 && num <= max));//�õ��Ϸ������

		while (p->num != num) p = p->next;
		if (P != NULL)Close_Play(P);
		return p;
	}

}

/*
* ���ܣ�Ĭ���б��ڲ��Ҹ�����������������
* ������Ĭ���б����������ͷ������ָ�룬��Сֵ����������
* ���ú�����Choose_Song
* ����ֵ�����������Ĺ���ָ��
*/
struct media* FindSong(struct media* head, struct media* p, int num, int max)
{
	char str[100] = { 0 };
	int i = 0;
	char choice;
	struct media* pCur = head->next;

	system("CLS");
	Print_List(head);
	printf("���������������ĸ���:");
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
			if (strstr(pCur->name, str) != NULL)  //�������ĸ���	
			{
				printf("\t%d.%s\n", pCur->num, pCur->name);
				i++;
			}
			pCur = pCur->next;
		}

	}

	if (i == 0)
	{
		printf("\nδ�ҵ��ø���");
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
* ���ܣ����Ÿ���
* ������ĳ�����������ͷ������ָ�룬�����������ڵ�����
* ���ú�����SongPlaying ,progress_Display
* ����ֵ����
*/
void play(struct meida* head, struct media* p, int max)
{
	char cmd[100];
	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//��ȡ����
	sprintf(cmd, "open %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);
	sprintf(cmd, "play %s", pathname);
	mciSendString(cmd, NULL, 0, NULL);

	K = 1;
	SongPlaying(p);
	progress_Display(head, p, max);
}

/*
* ���ܣ�ֹͣ����
* ������ĳ������Ĺ���ָ��
* ����ֵ����
*/
void Close_Play(struct media* p)//ֹͣ���ţ���ʵ�ǹر��ļ���
{
	if (p == NULL)
	{
		if (ch1 != 'l')//�����������������˳�ʱ��ɾ������жϻ�����ʾ�������ʾ����Խ�ch1����Ϊȫ�ֱ���
		{
			setSyscolor();
			printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
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

	K = 0;//�޸��ļ�״̬Ϊ��ͣ
}

/*
* ���ܣ���ͣ/�������Ÿ���
* ������ĳ������Ĺ���ָ��
* ����ֵ����
*/
void Pause_Play(struct media* p)//��ͣ�Ͳ��źϲ�
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return;
	}

	char pathname[200];
	char cmd[200];

	if (K == 1)//����״̬��ִ����ͣ
	{
		sprintf_s(pathname, sizeof(pathname), "%s%s", PATH, p->name); //��ȡ��ַ
		GetShortPathName(pathname, pathname, 50);     //��ȡ����
		sprintf_s(cmd, sizeof(cmd), "pause %s", pathname);     //��ȡ����
		mciSendString(cmd, NULL, 0, NULL);     //ִ��
		K = 0;
	}
	else if (K == 0)//��ͣ/ֹͣ״̬��ִ�в���
	{
		sprintf_s(pathname, sizeof(pathname), "%s%s", PATH, p->name);
		GetShortPathName(pathname, pathname, 50);
		sprintf_s(cmd, sizeof(cmd), "play %s", pathname);
		mciSendString(cmd, NULL, 0, NULL);
		K = 1;
	}

}

/*
* ���ܣ�������һ������
* ������ĳ�����������ͷ������ָ��
* ����ֵ������ָ��
*/
struct media* Last_Play(struct media* head, struct media* p)//��һ��
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return p;
	}
	if (p != head->next) {
		Close_Play(p);//�رյ�ǰ����
		struct media* q;
		q = (struct media*)malloc(sizeof(struct media));
		q = head->next;
		while (q->next != p)q = q->next;//��ָ��ָ����һ��
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
		printf("\t\t\t��ǰ�ǵ�һ�ף�");
		Sleep(500);
		printf("\r");
		printf("\t\t\t                ");
		printf("\r");
		printf("\n");
	}
	return p;//���ع���ָ��
}

/*
* ���ܣ�������һ������
* ������ĳ�����������ͷ������ָ��
* ����ֵ������ָ��
*/
struct media* Next_Play(struct media* head, struct media* p)//��һ��
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return p;
	}
	if (p->next != NULL)
	{
		Close_Play(p);//�رղ����ļ�
		p = p->next;//ָ��ָ����һ��
		isEnd = 0;
	}
	else
	{
		if (isEnd == 1) {
			return p;
		}
		isEnd = 1;
		printf("\n");
		printf("\t\t\t��ǰ�����һ�ף�");
		Sleep(500);
		printf("\r");
		printf("\t\t\t                 ");
		printf("\r");
		printf("\n");
	}
	return p;//���ع���ָ��

}


/*
* ���ܣ���С����
* ������ĳ������Ĺ���ָ��
* ����ֵ����
*/
void VolDown(struct media* p)//������С���ļ���ʼ����ʱĬ������Ϊ1000��ÿ�οɸ���50��
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return;
	}
	TCHAR cmd[256]; // ý������
	TCHAR volume[256]; // ����(�ַ���)
	int nVolume; // ����(����)

	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);

	sprintf(cmd, "status %s volume", pathname); //pathname2Ϊ���ֵ�·��
	mciSendString(cmd, volume, sizeof(volume), 0); // ��ȡ��ǰ������ volume �ַ�����

	nVolume = atoi(volume); // �ַ���ת��Ϊ����

	sprintf(cmd, "setaudio %s volume to %i", pathname, nVolume - 50); // ����ý��������������� 50
	mciSendString(cmd, NULL, 0, NULL); // ִ��ý������
}

/*
* ���ܣ���������
* ������ĳ������Ĺ���ָ��
* ����ֵ����
*/
void VolUp(struct media* p)//��������
{
	if (p == NULL)
	{
		setSyscolor();
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return;
	}
	TCHAR cmd[256]; // ý������
	TCHAR volume[256]; // ����(�ַ���)
	int nVolume; // ����(����)

	char pathname[100];
	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);

	sprintf(cmd, "status %s volume", pathname); //pathname2Ϊ���ֵ�·��
	mciSendString(cmd, volume, sizeof(volume), 0); // ��ȡ��ǰ������ volume �ַ�����

	nVolume = atoi(volume); // �ַ���ת��Ϊ����

	sprintf(cmd, "setaudio %s volume to %i", pathname, nVolume + 50); // ����ý��������������� 50
	mciSendString(cmd, NULL, 0, NULL); // ִ��ý������
}

/*
* ���ܣ����5s
* ������ĳ������Ĺ���ָ��
* ����ֵ����
*/
void go(struct media* p)
{
	if (p == NULL)
	{
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return;
	}
	int time = Progress(p) * 1000;
	int nPosition;
	char position[200];
	char pathname[200];
	char cmd[200];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//��ȡ����
	sprintf(cmd, "status %s position", pathname);
	mciSendString(cmd, position, sizeof(position), 0);
	nPosition = atoi(position) + 5 * 1000;//��ǰλ��

	if (nPosition > time) {
		nPosition = time;
	}
	sprintf(cmd, "play %s from %d", pathname, nPosition);
	mciSendString(cmd, NULL, 0, NULL); // ���5000ms
}

/*
* ���ܣ�����5s
* ������ĳ������Ĺ���ָ��
* ����ֵ����
*/
void back(struct media* p)
{
	if (p == NULL)
	{
		printf("\n\t\t\t��ǰ�޸������ڲ���,��ѡ������\n");
		Sleep(500);
		return;
	}

	int itime;
	int nPosition;
	char position[200];
	char pathname[200];
	char cmd[200];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//��ȡ����
	sprintf(cmd, "status %s position", pathname);
	mciSendString(cmd, position, sizeof(position), 0);
	nPosition = atoi(position) - 5 * 1000;//��ǰλ��

	if (nPosition < 0) {
		nPosition = 0;
	}
	sprintf(cmd, "play %s from %d", pathname, nPosition);
	mciSendString(cmd, NULL, 0, NULL); // ���5000ms
}

/*
* ���ܣ�����ϵͳ������ɫ���ı�������ɫ
* ��������
* ����ֵ����
*/
void changeColor() {
	system("CLS");
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\t\t\t\t\t\t0--------------ϵͳ��ɫ\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	printf("\t\t\t\t\t\t1--------------����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("\t\t\t\t\t\t2--------------����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("\t\t\t\t\t\t3--------------����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("\t\t\t\t\t\t4--------------���\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("\t\t\t\t\t\t5--------------�Ϻ�\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("\t\t\t\t\t\t6--------------���\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\t\t\t\t\t\t7--------------��ɫ\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	printf("\t\t\t\t\t\t8--------------���\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("\t\t\t\t\t\t9--------------��ɫ\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\t\t\t\t\t\t10-------------ǳ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("\t\t\t\t\t\t11-------------ǳ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\t\t\t\t\t\t12-------------��ɫ\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("\t\t\t\t\t\t13-------------õ��\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("\t\t\t\t\t\t14-------------��ɫ\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\t\t\t\t\t\t15-------------����\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U    ����������Ҫ�ı��ϵͳ������ɫ   �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	scanf("%d", &syscolor);
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U    ����������Ҫ�ı���ı�������ɫ   �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	scanf("%d", &textcolor);
}
/*
* ���ܣ�����ȫ�ֱ���syscolor����ϵͳ������ɫ
* ��������
* ����ֵ����
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
* ���ܣ�����ȫ�ֱ���syscolor�����ı�������ɫ
* ��������
* ����ֵ����
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
* ���ܣ�����ȫ�ֱ���face1�������˵�logo
* ��������
* ����ֵ����
*/
void  changeface1() {
	system("CLS");
	printf("\n\n\n");
	setSyscolor();
	printf("\t\t\t\t���� 0��Ĭ�ϣ� \n");
	printf("\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t�U          __  _______ _____                                  �U\n");
	printf("\t\t\t\t�U         /  |/  / __ \\__  /                                  �U\n");
	printf("\t\t\t\t�U        / /|_/ / /_/ //_ <                                   �U\n");
	printf("\t\t\t\t�U       / /  / / ____/__/ /                                   �U\n");
	printf("\t\t\t\t�U      /_/__/_/_/__ /___ /_ ___________      _____ ______     �U\n");
	printf("\t\t\t\t�U     / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/     �U\n");
	printf("\t\t\t\t�U    / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /        �U\n");
	printf("\t\t\t\t�U   / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /         �U\n");
	printf("\t\t\t\t�U  /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          �U\n");
	printf("\t\t\t\t�U                                                             �U\n");
	printf("\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	printf("\t\t\t\t���� 1 \n");
	printf("\t\t\t\t /$$$$$$$                 /$$                                 /$$  \n ");
	printf("\t\t\t\t| $$__  $$               | $$                                | $$  \n  ");
	printf("\t\t\t\t| $$  \\ $$ /$$$$$$   /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$ \n");
	printf("\t\t\t\t| $$$$$$$//$$__  $$ /$$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  \n");
	printf("\t\t\t\t| $$____/| $$  \\ $$| $$  | $$| $$        /$$$$$$$|  $$$$$$   | $$    \n");
	printf("\t\t\t\t| $$     | $$  | $$| $$  | $$| $$       /$$__  $$ \\____  $$  | $$ /$$\n");
	printf("\t\t\t\t| $$     |  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/\n");
	printf("\t\t\t\t|__/      \\______/  \\_______/ \\_______/ \\_______/|_______/    \\___/  \n");
	printf("\n");
	printf("\t\t\t\t���� 2 \n");
	printf("\n");
	printf("         \t\t        �������������[  �������������[ �������������[  �������������[ �����������[ ���������������[����������������  \n");
	printf("         \t\t        �����X�T�T�����[�����X�T�T�T�����[�����X�T�T�����[�����X�T�T�T�T�a�����X�T�T�����[�����X�T�T�T�T�a�^�T�T�����X�T�T�a  \n");
	printf("         \t\t 	�������������X�a�����U   �����U�����U  �����U�����U     ���������������U���������������[   �����U      \n");
	printf("         \t\t 	�����X�T�T�T�a �����U   �����U�����U  �����U�����U     �����X�T�T�����U�^�T�T�T�T�����U   �����U      \n");
	printf("         \t\t 	�����U     �^�������������X�a�������������X�a�^�������������[�����U  �����U���������������U   �����U    \n");
	printf("         \t\t 	�^�T�a      �^�T�T�T�T�T�a �^�T�T�T�T�T�a  �^�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a   �^�T�a      \n\n");
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U    ����������Ҫ�ı��ϵͳ������ʽ   �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	scanf("%d", &face1);
}
/*
* ���ܣ�����ȫ�ֱ���face1��ӡ���˵�logo
* ��������
* ����ֵ����
*/
void setface1() {
	switch (face1) {
	case 0:
		printf("\n\n\n");
		printf("\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
		printf("\t\t\t\t�U          __  _______ _____                                  �U\n");
		printf("\t\t\t\t�U         /  |/  / __ \\__  /                                  �U\n");
		printf("\t\t\t\t�U        / /|_/ / /_/ //_ <                                   �U\n");
		printf("\t\t\t\t�U       / /  / / ____/__/ /                                   �U\n");
		printf("\t\t\t\t�U      /_/__/_/_/__ /___ /_ ___________      _____ ______     �U\n");
		printf("\t\t\t\t�U     / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/     �U\n");
		printf("\t\t\t\t�U    / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /        �U\n");
		printf("\t\t\t\t�U   / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /         �U\n");
		printf("\t\t\t\t�U  /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          �U\n");
		printf("\t\t\t\t�U                                                             �U\n");
		printf("\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n\n\n");
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

		printf("         \t\t        �������������[  �������������[ �������������[  �������������[ �����������[ ���������������[����������������  \n");
		printf("         \t\t        �����X�T�T�����[�����X�T�T�T�����[�����X�T�T�����[�����X�T�T�T�T�a�����X�T�T�����[�����X�T�T�T�T�a�^�T�T�����X�T�T�a  \n");
		printf("         \t\t 	�������������X�a�����U   �����U�����U  �����U�����U     ���������������U���������������[   �����U      \n");
		printf("         \t\t 	�����X�T�T�T�a �����U   �����U�����U  �����U�����U     �����X�T�T�����U�^�T�T�T�T�����U   �����U      \n");
		printf("         \t\t 	�����U     �^�������������X�a�������������X�a�^�������������[�����U  �����U���������������U   �����U    \n");
		printf("         \t\t 	�^�T�a      �^�T�T�T�T�T�a �^�T�T�T�T�T�a  �^�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a   �^�T�a      \n\n\n\n\n");
		break;
	}
}
/*
* ���ܣ�����ȫ�ֱ���face2������������logo
* ��������
* ����ֵ����
*/
void  changeface2() {
	system("CLS");
	printf("\n\n\n");
	setSyscolor();
	printf("\t\t\t\t���� 0��Ĭ�ϣ� \n");
	printf("\t\t                        _ __   _____ ___  _  _________       _____ ______     \n");
	printf("\t\t                       / __ \\/  __  / /__\\ \\/  ___/ / \\ \\   / ____/__  __/      \n");
	printf("\t\t ________________     / /_/ / /  / / /   | / /   / /__| |  /_/_ _   / /     ________________   \n");
	printf("\t\t/___/___/___/___/    / ____/ /__/ / /___/ / /__   /___| | ____/ /  / /     /___/___/___/___/      \n");
	printf("\t\t                    /_/   /______/_/___/_/_/___/ /    | |/____ /  /_/          \n");
	printf("\n\n");
	printf("\t\t\t\t���� 1 \n");
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
	printf("\t\t\t\t���� 2 \n");
	printf("\n");
	printf("         \t\t        �������������[  �������������[ �������������[  �������������[ �����������[ ���������������[����������������  \n");
	printf("         \t\t        �����X�T�T�����[�����X�T�T�T�����[�����X�T�T�����[�����X�T�T�T�T�a�����X�T�T�����[�����X�T�T�T�T�a�^�T�T�����X�T�T�a  \n");
	printf("         \t\t 	�������������X�a�����U   �����U�����U  �����U�����U     ���������������U���������������[   �����U      \n");
	printf("         \t\t 	�����X�T�T�T�a �����U   �����U�����U  �����U�����U     �����X�T�T�����U�^�T�T�T�T�����U   �����U      \n");
	printf("         \t\t 	�����U     �^�������������X�a�������������X�a�^�������������[�����U  �����U���������������U   �����U    \n");
	printf("         \t\t 	�^�T�a      �^�T�T�T�T�T�a �^�T�T�T�T�T�a  �^�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a   �^�T�a      \n");
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U    ����������Ҫ�ı�Ĳ��Ž�����ʽ   �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
	scanf("%d", &face2);
}
/*
* ���ܣ�����ȫ�ֱ���face2��ӡ��������logo
* ��������
* ����ֵ����
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
		printf("         \t\t        �������������[  �������������[ �������������[  �������������[ �����������[ ���������������[����������������  \n");
		printf("         \t\t        �����X�T�T�����[�����X�T�T�T�����[�����X�T�T�����[�����X�T�T�T�T�a�����X�T�T�����[�����X�T�T�T�T�a�^�T�T�����X�T�T�a  \n");
		printf("         \t\t 	�������������X�a�����U   �����U�����U  �����U�����U     ���������������U���������������[   �����U      \n");
		printf("         \t\t 	�����X�T�T�T�a �����U   �����U�����U  �����U�����U     �����X�T�T�����U�^�T�T�T�T�����U   �����U      \n");
		printf("         \t\t 	�����U     �^�������������X�a�������������X�a�^�������������[�����U  �����U���������������U   �����U    \n");
		printf("         \t\t 	�^�T�a      �^�T�T�T�T�T�a �^�T�T�T�T�T�a  �^�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a   �^�T�a      \n\n");
		break;
	}
}

/*
* ���ܣ���λ���λ��
* ��������������x,y
* ����ֵ����
*/
void setCursorPosition(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
* ���ܣ���ȡ������ʱ��
* ����������ָ��
* ����ֵ��������ʱ�����룩
*/
int Progress(struct media* p) {

	int time;
	char len[100];
	char pathname[100];
	char cmd[100];

	sprintf(pathname, "%s%s", PATH, p->name);
	GetShortPathName(pathname, pathname, 50);//��ȡ����
	sprintf(cmd, "status %s length", pathname);
	mciSendString(cmd, len, sizeof(len), NULL);//��ȡʱ�䣬��λΪ����
	time = atoi(len) / 1000;
	return time;
}

/*
* ���ܣ�ʱ��/������/�����ʾ�������й��ܽ����ҳ����ת
* ������ĳ����ͷ������ָ�룬�����и�������
* ���ú��������в��Ź��ܺ�������ȡʱ�亯�������������غ���
* ����ֵ����
*/
void progress_Display(struct media* head, struct media* p, int max) {

	srand((unsigned)time(NULL));
	if (p == NULL) return;
	int time = Progress(p); //��ȡ����������	
	//��������ض���
	int x = 68; 
	int y = 24;
	double pro = 1 / (double)37;
	int min = 0;
	int second = 0;
	int mtime = time / 60;
	int stime = time % 60;
	int xp = x + 6;
	//�����ض���
	LRC* heads = NULL, * p_new = NULL, * ps1 = NULL, * ps0 = NULL, * ps2 = NULL, * ps = NULL;
	char* str = NULL, * lrc_buf = NULL;
	char file_name[20];
	int i, j, k, len;
	int time_buf[5];
	char* q[200];

	//��λ����ʽ��ӡ������
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
	
	lrc_buf = read_file(p); //��ȡ���и��ָ��
	len = msg_deal(lrc_buf, q, "\r\n"); //�ָ��ʣ���ȡÿ�и�ʺ�������


	//�ָ�ÿ�и�ʵ�ʱ��͸��
	for (int t = 0; (t >= 0) && (t <= time); t++) {

		for (k = 0; k < len; k++)
		{
			str = q[k];
			i = 0;
			while (*str == '[')//��ʱ���¼��������
			{
				time_buf[i++] = atoi(str + 1) * 60 + atoi(str + 4);
				str += 10;
			}
			for (j = 0; j < i; j++)
			{
				p_new = (LRC*)malloc(sizeof(LRC));//�����µĽڵ�
				p_new->m_time = time_buf[j];
				strcpy(p_new->lrc_buf, str);
				heads = link_insert(heads, p_new);
			}
		}
		if (t < heads->next->m_time + 1) {

			fflush(stdout);//���ˢ��
			ps2 = link_search(heads, t);
			if (ps2 != NULL) {
				//printf("1\n");
				setCursorPosition(80, 20);
				setSyscolor();
				printf("\r%*c\r", 60, ' ');
				printf(" \t\t%s\n", ps2->lrc_buf);//��ӡ����ʱ��
				setCursorPosition(80, 15);
				if (ps1 != NULL) {
					setTextcolor();
					printf("\r%*c\r", 60, ' ');
					printf(" \t\t%s\n", ps1->lrc_buf);//��ӡ����ʱ��
					//printf("22\n");
				}
				setCursorPosition(80, 10);
				if (ps0 != NULL) {
					setTextcolor();
					printf("\r%*c\r", 60, ' ');
					printf(" \t\t%s\n", ps0->lrc_buf);//��ӡ����ʱ��
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
			if (GetKeyState(VK_SPACE) < 0) {//��ͣ
				Pause_Play(p);
				setbuf(stdin, NULL);
				setCursorPosition(x, y + 1);
				char a = getchar();
				Pause_Play(p);
			}
			else if (GetKeyState(VK_RETURN) < 0) { //ֹͣ
				Close_Play(p);
				return;
			}
			else if (GetKeyState(VK_UP) < 0) { //��һ��
				p = Last_Play(head, p);
				if (isFir == 0) {
					play(head, p, max);
				}			
			}
			else if (GetKeyState(VK_DOWN) < 0) { //��һ��
				p = Next_Play(head, p);
				if (isEnd == 0) {
					play(head, p, max);
				}
			}
			else if (GetKeyState(VK_OEM_PLUS) < 0) { //����+
				VolUp(p);
			}
			else if (GetKeyState(VK_OEM_MINUS) < 0) { //����-
				VolDown(p);
			}
			else if (GetKeyState(VK_TAB) < 0) { //������һ��ҳ��
				chooseSong2(head, p);
			}
			else if (GetKeyState(VK_RIGHT) < 0) { //���
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
			else if (GetKeyState(VK_LEFT) < 0) { //����               //�¼�
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
	Sleep(1500);                                       //����������ģʽ
	if (mode == 1) { //����ѭ��
		Close_Play(p);
		play(head, p, max);
	}
	else if (mode == 2) {//�б�ѭ��
		if (p->next == NULL) {
			p = head->next;
		}
		else {
			p = p->next;
		}
		play(head, p, max);
	}
	else if (mode == 3) {//���
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
* ���ܣ��ڲ��Ž���ѡȡ����������ţ���ǰ��ChooseSong��ͬ
* ������ĳ�����������ͷ������ָ��
* ���ú�����play
* ����ֵ������ָ��
*/
struct media* chooseSong2(struct media* HEAD, struct media* P)//ѡ�����ѡ����Σ��б�ͷָ�룬����ָ��,����ֵ������ָ��,��ǰ��ѡ������ͬ���Ǵ�ӡ�����б�ͬ
{
	if (HEAD == NULL)//�ļ���Ϊ�գ�ͷָ����Ϊ��
		return HEAD;
	else
	{
		int max = Print_List(HEAD);
		int num = -1;
		int ch;
		struct media* p;//���ظù���ָ��
		p = HEAD->next;
		do
		{
			setSyscolor();
			printf("\n\t������������: ");
			setbuf(stdin, NULL);
			scanf("%d", &num);
			//fflush(stdin);
			while ((ch = getchar()) != EOF && ch != '\n')continue;//���������
				//printf("ceshi:%d\n", num);
			if (!(num > 0 && num <= max))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
				setSyscolor();
				printf("\t�����������Ӧ���1~ %d ��\n", max);
				fflush(stdin);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		} while (!(num > 0 && num <= max));//�õ��Ϸ������

		while (p->num != num)p = p->next;
		setSyscolor();
		if (P != NULL)Close_Play(P);
		facePlayer();
		play(HEAD, p, max);
		return p;
	}
}

/*
* ���ܣ��и���
* ���������и���ַ���ָ�룬�ַ������顪������־��ʣ��ָ����ַ�
* ����ֵ���������
*/
int msg_deal(char* msg_src, char* msg_done[], char* str)//�ָ��ַ���Ϊһ���ַ���
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
* ���ܣ����־��ĸ�ʲ���˫��������
* �������������ͷ������ָ��
*/
LRC* link_insert(LRC* head, LRC* p_new)
{
	LRC* pb;
	if (head == NULL)//������ʱ
	{
		head = p_new;
		head->next = p_new;
		head->front = p_new;
	}
	else//��һ�������Ͻڵ�ʱ
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
* ���ܣ����ݲ���ʱ��ǰʱ��������Ӧʱ���ĸ��
* �������������ͷ������ָ��
* ����ֵ������ָ���NULL
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
* ���ܣ����ݵ�ǰ���ŵĸ���������Ӧ����ļ�
* ��������ǰ���Ÿ�����ָ��
* ����ֵ����Ӧ����ļ��е�ȫ���ַ�
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
	fseek(fp, 0, SEEK_END);//�����ļ�����
	file_length = ftell(fp);
	rewind(fp);//ָ���ƻؿ�ͷ
	buf = malloc(file_length);
	fread(buf, 1, file_length, fp);
	fclose(fp);
	return buf;
}





//�赥
/*
* ���ܣ���ȡ.txt�ļ�������������
* ������.txt�ļ�ָ�룬���и�������ͷ
* ���ú�����findp_by_num
* ����ֵ��ĳ���赥�ڲ����и������γ������ͷ
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

	while (fgets(str, 200, fp)) {        //��ȡһ��
		for (int i = 0; (str[i] != '\n') && (str[i] != '\0'); i++) {
			if (str[i] != ',') {
				temp[i] = str[i];       //�ָ�'��'ǰ����
			}
			else {
				temp[i + 1] = '\0';
				num = atoi(temp);       //�������
				p = (struct media*)malloc(sizeof(struct media));
				if (p && q) {
					p->num = num;
					strcpy_s(p->name,     //�ܸ赥�ڼ�������������
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
	inMyList = 1;      //ȫ�ֱ�����Ϊ1�����������ڸ赥��
	return myhead;
}

/*
* ���ܣ�����������и��������ڼ�������
* ���������и�������ͷ��Ҫ�����ĸ��������
* ����ֵ��ָ��ø����ڵ��ָ��
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
* ���ܣ����û����룬�жϸ赥�Ƿ���ڻ�Ϊ�ղ�����Ӧ����
* ���������и�������ͷ
* ���ú�����Creat_MyLitsHead
* ����ֵ���ø赥����ͷ
*/
struct media* display_a_list(struct media* head)
{
	FILE* fp;
	char listname[100];
	char pathname[100];

	//��ȡ·�������ļ�
	printf("չʾ�赥���������ƣ���");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //������
		printc(30, "�赥�����ڣ����ȴ����赥��");
		system("cls");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //�赥Ϊ��
		fclose(fp);
		system("CLS");
		printf("\n\t�赥Ϊ��\n");
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
* ���ܣ��½��赥
*/
void new_list()
{
	FILE* fp;
	char listname[100];
	char pathname[100];

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("�������½��ĸ赥���ƣ�");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {  //��ʧ�ܣ������ڣ��½�		
		fopen_s(&fp, pathname, "w");
		if (fp) {
			fclose(fp);
		}
		printf("�½��赥�ɹ���");
		Sleep(3000);
	}
	else {         //�򿪳ɹ���������Ϣ�Ѵ���
		printc(15, "�赥�Ѵ��ڣ�");
		fclose(fp);
	}
}

/*
* ���ܣ�ɾ���赥
*/
void remove_list()
{
	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("ɾ���赥��");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {
		printc(20, "�赥������!");     
	}
	else {
		fclose(fp);
		int i = remove(pathname);
		if (i == 0) {
			printf("ɾ���ɹ���");
			Sleep(3000);
		}
		else{
			printf("ʧ��");
			Sleep(3000);
		}
		
	}
	
}
/*
* ���ܣ���ӡ���и赥
*/
void print_all_list()
{
	system("CLS");
	int i = 0;
	long Handle;

	//�����.mp3�ļ�������ͬ������һ���ļ�����.txt�ļ�
	struct _finddata_t FileInfo;
	if ((Handle = _findfirst("D:\\music\\*.txt", &FileInfo)) == -1L)
	{
		printf("\n\t���޸赥���봴���赥");
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
		printf("����%d���赥\n", i);
	}
}

/*
* ���ܣ�������Ӹ������赥
* ���������и���������ͷ
*/
void add_to_List(struct media* head)
{
	FILE* fp;
	char listname[100], pathname[100], str[200], str1[20];
	int numb = 0;
	int isFound = 0;

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("��ӵ��赥��");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");

	if (er != 0) {                //���������Զ�����һ��
		printc(50, "�赥�����ڣ��Ѵ����ø赥��");
		fopen_s(&fp, pathname, "w");
	}
	else if(fgetc(fp) == EOF) {	   //����Ϊ�գ���w��
		fclose(fp);
		fopen_s(&fp, pathname, "w");
	}
	else if (fgetc(fp) != EOF) {    //���ڲ�Ϊ�գ���a�򿪣���׷��һ�����е�ĩβ
		fclose(fp);
		fopen_s(&fp, pathname, "a");
		fputc('\n', fp);
	}

	if (fp) {
		printf("��ӵĸ�����ţ�");
		scanf_s("%s", str, sizeof(str));  //�û�����һ��������ţ��м���','����
		sprintf(str, "%s,", str);

		//��������ַ������һ�������ʵ�int��head������Ϣ������
		int j = 0;
		int first = 0;

		if (str[0] > '9' || str[0] < '0') {
			printc(20, "�˳����");
			return;
		}
		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] <= '9' && str[i] >= '0') { //���ŵ�������Ϊһ���������н�����str1
				str1[j] = str[i];
				j++;
			}
			else {
				str1[j] = '\0';  //�������˾�����һ���ַ�������
				numb = atoi(str1);

				//д���ļ���һЩ��ʽ�ĵ���
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
					printf("δ�ҵ����Ϊ%d�ĸ���\n", numb);
				}
				memset(str1, 0, j); //�н�����str1��0
				j = 0;
			}
		}		
	}
	if (fp) {
		fclose(fp);
	}	
	printf("\n");
	printf("��ӳɹ�");
	Sleep(3000);
}

/*
* ���ܣ�ɾ���赥�ڸ���(һ��һ��)
* ���������и���������ͷ
* ����ֵ��ɾ�ĺ�赥������ͷ
*/
struct media* remove_in_list(struct media* head)
{
	FILE* fp;
	struct media* myhead, *p, *q;
	char listname[100], pathname[100];
	int num;

	//�û����룬��ȡ·������r�򿪼��赥�Ƿ����
	printf("ɾ�ĸ赥��");
	scanf_s("%s", listname, sizeof(listname));
	sprintf_s(pathname, sizeof(pathname), "%s%s.txt", PATH, listname);
	errno_t er = fopen_s(&fp, pathname, "r");
	if (er != 0) {
		printc(20,"�赥�����ڣ�");
		return NULL;
	}
	else if (fgetc(fp) == EOF) {  //�赥Ϊ��
		system("CLS");
		printf("\n\t�赥Ϊ��\n");
		fclose(fp);
		return NULL;
	}
	else {
		myhead = Creat_MyLitsHead(fp, head);   //���ɸ赥����
		int n = Print_List(myhead);
		myFaceList();
		printf("ɾ���ĸ�����ţ�");
		scanf("%d", &num);

		//�赥�ڼ�������
		p = myhead->next;
		if (p->num == num) {
			myhead->next = p->next;    
		}
		else {
			//�ҵ���Ѹýڵ��ǰһ�ڵ�ָ���һ�ڵ�
			q = (struct media*)malloc(sizeof(struct media));
			while (p->num != num) {
				q = p;                             
				if (p->next == NULL) {
					printf("δ�ҵ���Ӧ����");
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

		//��w�򿪲�����ļ�����ɾ�Ĺ���������Ϣ����ʽд��ȥ
		p = myhead->next;
		fopen_s(&fp, pathname, "w");
		if (fp) {
			if (p == NULL) {
				fclose(fp);
				printf("ɾ���ɹ�");
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
				printf("ɾ���ɹ�");
				Sleep(2500);
				system("CLS");
			}			
			
		}	
	}
	return myhead;
}

/*
* ���ܣ��赥��ѡ������
* ���������и���������ͷ������ָ��
* ����ֵ������ָ��
*/
struct media* iChoose_Song(struct media* myhead, struct media* P)
{
	if (myhead == NULL)//�ļ���Ϊ�գ�ͷָ����Ϊ��
		return myhead;
	else
	{
		int num;
		int right = 1;
		struct media* p;//���ظù���ָ��
		p = myhead->next;
		do
		{
			printf("\n\t������������: ");
			scanf("%d", &num);

			//���������������û������ַ�������ѭ��
			while (getchar() != '\n')
				continue;

			//�����������ǲ��Ǹ赥���еĸ������
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
				printf("\t�����������Ӧ��ţ�\n");
				fflush(stdin);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
					FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
		} while (right == 0);

		if (P != NULL) Close_Play(P); //�����ڲ��ŵ����˳�
		return p;
	}

}

/*
* ���ܣ���ʾ��ɫ���»��ߵľ�ʾ��Ϣ���������ʧ
* �������ַ������ȣ��ַ�������
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



