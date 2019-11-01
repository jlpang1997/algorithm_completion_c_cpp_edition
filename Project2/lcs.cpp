#include"lcs.h"
#include<malloc.h>
void init_cb(int mn[], int **&c, int **&b)
{
	int m = mn[0];
	int n = mn[1];
	c = (int **)malloc(sizeof(int *)*(1+m));
	b = (int **)malloc(sizeof(int *)*(1+m));
	for (int i = 0; i < m+1; i++)
	{
		c[i] = (int *)malloc(sizeof(int)*(1+n));
		b[i] = (int *)malloc(sizeof(int)*(1+n));
	}
}
void lcs_length(char *X, char* Y, int **c, int **b, int mn[2])
{
	int m = mn[0];
	int n = mn[1];
	for (int i = 1; i <= m; i++)
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)
		c[0][j] = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (X[i - 1] == Y[j - 1])//跟课本下标不一致
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j-1];
				b[i][j] = 3;
			}
		}
	}
}
void get_lcs(int **b, char *X, int mn[],char *&lcs,int len)
{
	int m = mn[0];
	int n = mn[1];
	int i = m, j = n;
	lcs = (char *)malloc(sizeof(char)*(len+1));
	int end = len ;
	lcs[end] = '\0';
	while (i > 0 && j > 0)
	{
		if (b[i][j] == 1)
		{
			lcs[--end] = X[i - 1];
			i--;
			j--;
		}
		else if (b[i][j] == 2)
		{
			i--;
		}
		else
		{
			j--;
		}
	}
}