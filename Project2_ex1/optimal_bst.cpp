#include"optimal_bst.h"
#include<malloc.h>
#include<stdio.h>
void optimal_bst(double *p, double *q, int n, double **&e, int **&root)
{
	double **w= (double**)malloc(sizeof(double*)*(n + 2));
	e = (double**)malloc(sizeof(double*)*(n + 2));
	for (int i = 1; i <= n + 1; i++)
	{
		e[i] = (double*)malloc(sizeof(double)*(n + 1));
		w[i] = (double*)malloc(sizeof(double)*(n + 1));
	}
	root = (int **)malloc(sizeof(int *)*(n + 1));//用root记录下来每个子树对应的根节点
	for (int i = 1; i <= n; i++)
		root[i] = (int *)malloc(sizeof(int)*(n + 1));
	
	for (int i = 1; i <= n + 1; i++)
	{
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];
	}
	for (int l = 1; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			e[i][j] = MYINFINITY;
			w[i][j] = w[i][ j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++)
			{
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
		
	free(w);

}