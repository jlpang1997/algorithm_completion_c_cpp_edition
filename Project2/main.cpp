#include<iostream>
#include<Windows.h>
#include"fileio.h"
#include"lcs.h"

int main()
{
	int mn_pair[2][6][2] = {
		{
			{16,10},{16,20},{16,30},{16,40},{16,50},{16,60}
		},
		{
			{15,26},{30,26},{45,26},{60,26},{75,26},{90,26}
		}
	};
	test_input(mn_pair);//检查是否有给输入文件，如果没给自己就随机生成一个
	outputfileopen();
	for (int i = 0; i < 2; i++)
	{
		inputfileopen(i);//打开对应组的input文件
		for (int j = 0; j < 6; j++)
		{
			long time;
			LARGE_INTEGER begintime;
			LARGE_INTEGER finishtime;
			int m = mn_pair[i][j][0];
			int n = mn_pair[i][j][1];
			char *X=NULL;
			char *Y=NULL;
			get_input(mn_pair[i][j], X, Y);
			int **c=NULL,**b=NULL;
			init_cb(mn_pair[i][j], c, b);

			QueryPerformanceCounter(&begintime);
			lcs_length(X, Y, c, b, mn_pair[i][j]);
			QueryPerformanceCounter(&finishtime);//只测试找到长度的时间
			time= finishtime.QuadPart - begintime.QuadPart;

			char *lcs = NULL;
			get_lcs(b, X, mn_pair[i][j] , lcs,c[m][n]);
			dp_output_result(mn_pair[i][j], lcs,c[m][n],time);
			
			free(X);
			free(Y);
			free(c);
			free(b);
			free(lcs);
		}
		inputfileclose();
	}
	outputfileclose();
}