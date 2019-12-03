#pragma once
#include<stdio.h>
#define DATA_SET 5
long get_file_size(FILE*fp);
void get_input(char *filepath, unsigned char *input[DATA_SET][2]);
void get_output(char*filepath, int result[], long time[], int size[DATA_SET][2]);

void create_data(char *filepath, int n, int m);