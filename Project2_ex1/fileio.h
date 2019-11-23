#pragma once
#include<stdio.h>
#define N 5
void inputfileopen();

void inputfileclose();

void outputfileopen();

void outputfileclose();

void get_input(double *&p, double *&q, int &n);

void output_result(long time, int **root, double e, int n);

void fprint_preorder(int **root, int p, int r);

void create_input(int smallest, int biggest);