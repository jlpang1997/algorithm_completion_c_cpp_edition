#include"fileio.h"
#include"pattern_regulation.h"

#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#define FUNC_NUM 4

int main(int argc,char **argv)
{	
	const char *func_name[FUNC_NUM] = { "Naive","KMP","RK","BMH",};
	int(*func_wrapper[FUNC_NUM])(unsigned char *,int ,unsigned char *,int) = {
		Naive,
		KMP, 
		RK,
		BMH,  
		// finite_machine,
	};
	unsigned char *input[DATA_SET][2];
	int result[DATA_SET];
	long time[DATA_SET];
	int size[DATA_SET][2];
	char filepath[100] = "../input/input_strings.txt";
	get_input(filepath, input);
	char output_file[100] = "";
	for (int i = 0; i < FUNC_NUM; i++)
	{
		for (int j = 0; j < DATA_SET; j++)
		{
			int n = 1 << (5 + 3 * j);
			int m = 1 << (2 + j);
			size[j][0] = n; 
			size[j][1] = m;

			struct timeval start, end;
			gettimeofday(&start, NULL);
			result[j] = func_wrapper[i](input[j][0], n, input[j][1], m);
			gettimeofday(&end, NULL);
			time[j] = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
		}
		strcpy(output_file, "../output/");
		strcat(output_file, func_name[i]);
		strcat(output_file, "/result.txt");
		get_output(output_file,result,time,size);
	}
} 





