#pragma once
#include"quick_sort.h"
void heapify(int list[], int i, int heapsize,int flag=0);//i �����������±꣬����heap�±�,flag==0��ʾ�����
void build_heap(int list[], int n,int flag=0);
void heap_sort(int list[], int n);