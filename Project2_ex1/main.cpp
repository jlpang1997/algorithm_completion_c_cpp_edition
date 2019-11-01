#include<iostream>
#include<Windows.h>
#include"fileio.h"
#include"optimal_bst.h"

int main()
{
	//create_input(10, 10000);
	inputfileopen();//打开对应组的input文件
	outputfileopen();
	
	for (int i = 0; i < N; i++)
	{
		double *p = NULL;
		double *q = NULL;
		double **e = NULL;
		int **root = NULL;
		int n;
		get_input(p, q, n);

		long time;
		LARGE_INTEGER begintime;
		LARGE_INTEGER finishtime;
		QueryPerformanceCounter(&begintime);
		optimal_bst(p, q, n, e, root);
		QueryPerformanceCounter(&finishtime);//只测试找到长度的时间
		time = finishtime.QuadPart - begintime.QuadPart;
		output_result(time, root, e[1][n],n);
		free(p);
		free(q);
		free(e);
		free(root);
	}
	inputfileclose();
	outputfileclose();
}