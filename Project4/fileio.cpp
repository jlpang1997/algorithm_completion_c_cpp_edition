#include"fileio.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<time.h>
void get_input(char *filepath, unsigned char *input[DATA_SET][2])
{
	FILE*fp = fopen(filepath, "rb");
	if (!fp)
	{
		printf("%s open failed.\n", filepath);
		exit(0);
	}
	long size = get_file_size(fp);
	unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char)*size);
	if (!buffer)
	{
		printf("malloc failed.");
		exit(0);
	}
	fread(buffer, 1, size, fp);
	fclose(fp);
	long buffer_count = 0;
	for (int i = 0; i < DATA_SET; i++)
	{
		int n = 1 << (5 + 3 * i);
		int m = 1 << (2 + i);
		input[i][0] = (unsigned char *)malloc(sizeof(unsigned char)*(n+1));
		input[i][1] = (unsigned char *)malloc(sizeof(unsigned char)*(m+1));
		if (!input[i][0] || !input[i][1])
		{
			printf("malloc failed.\n");
			exit(0);
		}

		for (int j = 0; j < n; j++)
			input[i][0][j] = buffer[buffer_count++];
		input[i][0][n] = '\0';
		buffer_count+=2;//跳过/r /n
		for (int j = 0; j < m; j++)
			input[i][1][j] = buffer[buffer_count++];
		buffer_count+=2;//跳过换行
		input[i][1][m] = '\0';

	}
	fclose(fp);
	free(buffer);
	//for (int i = 0; i < DATA_SET; i++)
	//{
	//	printf("%s\n%s\n", input[i][0], input[i][1]);
	//}


}

long get_file_size(FILE*fp)
{
	fseek(fp, 0, SEEK_SET);
	long size = 0;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	return size;
}

void get_output(char*filepath,int result[],long time[], int size[DATA_SET][2])
{
	FILE*fp = fopen(filepath, "wb");
	if(!fp)
	{
		printf("%s open failed.\n", filepath);
		exit(0);
	}
	char output[10000] = "";
	
	for(int i=0;i<DATA_SET;i++)
	{
		char tmp[1000] = "";
		sprintf(tmp, "%-20d\t%-10d\t%10d\t%10d\r\n",size[i][0],size[i][1], result[i],time[i]);
		strcat(output, tmp);
	}
	fwrite(output, 1, strlen(output), fp);
	fclose(fp);
}
void create_data(char *filepath,int n, int m)
{
	FILE*fp = fopen(filepath, "ab");
	if (!fp)
	{
		printf("%s open failed.\n");
		exit(0);
	}
	unsigned char *buffer = (unsigned char *)malloc(n+2+m+2);
	if (!buffer)
	{
		printf("malloc failed.\n");
		exit(0);
	}
	for (int i = 0; i < n; i++)
	{
		buffer[i] = (unsigned char)(rand() % 256);
	}
	buffer[n] = '\r';
	buffer[n + 1] = '\n';
	for (int i = 0; i < m; i++)
	{
		buffer[n+2+i]= (unsigned char)(rand() % 256);
	}
	buffer[n+2+m] = '\r';
	buffer[n+2+m+1] = '\n';
	fwrite(buffer, 1, n + 2 + m + 2, fp);
	fclose(fp);
	free(buffer);
}