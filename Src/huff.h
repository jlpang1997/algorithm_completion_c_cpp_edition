#pragma once
typedef struct Huff_node
{
    long w;
    int lchild;
    int rchild;
    int parent;
}Huff_node;

void get_weight( char *filepath,long **weight,int *count);
void huff_encode(long weight[],int count,Huff_node**Huff_tree,char ***map,int *root);
void get_min(Huff_node*Huff_tree,int i ,int &min1,int &min2);
void get_huffcode(Huff_node*,int count,char **huffcode);

void print_map(char *map[],int count);


void get_encode_file( char*,char *);
void get_decode_file(char*filepath,char *);


void get_decode_map(unsigned long**decode_map,char **map,int count);






