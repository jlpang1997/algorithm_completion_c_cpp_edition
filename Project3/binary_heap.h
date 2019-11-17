#pragma once
#define MAX_KEY_COUNT 10000
#define MYINFINITY 10000000
int bi_heap_build(int heap[], int &heap_size,int key=-1,int key_k=-1);
int bi_heap_insert(int heap[], int &heap_size, int key=-1,int key_k=-1);
int bi_heap_delete(int heap[], int &heap_size, int key=-1,int key_k = -1);
int bi_heap_decrease(int heap[], int &heap_size,int key_x=-1, int key_k=-1);
int bi_heap_extract_min(int heap[], int &heap_size,int key_x=-1,int key_k=-1);
void bi_heap_decrease_tmp(int heap[], int heap_size, int i, int key_k);
int Is_Minheap(int heap[], int heap_size,int root);