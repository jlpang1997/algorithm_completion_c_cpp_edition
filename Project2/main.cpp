#include<iostream>
#include<sys/time.h>
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
	test_input(mn_pair);//����Ƿ��и������ļ������û���Լ����������һ��
	outputfileopen();
	for (int i = 0; i < 2; i++)
	{
		inputfileopen(i);//�򿪶�Ӧ���input�ļ�
		for (int j = 0; j < 6; j++)
		{
			long time;
			struct timeval start, end;
			//LARGE_INTEGER begintime,finishtime;
			int m = mn_pair[i][j][0];
			int n = mn_pair[i][j][1];
			char *X=NULL;
			char *Y=NULL;
			get_input(mn_pair[i][j], X, Y);
			int **c=NULL,**b=NULL;
			init_cb(mn_pair[i][j], c, b);

			//QueryPerformanceCounter(&begintime);
			gettimeofday( &start, NULL );
			lcs_length(X, Y, c, b, mn_pair[i][j]);
			gettimeofday( &end, NULL );
			time=1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
			//QueryPerformanceCounter(&finishtime);//ֻ�����ҵ����ȵ�ʱ��
			//time= finishtime.QuadPart - begintime.QuadPart;

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