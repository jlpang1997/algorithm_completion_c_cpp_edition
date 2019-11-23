#pragma once
#define PAIR_NUM 6
#define GROUP_NUM 2
void get_input(int mn[], char *&X, char *&Y);
void inputfileopen(int );
void inputfileclose();
void test_input(int mn_pair[][PAIR_NUM][2]);
void outputfileopen();
void outputfileclose();
void dp_output_result(int mn[], char *lcs,int len,long time);
