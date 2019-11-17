#include"heap_sort.h"
void heapify(int list[], int i,int heapsize)//i 并不是数组下标，而是heap下标
{
	int largest=i;
	if (2*i<=heapsize&&list[largest-1] < list[2 * i - 1])
	{
		largest = 2 * i;
	}
	if ((2*i+1)<=heapsize&&list[largest - 1] < list[2 * i + 1 - 1])
	{
		largest = 2 * i + 1;
	}
	if (largest != i)
	{
		swap(list[largest - 1], list[i - 1]);
		heapify(list, largest, heapsize);
	}

}
void build_heap(int list[], int n)
{
	int heapsize = n;
	for (int i = n / 2; i > 0; i--)
	{
		heapify(list, i, heapsize);
	}
}

void heap_sort(int list[], int n)
{
	int heapsize = n;
	build_heap(list, n);
	swap(list[0], list[heapsize - 1]);
	for (heapsize = n - 1; heapsize > 0; heapsize--)
	{
		heapify(list, 1, heapsize);
		swap(list[0], list[heapsize -1]);
	}
}
