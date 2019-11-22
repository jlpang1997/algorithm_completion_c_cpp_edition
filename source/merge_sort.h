#pragma once
#include<stdlib.h>
#define MYINFINITY (1<<20)
void merge(int list[], long p, long q, long r);
void merge_sort_tmp(int list[], long p, long r);
void merge_sort(int list[], long n);