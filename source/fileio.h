#pragma once
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#define MAX_NUM (1<<20)
#define MAX_SIZE_N 30
#define STEP 1
#define START_STEP 3
#define N 4
extern char sort_func_name[N][100];
void get_list_to_sort(long n);
void get_list( int *list, long n);
void output_result(int i, int size_n, int list[]);
void output_time(int i, long time[],int max_size_n);
void myfree();