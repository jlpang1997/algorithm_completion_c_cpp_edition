#include"counting_sort.h"
void counting_sort(int list[], long n)
{
	int *count = (int *)malloc(sizeof(int)*(MAX_NUM+1));
	//unsigned a = MAX_NUM;
	for (long i = 0; i <= MAX_NUM; i++)
		count[i] = 0;
	for (long i = 0; i < n; i++)
		count[list[i]]++;
	for (long i = 1; i <= MAX_NUM; i++)
	{
		count[i] += count[i - 1];
	}
	int *tmp = (int *)malloc(sizeof(int)*(n));
	if (!tmp)
		printf("fjdskljf");
	for(long i=0;i<n;i++)
	{
		tmp[ count[ list[i] ] -1]= list[i];
		count[list[i]]--;
	}
	for (long i = 0; i < n; i++)
		list[i] = tmp[i];
	free(count);
	free(tmp);
}


