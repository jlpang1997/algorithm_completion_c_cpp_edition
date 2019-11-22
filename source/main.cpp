#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include"merge_sort.h"
#include"quick_sort.h"
#include"counting_sort.h"
#include"heap_sort.h"
#include"fileio.h"

using namespace std;
void(*sort_func_wrapper[N])(int list[], long n) = { heap_sort,quick_sort,merge_sort,counting_sort };
char sort_func_name[N][100] = { "heap_sort","quick_sort","merge_sort","counting_sort" };
int main(int argc ,  char *argv[])
{
	
	if(argc!=2)
	{
		printf("input error\n");
		return -1;
	}
	int max_size_n=atoi(argv[1]);
	get_list_to_sort(max_size_n);
	for (int i = 0; i < N; i++)
	{		
		long time[(MAX_SIZE_N - START_STEP) / STEP + 1];
		
		for (int size_n = START_STEP; size_n <= max_size_n; size_n += STEP)
		{
			long n = 1 << size_n;
			int* list = (int *)malloc(sizeof(int)*n);
			get_list(list,n);
			
			struct timeval start, end;
			gettimeofday( &start, NULL );

			sort_func_wrapper[i](list,n);

			gettimeofday( &end, NULL );
			time[(size_n - START_STEP) / STEP]= 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;

		
			output_result(i, size_n,list);
			free(list);
		}
		output_time(i, time,max_size_n);
	}
	myfree();
}




