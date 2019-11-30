#pragma once
#define MAX_KEY_COUNT 10000
#define MYINFINITY 10000000
typedef struct fibo_node
{
	int key;
	int degreee;
	struct fibo_node *left;
	struct fibo_node *right;
	struct fibo_node *child;
	struct fibo_node *parent;
	bool marked;
}Fibo_node;
typedef struct Fibo_heap
{
	int rootnum;
	int keynum;
	int maxdegree;
	Fibo_node *min;
	Fibo_node **cons;//��ʱ��֪���к���
}Fibo_heap;
void add_fibo_node(Fibo_node *node, Fibo_node *root);//����������ǲ�Ϊ��
void print_fibo(Fibo_heap fibo_heap);
int fibo_heap_build(Fibo_heap &fibo_heap, int*data, int n, Fibo_node*,int);
int fibo_heap_insert(Fibo_heap &fibo_heap,int *,int, Fibo_node*,int);
int fibo_heap_decrease(Fibo_heap &fibo_heap, int *,int, Fibo_node*, int k);
int fibo_heap_delete(Fibo_heap &fibo_heap, int *,int , Fibo_node*,int);
int fibo_heap_extract_min(Fibo_heap &fibo_heap,int *,int , Fibo_node*,int);

void CONSOLIDATE(Fibo_heap &fibo_heap);
void fib_heap_link(Fibo_heap &fibo_heap, Fibo_node*y, Fibo_node*x);




Fibo_node *fibo_heap_search( Fibo_node*,  int cousins, int );
void CUT(Fibo_heap &fibo_heap, Fibo_node *&x, Fibo_node*&y);
void CASCADING_CUT(Fibo_heap &fibo_heap, Fibo_node *&y);
