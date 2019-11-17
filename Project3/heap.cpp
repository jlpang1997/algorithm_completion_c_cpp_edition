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
			cout << "ÅÜ¶þ²æ¶ÑÃüÁî £º./heap.exe binary" << endl;
			cout << "ÅÜì³²¨ÄÇÆõ¶ÑÃüÁî £º./heap.exe fibo" << endl;
		}
		return 0;

	}
	else
	{
		cout << "ÅÜ¶þ²æ¶ÑÃüÁî £º./heap.exe 1" << endl;
		cout << "ÅÜì³²¨ÄÇÆõ¶ÑÃüÁî £º./heap.exe 2" << endl;
		return 0;
	}

}
void heap(Heaptype heaptype)
{
	const char *func_name[5] = { "build","insert","decrease","delete","extract" };
	int(*binary_func_wrapper[FUNC_NUM])(int heap[], int &heap_size, int, int) = {
		bi_heap_build,
		bi_heap_insert,
		bi_heap_decrease,
		bi_heap_delete,
		bi_heap_extract_min
	};
	int(*fibo_func_wrapper[FUNC_NUM])(Fibo_heap &fibo_heap, int*data, int n, int, int) = {
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
					fibo_func_wrapper[k](fibo_heap, data, n, -1, -1);
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
						QueryPerformanceCounter(&begintime);
						min = binary_func_wrapper[k](heap, heap_size, data[j], data[j] - 10);
						QueryPerformanceCounter(&finishtime);
						runtime += finishtime.QuadPart - begintime.QuadPart;
					}
					else if (heaptype == fibo)
					{
						QueryPerformanceCounter(&begintime);
						min = fibo_func_wrapper[k](fibo_heap, NULL, -1,data[j], data[j] - 10);
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


	//for (int i = 1; i <= 1; i++)
	//{
	//	int n;
	//	int *data;
	//	Fibo_heap fibo_heap;
	//	for (int k = 0; k < FUNC_NUM; k++)
	//	{
	//		get_data(i, func_name[k], data, n);
	//		if (k == 0)
	//		{
	//			fibo_heap_build(fibo_heap, data, n);
	//			//print_fibo(fibo_heap);
	//		}
	//		else
	//		{
	//			long runtime = 0;
	//			for (int j = 0; j < n; j++)
	//			//while(fibo_heap.keynum>0)
	//			{

	//				LARGE_INTEGER begintime;
	//				LARGE_INTEGER finishtime;
	//				QueryPerformanceCounter(&begintime);
	//				int min = fibo_heap_insert(fibo_heap,data[j]);
	//				printf("%d\n", fibo_heap.keynum);
	//				print_fibo(fibo_heap);
	//				int min = fibo_heap_extract_min(fibo_heap);
	//				printf("min:%d\n\n", min);


	//				Fibo_node*p = fibo_heap_search(fibo_heap.min, fibo_heap.rootnum, 24);
	//				p = fibo_heap_search(fibo_heap.min, fibo_heap.rootnum, 24);

	//				print_fibo(fibo_heap);
	//				fibo_heap_decrease(fibo_heap, 24, 1);
	//				print_fibo(fibo_heap);
	//				min = fibo_heap_extract_min(fibo_heap);
	//				printf("min:%d\n\n", min);

	//				int a = 90;
	//				//print_fibo(fibo_heap);
	//			//	QueryPerformanceCounter(&finishtime);
	//			//	runtime += finishtime.QuadPart - begintime.QuadPart;

	//			//	Output_flag output_flag;

	//			//	if (j == n - 1)
	//			//		output_flag = end_output;
	//			//	else if (j == 0)
	//			//		output_flag = start_output;
	//			//	else
	//			//		output_flag = continue_output;


	//			//	if (k == FUNC_NUM - 1)
	//			//	{
	//			//		output_result(min, output_flag, heaptype, i);
	//			//	}

	//			}

	//			//Output_flag output_flag;
	//			//if (k == FUNC_NUM - 1)
	//			//	output_flag = end_output;
	//			//else if (k == 1)
	//			//	output_flag = start_output;
	//			//else
	//			//	output_flag = continue_output;
	//			//output_time((double)runtime / n, output_flag, heaptype, i, func_name[k]);

	//		}

	//		free(data);
	//	}
	//}
}