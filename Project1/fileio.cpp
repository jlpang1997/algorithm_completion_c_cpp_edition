#include"fileio.h"
int *list_to_sort = (int *)malloc(sizeof(int)*(1 << MAX_SIZE_N));
void get_list_to_sort()
{
	srand((unsigned)time(NULL));
	FILE *fp_input = fopen("../input/input_strings.txt", "r");
	unsigned n = 1 << MAX_SIZE_N;
	if (fp_input)
	{
		int i;
		for (i = 0; i < n && !feof(fp_input); i++)
		{
			char str[10] = { '\0' };
			if (!feof(fp_input))
				fscanf(fp_input, "%s\n", &str);
			list_to_sort[i] = atoi(str);
		}
		if (i < n)//说明给定的input文件数据个数不够
		{
			for (int i = 0; i < n; i++)
			{
				list_to_sort[i] = rand() % MAX_NUM + 1;
			}
		}
	}
	else {
		for (int i = 0; i < n; i++)
		{
			list_to_sort[i] = rand() % MAX_NUM + 1;
		}
	}

}

void get_list(int *list,int n)
{
	for (int i = 0; i < n; i++)
		list[i] = list_to_sort[i];
}
void output_result(int i, int size_n, int list[])
{
	char filepath[100] = { '\0' };
	strcat(filepath, "../output");
	if (access(filepath, 0))//如果input目录不存在，就新建一个目录
	{
		int a = _mkdir(filepath);
	}
	strcat(filepath, "/");
	strcat(filepath, sort_func_name[i]);
	if (access(filepath, 0))//如果_sort目录不存在，就新建一个目录
	{
		_mkdir(filepath);
	}
	//strcpy(timepath, filepath);
	strcat(filepath, "/result_");
	char tmp[10] = { '\0' };
	strcat(filepath, itoa(size_n, tmp, 10));
	strcat(filepath, ".txt");
	FILE* fp_result = fopen(filepath, "w");
	if (!fp_result)
	{
		printf("file open failed\n");
		return;
	}
	int n = 1 << size_n;
	for (int k = 0; k < n; k++)
		fprintf(fp_result, "%d\n", list[k]);
	fclose(fp_result);
}
void output_time(int i, long time[])
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
	for (int k = 0; k < (MAX_SIZE_N - START_STEP) / STEP + 1; k++)
	{
		fprintf(fp_time, "%2d%15d\n", k * STEP + START_STEP, time[k]);
	}
	fclose(fp_time);
}
void myfree()
{
	free(list_to_sort);
}