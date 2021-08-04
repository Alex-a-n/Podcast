struct media* Choose_Song(struct media* HEAD, struct media* P, int num, int max);
void Pause_Play(struct media* p);
void Close_Play(struct media* p);
int Print_List(struct media* head);
struct media* CreatHead();
void SongPlaying(struct media* p);
void VolUp(struct media* p);
void VolDown(struct media* p);
struct media* Next_Play(struct media* head, struct media* p);
struct media* Last_Play(struct media* head, struct media* p);
void go(struct media* p);
void back(struct media* p);
//struct media* repeatmode(struct media* HEAD, struct media* p, int max);
//struct media* ordermode(struct media* HEAD, struct media* p, int max);
//struct media* randommode(struct media* HEAD, struct media* p, int max);
void play(struct meida* HEAD, struct media* p, int max);
int Progress(struct media* p);
void progress_Display(struct media* head, struct media* p, int max);



//int judge(struct media* p);
//struct media* monitor(struct media* HEAD, struct media* p, int max);
//struct media* playfirst(struct media* HEAD, struct media* p);
void changeColor();
void setSyscolor();
void setTextcolor();

void setCursorPosition(int x, int y);
struct media* chooseSong2(struct media* HEAD, struct media* P);
#include "LRC.h"
int msg_deal(char* msg_src, char* msg_done[], char* str);
LRC* link_insert(LRC* head, LRC* p_new);
LRC* link_search(LRC* head, int num);
char* read_file(struct media* p);



//¸èµ¥
struct media* findp_by_num(struct media* head, int num);
struct media* display_a_list(struct media* head);
void add_to_List(struct media* head);
struct media* remove_in_list(struct media* head);

void new_list();
void remove_list();
void print_all_list();

void printc(int len, char* str);

struct media* iChoose_Song(struct media* myhead, struct media* P);

struct media* FindSong(struct media* head, struct media* p, int num, int max);

#pragma once

