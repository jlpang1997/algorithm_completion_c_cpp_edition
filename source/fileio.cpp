#include"fileio.h"
#include<string.h>
int *list_to_sort = (int *)malloc(sizeof(int)*((long)1 << MAX_SIZE_N));
void get_list_to_sort(long size)
{
	srand((unsigned)time(NULL));
	FILE *fp_input = fopen("../input/input.txt", "r");
	long n = 1 << size;
	if (fp_input)
	{
		long i;
		for (i = 0; i < n && !feof(fp_input); i++)
		{
			char str[10] = { '\0' };
			if (!feof(fp_input))
				fscanf(fp_input, "%s\n", str);
			list_to_sort[i] = atoi(str);
		}
		if (i < n)
		{
			for (long i = 0; i < n; i++)
			{
				list_to_sort[i] = rand() % MAX_NUM + 1;
			}
		}
	}
	else {
		for (long i = 0; i < n; i++)
		{
			list_to_sort[i] = rand() % MAX_NUM + 1;
		}
	}

}

void get_list(int *list,long n)
{
	for (long i = 0; i < n; i++)
		list[i] = list_to_sort[i];
}
void output_result(int i, int size_n, int list[])
{
	struct stat file_stat;
	int ret;
	char filepath[100] = { '\0' };
	strcat(filepath, "../output");
	
	ret=stat(filepath,&file_stat);
	if (errno==ENOENT)//���inputĿ¼�����ڣ����½�һ��Ŀ¼
	{
		ret = mkdir(filepath,0775);
	}
	strcat(filepath, "/");
	strcat(filepath, sort_func_name[i]);

	//printf("*************************\n");
	ret=stat(filepath,&file_stat);
	if (errno==ENOENT)
	{
		ret = mkdir(filepath,0775);
	}
	//strcpy(timepath, filepath);
	strcat(filepath, "/result_");
	char tmp[10] = { '\0' };
	sprintf(tmp,"%d",size_n);
	strcat(filepath, tmp);
	strcat(filepath, ".txt");
	FILE* fp_result = fopen(filepath, "w");
	if (!fp_result)
	{
		printf("file open failed\n");
		return;
	}
	long n= 1 << size_n;
	for (long k = 0; k < n; k++)
		fprintf(fp_result, "%d\n", list[k]);
	fclose(fp_result);
}
void output_time(int i, long time[],int max_size_n)
{
	char filepath[100] = { '\0' };
	strcat(filepath, "../output");
	strcat(filepath, "/");
	strcat(filepath, sort_func_name[i]);
	strcat(filepath, "/time.txt");
	FILE *fp_time = fopen(filepath, "w");
	if (!fp_time)
	{
		printf("file open failed\n");
		return ;
	}
	for (int k = 0; k < (max_size_n - START_STEP) / STEP + 1; k++)
	{
		fprintf(fp_time, "%2d%15ld\n", k * STEP + START_STEP, time[k]);
	}
	fclose(fp_time);
}
void myfree()
{
	free(list_to_sort);
}