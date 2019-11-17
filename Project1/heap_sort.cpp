#include"heap_sort.h"
void heapify(int list[], int i,int heapsize,int flag)
{
	int largest=i;
	int smallest = i;
	if (2 * i <= heapsize)
	{
		if ( list[i - 1] < list[2 * i - 1])
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
void build_heap(int list[], int n,int flag)
{
	int heapsize = n;
	for (int i = n / 2; i > 0; i--)
	{
		heapify(list, i, heapsize,flag);
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
