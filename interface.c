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
	printf("\t\t\t\t      1.�����б�\t\t\t2.ʹ��˵��\n\n");
	printf("\t\t\t\t      3.������Ϣ\t\t\t4.����Ƥ��\n\n");
	printf("\t\t\t\t      0.�˳�����\n\n");
}
void faceList()
{
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	setface2();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *x.�л�����ģʽ       *t.�ҵĸ赥   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *p.ѡ������           *q.������Ŀ   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *l.���ز˵�                         �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");

	switch (mode)
	{
	case 1:printf("��ǰ����ģʽ������ѭ��\n"); break;
	case 2:printf("��ǰ����ģʽ��˳�򲥷�\n"); break;
	case 3:printf("��ǰ����ģʽ���������\n"); break;
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
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *x.�½��赥           *t.ɾ���赥   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *p.չʾ�赥           *q.ѡ������   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *l.��Ӹ���           *d.ɾ������   �U\n");
	printf("\t\t\t\t\t�U                                     �U\n");
	printf("\t\t\t\t\t�U *a.���и赥           *e.���ز˵�   �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
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
	printf("\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	setCursorPosition(45, 10);
	printf("\t\t\t\t�U                                      �U\n");
	setCursorPosition(45, 11);
	printf("\t\t\t\t�U *tab.ѡ������        *space.����/��ͣ�U\n");
	setCursorPosition(45, 12);
	printf("\t\t\t\t�U                                      �U\n");
	setCursorPosition(45, 13);
	printf("\t\t\t\t�U *��.��һ��           *��.��һ��      �U\n");
	setCursorPosition(45, 14);
	printf("\t\t\t\t�U                                      �U\n");
	setCursorPosition(45, 15);
	printf("\t\t\t\t�U *��.����             *��.���        �U\n");
	setCursorPosition(45, 16);
	printf("\t\t\t\t�U                                      �U\n");
	setCursorPosition(45, 17);
	printf("\t\t\t\t�U *+.����+             *-.����-        �U\n");
	setCursorPosition(45, 18);
	printf("\t\t\t\t�U                                      �U\n");
	setCursorPosition(45, 19);
	printf("\t\t\t\t�U            *enter.�˳�����           �U\n");
	setCursorPosition(45, 20);
	printf("\t\t\t\t�U                                      �U\n");
	setCursorPosition(45, 21);
	printf("\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");

	setCursorPosition(45, 22);
	printf("\t\t\t\t������\n\n");
}




void state()
{
	system("CLS");
	//setbkcolor();
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\tʹ��˵��\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t 1.�뽫Ҫ���ŵ�.mp3�����ļ�����Ĭ��·��\" D:\\music\\ \"��\n\t\t  (��Ҫ����·����ֱ���޸�function.c�ļ���ͷPATH�ĺ궨�弴��)\n\n\n");
	printf("\t\t 2.����.mp3�����ļ�֡�ʹ����޷����ţ������Դ�ļ�\n\n\n");
	printf("\t\t 3.������Ĭ�ϲ���ģʽΪ����ѭ�����ɸ���\n\n\n");
	printf("\t\t 4.������Ĭ���ļ��м����µ�.mp3�ļ�����ʹ��\"ѡ������ļ�\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | COMMON_LVB_UNDERSCORE);
	printf("\t\t 5.�����������ʱ��Ҫɾ�����������Ȱ�pֹͣ���ţ�ɾ���ļ���ʹ��ѡ�����Ÿ����ļ����ƶ����ڲ��ŵ��ļ����ܻ����bug\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t 6.ϵͳ��ɫΪ���桢��ʾ����ɫ���ı���ɫΪ�赥�б���ʵ�\n\n\n");
	system("pause");
}

void info()
{
	system("CLS");
	//setbkcolor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t��Ȩ˵��\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t����Ŀ���Ĵ���ѧ���ѧԺ2020��2021��ʵѵ�ڶ�ʮ����ĿPodcast���ֲ�����");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	setSyscolor();
	printf("\t\t\t\t\t\t\t\t\t �Ĵ���ѧ���ѧԺ����Ц������诣�����\n");
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
	printf("\t\t\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t\t\t\t\t�U                                      �U\n");
	printf("\t\t\t\t\t�U  *1.ѭ������         *2.˳�򲥷�     �U\n");
	printf("\t\t\t\t\t�U                                      �U\n");
	printf("\t\t\t\t\t�U             *3.�������              �U\n");
	printf("\t\t\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}