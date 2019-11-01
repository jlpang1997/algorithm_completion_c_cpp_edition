#pragma once
#include<string.h>
#define MAX_LENGTH 100
void init_cb(int mn[], int **&c, int **&b);
void lcs_length(char *X,char* Y, int **c, int **b, int mn[2]);
void get_lcs(int **b, char *X, int mn[], char *&lcs,int len);