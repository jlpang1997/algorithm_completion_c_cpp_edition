#include"binary_heap.h"
#include<stdio.h>
#include<malloc.h>
#include"fileio.h"
#include<string.h>
int bi_heap_search(int heap[], int heap_size,int value)//����value�������±�i
{
	int i;
	for (i = 0; i < heap_size&&heap[i] != value; i++);
	if (i >= heap_size)
		return -1;
	else
		return i;
}
int Is_Minheap(int heap[], int heap_size ,int root)//���root��heap�±�
{
	if (2 * root <= heap_size )
	{
		if (!Is_Minheap(heap, heap_size, 2 * root) || heap[root - 1] > heap[2 * root - 1])
			return 0;
	}
	if (2 * root+1 <= heap_size)
	{
		if (!Is_Minheap(heap, heap_size, 2 * root+1) || heap[root - 1] > heap[2 * root+1 - 1])
			return 0;
	}
	return 1;

}
int bi_heap_build(int heap[], int &heap_size,int ,int)
{
	build_heap(heap, heap_size,1);
	return 1;
}
int bi_heap_decrease_tmp(int heap[], int &heap_size, int i, int key_k)
{
	if (i >= heap_size)
	{
		printf("%d out of heap_size\n",i );
		return -1;
	}
	if (heap[i] < key_k)
	{
		printf("new key is bigger than current key\n");
		return -1;
	}
	heap[i] = key_k;
	//���ϣ�һֱ��ά����С�ѵ�����
	for (; i > 0 && heap[(i + 1) / 2 - 1] > heap[i]; i = (i + 1) / 2 - 1)
	{
		swap(heap[(i + 1) / 2 - 1], heap[i]);
	}
	return 1;
}
int bi_heap_decrease(int heap[], int &heap_size,int key_x, int key_k)
{
	if (key_x < key_k)
	{
		printf("new key is bigger than current key\n");
		return -1;
	}
	int i;
	for (i= 0; i < heap_size&&heap[i] != key_x; i++);
	if (i >= heap_size)
	{
		printf("no such key with value %d\n", key_x);
		return -1;
	}
	heap[i] = key_k;
	for (; i > 0 && heap[(i + 1) / 2 - 1] > heap[i]; i = (i + 1) / 2 - 1)
	{
		swap(heap[(i + 1) / 2 - 1], heap[i]);
	}
	return 1;
}
int bi_heap_insert(int heap[], int &heap_size, int key,int )
{
	//ֱ����heap������һ�������Ȼ��decrease��key
	heap_size++;
	heap[heap_size - 1] = MYINFINITY;
	bi_heap_decrease_tmp(heap, heap_size, heap_size - 1, key);
	return 1;
}
int bi_heap_extract_min(int heap[], int &heap_size,int ,int)
{
	/*ͬheapsort��ÿ��ȡ��root��Ȼ�����һ��heapify*/
	if (heap_size < 1)
	{
		printf("heap underflow\n");
		return -1;
	}
	int min = heap[0];
	heap[0] = heap[heap_size - 1];
	heap_size--;
	heapify(heap, 1,heap_size,1);
	return min;
}
int bi_heap_delete(int heap[], int &heap_size, int i,int)
{
	//�Ѷ�Ӧֵdecrease�������Ȼ��extract-min
	
	//if (heap_size < 1)
	//{
	//	printf("heap underflow\n");
	//	return -1;
	//}
	//int i;
	//for (i = 0; i < heap_size&&heap[i] != key; i++);
	//if (i >= heap_size)
	//{
	//	printf("no such key with value %d\n", key);
	//	return -1;
	//}
	//if (i == heap_size - 1)
	//{
	//	heap_size--;
	//	return -1;
	//}
	//int new_value = heap[heap_size - 1];
	//heap_size--;
	////swap(heap[heap_size - 1], heap[i]);
	//heap[i] = new_value;
	//if (key>new_value)
	//{
	//	bi_heap_decrease_tmp(heap, heap_size, i,new_value);
	//}
	//else
	//{
	//	heapify(heap, i + 1, heap_size,1);
	//}
	bi_heap_decrease_tmp(heap, heap_size, i, -MYINFINITY);
	bi_heap_extract_min(heap, heap_size);
	return 1;
}


void swap(int &a, int &b)
{
	int tmp = b;
	b = a;
	a = tmp;
}
void heapify(int list[], int i, int heapsize, int flag)
{
	int largest = i;
	int smallest = i;
	if (2 * i <= heapsize)
	{
		if (list[i - 1] < list[2 * i - 1])
			largest = 2 * i;
		else
			smallest = 2 * i;
	}

	if ((2 * i + 1) <= heapsize && list[largest - 1] < list[2 * i + 1 - 1])
	{
		largest = 2 * i + 1;
	}
	if ((2 * i + 1) <= heapsize && list[smallest - 1] > list[2 * i + 1 - 1])
	{
		smallest = 2 * i + 1;
	}
	int lar_sml = (flag == 0) ? largest : smallest;
	if (lar_sml != i)
	{
		swap(list[lar_sml - 1], list[i - 1]);
		heapify(list, lar_sml, heapsize, flag);
	}
}
void build_heap(int list[], int n, int flag)
{
	int heapsize = n;
	for (int i = n / 2; i > 0; i--)
	{
		heapify(list, i, heapsize, flag);
	}
}