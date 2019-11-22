#include"fileio.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void get_data(int datanum,const char *func_name,int *&data, int &n)
{
	char filepath[100] = "";
	sprintf(filepath, "../input/data%d/", datanum);
	strcat(filepath, func_name);
	strcat(filepath, ".txt");
	FILE*fp = fopen(filepath, "r");
	fscanf(fp, "%d\n", &n);
	
	data = (int *)malloc(sizeof(int)*n);
	if (strcmp(func_name, "extract") != 0)
	{
		for (int i = 0; i < n; i++)
			fscanf(fp, "%d\n", &data[i]);
	}
	fclose(fp);
	return;
}
FILE*fp_outputmin,*fp_outputtime;
void output_result(int min, Output_flag flag, Heaptype heaptype, int datanum)
{

	if (flag == start_output)
	{
		if (datanum == 1)
		{
			char filepath[100] = "../output/";
			strcat(filepath, (heaptype == binary) ? "binary_heap/result.txt" : "fibo_heap/result.txt");
			fp_outputmin = fopen(filepath, "w");
			fprintf(fp_outputmin, "data%d result:\n%d\n", datanum, min);
			
		}
		else
		{
			fprintf(fp_outputmin, "data%d result:\n%d\n", datanum, min);
		}

	}
	else if (flag == end_output)
	{
		if (datanum == DATASET)
		{
			fprintf(fp_outputmin, "%d\n\n", min);
			fclose(fp_outputmin);

		}
		else
		{
			fprintf(fp_outputmin, "%d\n\n", min);
		}
		
	}
	else
	{
		fprintf(fp_outputmin, "%d\n", min);
	}
	
	
}
void output_time(double runtime,Output_flag flag, Heaptype heaptype, int datanum, const char *func_name)
{
	if (flag == start_output)
	{
		if (datanum == 1)
		{
			char filepath[100] = "../output/";
			strcat(filepath, (heaptype == binary) ? "binary_heap/time.txt" : "fibo_heap/time.txt");
			fp_outputtime = fopen(filepath, "w");
			fprintf(fp_outputtime, "data%d time:\n%0.8f\n", datanum,  runtime);

		}
		else
		{
			fprintf(fp_outputtime, "data%d time:\n%0.8f\n", datanum, runtime);
		}

	}
	else if (flag == end_output)
	{
		if (datanum == DATASET)
		{
			fprintf(fp_outputtime, "%0.8f\n\n", runtime);
			fclose(fp_outputtime);

		}
		else
		{
			fprintf(fp_outputtime, "%0.8f\n\n", runtime);
		}

	}
	else
	{
		fprintf(fp_outputtime, "%0.8f\n", runtime);
	}
}