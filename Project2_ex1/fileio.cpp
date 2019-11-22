#include"fileio.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
FILE* fp_input;
void inputfileopen()
{
	//fp_input = fopen("../input/myinput.txt", "r");
	fp_input = fopen("../input/input.txt", "r");
	if (!fp_input)
	{
		printf("file open failed\n");
		exit(0);
	}
	//fp_input = fopen("../input/myinput.txt", "w");
}
void inputfileclose()
{
	fclose(fp_input);
}
FILE* fp_result, *fp_time;
void outputfileopen()
{
	fp_result = fopen("../output/result.txt", "w");
	fp_time = fopen("../output/time.txt", "w");
	if (!fp_result||!fp_time)
	{
		printf("file open failed\n");
		exit(0);
	}
}
void outputfileclose()
{
	fclose(fp_result);
	fclose(fp_time);
}
void get_input(double *&p, double *&q, int &n)
{
	fscanf(fp_input, "%d\n", &n);
	p = (double *)malloc(sizeof(double)*(n + 1));
	q = (double *)malloc(sizeof(double)*(n + 1));
	if (!p || !q)
	{
		printf("OVERFLOW\n");
		exit(0);
	}
	p[0] = 0;
	for (int i = 1; i <= n; i++)
		fscanf(fp_input, "%lf", &p[i]);
		
	char tmp;
	fscanf(fp_input, "%c", &tmp);
	for(int i=0;i<=n;i++)
		fscanf(fp_input, "%lf", &q[i]);
	fscanf(fp_input, "%c", &tmp);

}
void output_result(long time, int **root,double e,int n)
{
	fprintf(fp_time, "%3d   %ld\n", n, time);
	//fprintf(fp_time, "%3d\n", time);
	fprintf(fp_result, "%3d        %.2lf ",n,e);
	fprint_preorder(root, 1, n);
	fprintf(fp_result, "\n");
}
void fprint_preorder(int **root, int p, int r)
{
	if (p <= r)
	{
		int q = root[p][r];
		fprintf(fp_result, "k%d ",q);//�������������
		fprint_preorder(root, p, q - 1);
		fprint_preorder(root, q + 1, r);
	}
	else
	{
		fprintf(fp_result, "d%d ", p - 1);//����Ҷ�ڵ�
	}
}
void create_input(int smallest, int biggest)
{
	fp_input = fopen("../input/myinput.txt", "w");
	int tmp = smallest;
	for (int i = 0; i < N; i++)
	{
		smallest = tmp+i;
		int sum = 0;
		int list[1 << 16];
		int n = 0;
		while (sum < biggest&&n < (1 << 16))
		{
			int a = rand() % smallest + 1;//tmp 1 - 100
			sum += a;
			list[n++] = a;
		}
		if (sum > biggest)
		{
			list[n - 1] -= (sum - biggest);
			sum -= (sum - biggest);
		}
		else if(n >= (1 << 16) ){
			printf("OVERFLOW\n");
			exit(0);
		}
		if (n % 2 == 0)//���ǡ����ż���Ļ��������һ�����뵹���ڶ���
		{
			list[n - 2] += list[n - 1];
			n--;
		}
		int m = (n - 1) / 2;

		fprintf(fp_input, "%d\n", m);
		for (int i = 1; i <= m; i++)
		{
			fprintf(fp_input, "%lf ", (double)(list[i * 2 - 1]) / biggest);
		}
		fprintf(fp_input, "\n");
		for (int i = 0; i <= m; i++)
		{
			fprintf(fp_input, "%lf ", (double)(list[i * 2]) / biggest);
		}
		fprintf(fp_input, "\n");
	}
	fclose(fp_input);
}