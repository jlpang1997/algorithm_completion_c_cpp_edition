#include"heap_sort.h"
void heapify(int list[], long i,long heapsize)//i �����������±꣬����heap�±�
{
	long largest=i;
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
void build_heap(int list[], long n)
{
	long heapsize = n;
	for (long i = n / 2; i > 0; i--)
	{
		heapify(list, i, heapsize);
	}
}

void heap_sort(int list[], long n)
{
	long heapsize = n;
	build_heap(list, n);
	swap(list[0], list[heapsize - 1]);
	for (heapsize = n - 1; heapsize > 0; heapsize--)
	{
		heapify(list, 1, heapsize);
		swap(list[0], list[heapsize -1]);
	}
}
