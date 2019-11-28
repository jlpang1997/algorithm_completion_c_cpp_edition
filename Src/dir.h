#pragma once
#include<stdio.h>

void dir_visiting(FILE*fp,FILE*fp_huff,char **map,char *relative_path);
void dir_encoding(FILE*fp_huff,char *path,char **map,char *relative_path,int *file_num);
void dir_weighting(char * path,long *weight,long *total_bytes);
