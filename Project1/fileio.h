#pragma once
#include<stdio.h>
#include<iostream>
#include<malloc.h>
#include<time.h>
#include<string.h>
#include<io.h>
#include<direct.h>
#define MAX_NUM (1<<20)
#define MAX_SIZE_N 20
#define STEP 1
#define START_STEP 3
#define N 4
extern char sort_func_name[N][100];
void get_list_to_sort();
void get_list( int *list, int n);
void output_result(int i, int size_n, int list[]);
void output_time(int i, long time[]);
void myfree();