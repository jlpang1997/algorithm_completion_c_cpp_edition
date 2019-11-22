#pragma once
#define DATASET 5
#define FUNC_NUM 5//�������ֲ���
#define HEAPTYPE_NUM 2
enum Output_flag { start_output,continue_output, end_output };
enum Heaptype {binary,fibo};

void get_data(int datanum,const char *,int *&data, int &n);
void output_result(int min,Output_flag flag, Heaptype, int datanum);
void output_time(double runtime, Output_flag flag, Heaptype, int datanum,const char *func_name);