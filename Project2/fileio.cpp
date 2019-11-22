#include<iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include"fileio.h"

void test_input(int mn_pair[][PAIR_NUM][2])
{
	for (int i = 0; i < GROUP_NUM; i++)//���ÿһ���input�ļ�
	{
		char filepath[100] = { '\0' };
		strcat(filepath, "../input/input");
		char tmp[2] = { '\0' };
		tmp[0] = 'A' + i;
		strcat(filepath, tmp);
		strcat(filepath, ".txt");
		FILE *fp = fopen(filepath, "r");
		if (!fp)//�򲻿���˵��û�и��������ļ����Ǿ��Լ��������һ��
		{
			fp = fopen(filepath, "w");
			for (int j = 0; j < PAIR_NUM; j++)
			{
				int m = mn_pair[i][j][0];
				int n = mn_pair[i][j][1];
				char *X = (char *)malloc(sizeof(char)*(m + 1));
				char *Y = (char *)malloc(sizeof(char)*(n + 1));
				if (!X||!Y)
				{
					printf("OVERFLOW\n");
					return;
				}
				for (int k = 0; k < m; k++)
					X[k] = 'A' + (rand() % 26);
				X[m] = '\0';

				
				for (int t = 0; t < n; t++)
					Y[t] = 'A' + (rand() % 26);
				Y[n] = '\0';
				fprintf(fp, "%s\n%s\n", X, Y);
				free(X);
				free(Y);			}
			fclose(fp);
		}
	}
}
FILE *fp_input;
void inputfileopen(int i)
{
	char filepath[100] = { '\0' };
	strcat(filepath, "../input/input");
	char tmp[2] = { '\0' };
	tmp[0] = 'A' + i;
	strcat(filepath, tmp);
	strcat(filepath, ".txt");
	fp_input = fopen(filepath, "r");
}
void inputfileclose()
{
	fclose(fp_input);
}
void get_input(int mn[], char *&X, char *&Y)
{
	int m = mn[0];
	int n = mn[1];
	X = (char *)malloc(sizeof(char)*(m + 1));
	Y = (char *)malloc(sizeof(char)*(n + 1));
	if (!X || !Y)
	{
		printf("OVERFLOW\n");
		return;
	}
	X[m] = '\0';
	Y[n] = '\0';
	fscanf(fp_input, "%s\n%s\n", X,Y);
}
FILE* fp_result, *fp_time;
void outputfileopen()
{
	fp_result = fopen("../output/result.txt","w");
	fp_time = fopen("../output/time.txt","w");
	if (!fp_result || !fp_time)
	{
		printf("output file open failed\n");
		exit(0);
	}
}
void outputfileclose()
{
	fclose(fp_result);
	fclose(fp_time);
}
void dp_output_result(int mn[], char *lcs, int len,long time)
{
	int m = mn[0];
	int n = mn[1];
	fprintf(fp_result, "(%3d,%3d)   %3d   %s\n", m, n, len, lcs);
	//fprintf(fp_time, "(%3d,%3d)   %3d\n", m, n, time);
	//fprintf(fp_time, "%3d\n", m+n);
	fprintf(fp_time, "%3ld\n",time);

}
