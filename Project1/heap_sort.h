#pragma once
#include"quick_sort.h"
void heapify(int list[], int i, int heapsize,int flag=0);//i 并不是数组下标，而是heap下标,flag==0表示建大堆
void build_heap(int list[], int n,int flag=0);
void heap_sort(int list[], int n);
