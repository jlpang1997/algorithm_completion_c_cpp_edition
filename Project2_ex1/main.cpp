#include<iostream>
#include<sys/time.h>
#include"fileio.h"
#include"optimal_bst.h"

int main()
{
	//create_input(10, 10000);
	inputfileopen();//�򿪶�Ӧ���input�ļ�
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
		struct timeval start, end;
    gettimeofday( &start, NULL );
	optimal_bst(p, q, n, e, root);
    gettimeofday( &end, NULL );
    time = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;

		

		output_result(time, root, e[1][n],n);
		free(p);
		free(q);
		free(e);
		free(root);
	}
	inputfileclose();
	outputfileclose();
}