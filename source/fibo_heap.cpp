#include"fibo_heap.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void add_fibo_node(Fibo_node *node, Fibo_node *root)
{
	node->left = root->left;
	root->left->right = node;
	node->right = root;
	root->left = node;
}
int fibo_heap_insert(Fibo_heap &fibo_heap, int *, int, int x, int)
{
	Fibo_node*node = (Fibo_node*)malloc(sizeof(Fibo_node));
	node->child = NULL;
	node->parent = NULL;
	node->degreee = 0;
	node->key = x;
	node->marked = false;
	fibo_heap.keynum++;
	fibo_heap.rootnum++;
	if (fibo_heap.min == NULL)
	{
		node->left = node->right = node;
		fibo_heap.min = node;
	}
		
	else
	{
		add_fibo_node(node, fibo_heap.min);
		if (x < fibo_heap.min->key)
			fibo_heap.min = node;
	}
	return -1;
	
}
int fibo_heap_build(Fibo_heap &fibo_heap, int*data, int n, int, int)//�����˳�ʼ��
{
	fibo_heap.rootnum = 0;
	fibo_heap.keynum = 0;
	fibo_heap.maxdegree = 0;
	fibo_heap.min = NULL;
	for (int i = 0; i < n; i++)
	{
		fibo_heap_insert(fibo_heap,NULL, -1,data[i],-1);
	}
	return 1;
}
void print_fibo(Fibo_heap fibo_heap)
{
	if (fibo_heap.keynum == 0)
		return;
	Fibo_node*p= fibo_heap.min->left,*next_p=fibo_heap.min;
	Fibo_node*end = p;
	do
	{
		p = next_p;
		next_p = p->right;
		printf("%d\n", p->key);
	} while (p != end);


	printf("\n\n");
}
int fibo_heap_extract_min(Fibo_heap &fibo_heap, int *, int, int, int)
{
	Fibo_node *z = fibo_heap.min;
	//print_fibo(fibo_heap);
	if (!z)
	{
		printf("heap is empty\n");
		return -1;
	}
	else
	{
		int i = 0;
		
		for (Fibo_node *x = z->child; i < z->degreee; i++)
		{
			Fibo_node*tmp = x->right;
			add_fibo_node(x, fibo_heap.min);
			x->parent = NULL;
			x = tmp;
			
		}
		//print_fibo(fibo_heap);
		if (z->right == z)
		{
			fibo_heap.min = NULL;
			fibo_heap.keynum--;
		}
		else
		{
			z->right->left = z->left;
			z->left->right = z->right;
			
			fibo_heap.min = z->right;
			CONSOLIDATE(fibo_heap);
			fibo_heap.keynum--;
		}
		
		return z->key;//��û�ͷ�
	}
	
}
void CONSOLIDATE(Fibo_heap &fibo_heap)
{
	int dn = (int)(log(fibo_heap.keynum)/log(2))+1;//���dn���׿������װ����ַ������������ô�죿
	//print_fibo(fibo_heap);
	Fibo_node **A = (Fibo_node**)malloc(sizeof(Fibo_node*)*(dn + 1));
	for (int i = 0; i < (dn + 1); i++)
		A[i] = NULL;

	Fibo_node*end = fibo_heap.min->left;
	Fibo_node* w = fibo_heap.min->left,*next_w=fibo_heap.min;
	do
	{
		w = next_w;
		next_w = w->right;
		Fibo_node *x;
		x = w;
		int d = x->degreee;
		while (A[d])
		{
			Fibo_node *y = A[d];
			if (x->key > y->key)
			{
				Fibo_node*tmp = x;
				x = y;
				y = tmp;
			}
			fib_heap_link(fibo_heap, y, x);
			//print_fibo(fibo_heap);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
	} while (w != end);
	int root_num = 0;
	int min = -1;
	for (int i = 0; i < (dn + 1); i++)//�ҵ���С�ĸ�
	{
		if (A[i])
		{
			root_num++;
			if (min == -1)
			{
				min = i;
			}
			else if (A[i]->key < A[min]->key)
			{
				min = i;
			}
		}
	}
	fibo_heap.min = A[min];
	fibo_heap.rootnum = root_num;
	free(A);
	//print_fibo(fibo_heap);
	return;
}
void fib_heap_link(Fibo_heap &fibo_heap, Fibo_node*y, Fibo_node*x)
{
	y->left->right = y->right;
	y->right->left = y->left;

	if (x->child)
	{
		y->left = x->child->left;
		x->child->left->right = y;
		y->right = x->child;
		x->child->left = y;
	}
	else
	{
		x->child = y;
		y->left = y->right = y;
	}
	y->parent = x;
	x->degreee++;
	if (x->degreee > fibo_heap.maxdegree)
		fibo_heap.maxdegree = x->degreee;
	y->marked = false;
}
int fibo_heap_decrease(Fibo_heap &fibo_heap, int *, int, int value, int k)
{
	if (k > value)
	{
		printf("Ӧ������һ����С��ֵ\n");
		return -1;
	}
	if (value == 242)
		print_fibo(fibo_heap);
	//print_fibo(fibo_heap);
	Fibo_node*x=fibo_heap_search(fibo_heap.min, fibo_heap.rootnum, value);
	if (!x)
	{
		printf("û���ҵ�Ҫ��С��ֵ\n");
		return -1;
	}
	x->key = k;
	Fibo_node*y = x->parent;
	if (y&&x->key < y->key)
	{
		CUT(fibo_heap, x, y);
		CASCADING_CUT(fibo_heap, y);
	}
	if (x->key < fibo_heap.min->key)
		fibo_heap.min = x;

	return 1;
}
void CUT(Fibo_heap &fibo_heap, Fibo_node *&x, Fibo_node*&y)
{
	
	if (y->degreee == 1)
	{
		y->child = NULL;
	}
	else
	{
		if (x == y->child)
		{
			y->child = x->right;
		}
		x->left->right = x->right;
		x->right->left = x->left;
	}
	add_fibo_node(x, fibo_heap.min);
	x->parent = NULL;
	x->marked = false;
	y->degreee--;
	fibo_heap.rootnum++;
}
void CASCADING_CUT(Fibo_heap &fibo_heap, Fibo_node *&y)
{
	Fibo_node *z = y->parent;
	if (z)
	{
		if (y->marked == false)
		{
			y->marked = true;
		}
		else
		{
			CUT(fibo_heap, y,z);
			CASCADING_CUT(fibo_heap, z);
		}
	}

}
Fibo_node *fibo_heap_search(Fibo_node *root, int cousins, int x)
{
	Fibo_node*result;
	if (!root)
	{
		return NULL;
	}
	else if (root->key == x)
	{
		return root;
	}
	if (cousins > 0)
	{
		result = fibo_heap_search(root->right, cousins - 1, x);
		if (result)
			return result;
	}
	if (root->child)
	{
		result = fibo_heap_search(root->child, root->degreee - 1, x);
		if (result)
			return result;
	}
	else
		return NULL;
}
int fibo_heap_delete(Fibo_heap &fibo_heap, int *, int, int value, int)
{

	fibo_heap_decrease(fibo_heap,NULL,-1, value, -MYINFINITY);
	long a=fibo_heap_extract_min(fibo_heap,NULL,-1,-1,-1);
	return -1;
}