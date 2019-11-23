#include<stdio.h>
#include<iostream>
#include<Windows.h>
#include"binary_heap.h"
#include"fibo_heap.h"
#include"fileio.h"

using namespace std;
void heap(Heaptype type);
int main(int argc, char *argv[])
{
	if (argc == 2)
	{

		if (strcmp(argv[1],"binary")==0)
		{
			heap(binary);

		}
		else if (strcmp(argv[1], "fibo") == 0)
		{
			heap(fibo);
		}
		else
		{
			cout << "跑二叉堆命令 ：./heap.exe binary" << endl;
			cout << "跑斐波那契堆命令 ：./heap.exe fibo" << endl;
		}
		return 0;

	}
	else
	{
		cout << "跑二叉堆命令 ：./heap.exe binary" << endl;
		cout << "跑斐波那契堆命令 ：./heap.exe fibo" << endl;
		return 0;
	}

}
void heap(Heaptype heaptype)
{
	const char *func_name[5] = { "build","insert","decrease","delete","extract" };
	int(*binary_func_wrapper[FUNC_NUM])(int heap[], int &heap_size, int, int) = {
		bi_heap_build,
		bi_heap_insert,
		bi_heap_decrease_tmp,
		bi_heap_delete,
		bi_heap_extract_min
	};
	int(*fibo_func_wrapper[FUNC_NUM])(Fibo_heap &fibo_heap, int*data, int n, Fibo_node*, int) = {
	fibo_heap_build,
	fibo_heap_insert,
	fibo_heap_decrease,
	fibo_heap_delete,
	fibo_heap_extract_min
	};
	for (int i = 1; i <= DATASET; i++)
	{
		
		int n;
		int *data;
		int heap[MAX_KEY_COUNT];
		int heap_size;
		Fibo_heap fibo_heap;
		for (int k = 0; k < FUNC_NUM; k++)
		{
			get_data(i, func_name[k], data, n);
			if (k == 0)
			{
				if (heaptype == binary)
				{
					heap_size = n;
					for (int m = 0; m < n; m++)heap[m] = data[m];
					binary_func_wrapper[k](heap, heap_size, -1, -1);
				}
				else if (heaptype == fibo)
				{
					fibo_func_wrapper[k](fibo_heap, data, n, NULL, -1);
				}
			}
			else
			{
				long runtime = 0;
				
				
				for (int j = 0; j < n; j++)
				{
					int min;
					LARGE_INTEGER begintime;
					LARGE_INTEGER finishtime;
					if (heaptype == binary)
					{
						int i = data[j];
						if (strcmp(func_name[k], "decrease") == 0|| strcmp(func_name[k], "delete")==0)
						{
							i=bi_heap_search(heap, heap_size, data[j]);
							if (i == -1)
							{
								printf("heap内没有要decrease或delete的%d\n", data[j]);
								break;
							}
						}//查找的时间不算在内
						QueryPerformanceCounter(&begintime);
						min = binary_func_wrapper[k](heap, heap_size, i, data[j] - 10);
						QueryPerformanceCounter(&finishtime);
						runtime += finishtime.QuadPart - begintime.QuadPart;
					}
					else if (heaptype == fibo)
					{
						Fibo_node *node=NULL;
						if (strcmp(func_name[k], "decrease") == 0 || strcmp(func_name[k], "delete") == 0)
						{
							node = fibo_heap_search(fibo_heap.min, fibo_heap.rootnum, data[j]);
							data[j] -= 10;
							if (node == NULL)
							{
								printf("heap内没有要decrease或delete的%d\n", data[j]);
								break;
							}
						}//查找的时间不算在内
						QueryPerformanceCounter(&begintime);
						min = fibo_func_wrapper[k](fibo_heap, NULL, -1,node, data[j] );
						QueryPerformanceCounter(&finishtime);
						runtime += finishtime.QuadPart - begintime.QuadPart;
					}

					
					

					if (k == FUNC_NUM - 1)
					{
						Output_flag output_flag;

						if (j == n - 1)
							output_flag = end_output;
						else if (j == 0)
							output_flag = start_output;
						else
							output_flag = continue_output;
						output_result(min, output_flag, heaptype, i);
					}
					
				}
				Output_flag output_flag;
				if (k == FUNC_NUM-1)
					output_flag = end_output;
				else if (k == 1)
					output_flag = start_output;
				else
					output_flag = continue_output;
				output_time((double)runtime / n,output_flag, heaptype, i, func_name[k]);

			}

			free(data);
		}
	}

}

//void heap(Heaptype heaptype)
//{
//	output_time(1000000, start_output, heaptype, 1, "insert");
//	int heap[100000];
//	int heap_size = 0;
//	Fibo_heap fibo_heap;
//	
//	for (int i = 0; i < 100000; i++)
//	{
//		heap[i] = rand() % 100000 + 1;
//	}
//	fibo_heap_build(fibo_heap, heap, 1000, NULL, -1);
//	while (fibo_heap.keynum > 0)
//	{
//		long runtime;
//		LARGE_INTEGER begintime;
//		LARGE_INTEGER finishtime;
//		QueryPerformanceCounter(&begintime);
//		fibo_heap_extract_min(fibo_heap, NULL, -1, NULL, -1);
//		QueryPerformanceCounter(&finishtime);
//		runtime = finishtime.QuadPart - begintime.QuadPart;
//		output_time((double)runtime, continue_output, heaptype, 5, "extract-min");
//	
//	}
//	
//	
//}
