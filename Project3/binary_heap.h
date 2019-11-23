#pragma once
#define MAX_KEY_COUNT 10000
#define MYINFINITY 10000000
int bi_heap_build(int heap[], int &heap_size,int key=-1,int key_k=-1);
int bi_heap_insert(int heap[], int &heap_size, int key=-1,int key_k=-1);
int bi_heap_delete(int heap[], int &heap_size, int i=-1,int key_k = -1);//�����±�i
int bi_heap_decrease(int heap[], int &heap_size,int key_x=-1, int key_k=-1);//��������key
int bi_heap_extract_min(int heap[], int &heap_size,int key_x=-1,int key_k=-1);
int bi_heap_decrease_tmp(int heap[], int &heap_size, int i=-1, int key_k=-1);//�����±�i
int Is_Minheap(int heap[], int heap_size,int root);
int bi_heap_search(int heap[],int heap_size, int value);//����value�������±�i

void swap(int &a, int &b);
void build_heap(int list[], int n, int flag);
void heapify(int list[], int i, int heapsize, int flag);