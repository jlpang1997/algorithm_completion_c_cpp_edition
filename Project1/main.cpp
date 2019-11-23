#include<iostream>
#include<stdio.h>
#include<malloc.h>
#include<Windows.h>
#include"merge_sort.h"
#include"quick_sort.h"
#include"counting_sort.h"
#include"heap_sort.h"
#include"fileio.h"

using namespace std;
extern void(*sort_func_wrapper[N])(int list[], int n) = { heap_sort,quick_sort,merge_sort,counting_sort };
char sort_func_name[N][100] = { "heap_sort","quick_sort","merge_sort","counting_sort" };
int main()
{
	
	
	get_list_to_sort();
	for (int i = 0; i < N; i++)
	{		
		long time[(MAX_SIZE_N - START_STEP) / STEP + 1];
		
		for (int size_n = START_STEP; size_n <= MAX_SIZE_N; size_n += STEP)
		{
			int n = 1 << size_n;
			int* list = (int *)malloc(sizeof(int)*n);
			get_list(list,n);
			LARGE_INTEGER begintime;
			LARGE_INTEGER finishtime;
			QueryPerformanceCounter(&begintime);
			sort_func_wrapper[i](list,n);
			QueryPerformanceCounter(&finishtime);
			time[(size_n - START_STEP) / STEP] = finishtime.QuadPart - begintime.QuadPart;
			output_result(i, size_n,list);
			free(list);
		}
		output_time(i, time);
	}
	myfree();
}



