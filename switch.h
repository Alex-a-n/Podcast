#ifndef _SWITCH_H_
#define _SWICTH_H_

extern int mode;//播放模式
extern int inMyList;//是否在我的歌单
extern char ch1;//Close_Play()函数中使用，修复误显示bug
void Main_Switch();//第一个界面选择
void List_Switch();//列表界面选择
void myList_Switch();//歌单页面选择
struct media* Player_Switch(struct media* HEAD, struct media* P, int max);//播放界面
void  Mode_Switch();//切换播放模式

#endif
