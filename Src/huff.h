#pragma once

#include<stdio.h>
typedef struct Huff_node
{
    long w;
    int lchild;
    int rchild;
    int parent;
}Huff_node;


void format_filepath(char *filepath);

void get_weight_from_file( char *filepath,long **weight,int *count);
void huff_encode(long weight[],int count,Huff_node**Huff_tree,char ***map,int *root);
void getmin(Huff_node*Huff_tree,int i ,int &min1,int &min2);
void get_huffcode(Huff_node*,int count,char **huffcode);

void print_map(char *map[],int count);
long get_file_size(FILE*fp);
void print_progress(int n);

void get_encode_file( char*,char *,int);
void get_decode_file(char*filepath,char *output,int);

void get_encode_file_recursion(char*init_filepath,char *huff_dir_file3,int MAX_TIME_ENCODE_TIME);
void get_decode_file_recursion(char*huff_filepath,char *init_dir_file0);







void my_itoa(unsigned char ch,char num_str[10]);
unsigned char my_atoi(char num_str[],int len);

unsigned char search_by_decode_map(unsigned long*decode_map,int count,char code[]);
void get_decode_map(unsigned long**decode_map,char **map,int count);

void print_progress(int n,char *title);