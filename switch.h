#ifndef _SWITCH_H_
#define _SWICTH_H_

extern int mode;//����ģʽ
extern int inMyList;//�Ƿ����ҵĸ赥
extern char ch1;//Close_Play()������ʹ�ã��޸�����ʾbug
void Main_Switch();//��һ������ѡ��
void List_Switch();//�б����ѡ��
void myList_Switch();//�赥ҳ��ѡ��
struct media* Player_Switch(struct media* HEAD, struct media* P, int max);//���Ž���
void  Mode_Switch();//�л�����ģʽ

#endif
