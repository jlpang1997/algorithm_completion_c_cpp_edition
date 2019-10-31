#include"merge_sort.h"
void merge(int list[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = (int *)malloc(sizeof(int)*(n1 + 1));
	for (int i = 0; i < n1; i++)
	{
		L[i] = list[p + i];
	}
	L[n1] = MYINFINITY;
	int *R = (int *)malloc(sizeof(int)*(n2 + 1));
	for (int i = 0; i < n2; i++)
	{
		R[i] = list[q + 1 + i];
	}
	R[n2] = MYINFINITY;
	int i = 0;
	int j = 0;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			list[k] = L[i];
			i++;
		}
		else
		{
			list[k] = R[j];
			j++;
		}
	}
}
void merge_sort_tmp(int list[], int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		merge_sort_tmp(list, p, q);
		merge_sort_tmp(list, q + 1, r);
		merge(list, p, q, r);
	}
}
void merge_sort(int list[], int n)
{
	merge_sort_tmp(list, 0, n - 1);
}