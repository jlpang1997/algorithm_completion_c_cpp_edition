#pragma once
#include<malloc.h>
#define MYINFINITY (1<<20)
void merge(int list[], int p, int q, int r);
void merge_sort_tmp(int list[], int p, int r);
void merge_sort(int list[], int n);