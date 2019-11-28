#pragma once
#include<stdio.h>

void my_itoa(unsigned char ch,char num_str[10],int len);
unsigned char my_atoi(char num_str[],int len);

long get_file_size(FILE*fp);

void print_progress(int n,char *title);

FILE* create_dir_file(char *relative_path);
