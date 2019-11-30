#include"pattern_regulation.h"
#include<stdio.h>
#include<stdlib.h>
//LC65RpZZ
int Naive(unsigned char *T, int n, unsigned char *P, int m)
{
	for (int i = 0; i < n; i++)
	{
		int j = 0, k = i;
		while (j < m&&k < n&&P[j] == T[k])
		{
			j++;
			k++;
		}
		if (j == m)
			return i;
	}
	return -1;
}

void get_next(unsigned char *P,int m,int **next)//next[j]=k 表示 当前已将匹配了j-1个，正在测试第j个，并且不匹配，j 要返回到k
{
	*next = (int *)malloc(sizeof(int)*(m+1));
	if (!*next)
	{
		printf("malloc failed.\n");
		exit(0);
	}
	(*next)[1] = 0;
	(*next)[0] = 0;
	//for (int j = 2; j < m+1; j++)
	//{
	//	int len = j - 1;
	//	for (; len > 0 && Naive(&P[j - len], len, &P[0], len) == -1; len--);
	//	(*next)[j]= len;
	//}
	for (int j = 2; j < m + 1; j++)
	{
		int result = 0;
		for (int k = j - 1;k>0 ; k = (*next)[k])//其实就是利用了一条不等式next[j]<=m 则 next[j+1]<=m+1
		{
			if (P[(*next)[k]] == P[j - 1])
			{
				result = (*next)[k] + 1;
				break;
			}
		}
		(*next)[j] = result;
	}

}
int KMP(unsigned char *T, int n, unsigned char *P, int m)
{
	int *next;
	get_next(P, m, &next);
	//for (int i = 0; i < m+1; i++)
	//	printf("next[%d]=%d\n", i, next[i]);
	int i = 0, j = 0;
	for (; j < m&&i<n;i++)
	{
		if (P[j] == T[i])
			j++;
		else
			j = next[j];
	}
	if (j == m)
	{
		free(next);
		return i-m;
	}

	free(next);
	return -1;
}
int RK(unsigned char *T, int n, unsigned char *P, int m)
{
	int d = 16;
	int q = 13;

	//用迭代来计算 pow(d,m-1)mod q
	int h = 1;
	for (int i = 0; i < m - 1; i++)
		h = (h*d) % q;

	int p = 0;
	int t = 0;
	for (int i = 0; i < m; i++)
	{
		p = (d*p + P[i]) % q;
		t = (d*t + T[i]) % q;
	}



	for (int s = 0; s <= n - m; s++)
	{
		if (p == t)
		{
			int j = 0;
			for (; j < m; j++)
				if (P[j] != T[s + j])
					break;
			if (j == m)
				return s;
		}
		if(s<n-m)
		{
			t = (  d*(t - T[s] * h) + T[s + m ]  ) % q; //这条公式要看清楚点
			if (t < 0)
				t += q;
		}
	}

	return -1;
}
int BMH(unsigned char *T, int n, unsigned char *P, int m)
{
	int HpBc[256];
	get_HpBc(P, m, HpBc);

	for (int i = 0; i <= n - m;)
	{
		int j = m - 1;
		for (; j >= 0; j--)
			if (P[j] != T[i + j])
			{
				i += HpBc[T[i + m - 1]];
				break;
			}
		if (j == -1)
			return i;
	}
	return -1;
}
void get_HpBc(unsigned char *P, int m,int HpBc[256])//最多127ascii个字符
{
	for (int i = 0; i < 256; i++)
		HpBc[i] = m;
	for (int i = m - 2; i >= 0; i--)
	{
		if (HpBc[P[i]] == m)
		{
			HpBc[P[i]] = m - 1 - i;
		}
	}
}

int finite_machine(unsigned char *T, int n, unsigned char *P, int m)
{
	int cur_state, next_state = 0;
	int i = 0;
	while (i < n)
	{
		cur_state = next_state;
		if (cur_state < m)
		{
			if (T[i] == P[cur_state])
				next_state = cur_state+1;
			else if (T[i] = P[0])
				next_state = 1;
			else
				next_state = 0;
		}
		else if (cur_state == m)
			return i - m;
		i++;
	}
	return -1;
}