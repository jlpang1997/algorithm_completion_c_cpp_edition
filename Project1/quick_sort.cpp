#include"quick_sort.h"
void swap(int &a, int &b)
{
	int tmp = b;
	b = a;
	a = tmp;
}
int partition(int list[], int p, int r)
{
	int i = p - 1;
	int key = list[r];
	for (int j = p; j < r; j++)
	{
		if (list[j] <= key)
		{
			i++;
			swap(list[i], list[j]);
		}
	}
	swap(list[i + 1], list[r]);
	return i + 1;
}
void quick_sort_tmp(int list[], int p, int r)
{
	if (p < r)
	{
		int q = partition(list, p, r);
		quick_sort_tmp(list, p, q - 1);
		quick_sort_tmp(list, q + 1, r);
	}
}
void quick_sort(int list[], int n)
{
	quick_sort_tmp(list, 0, n - 1);
}