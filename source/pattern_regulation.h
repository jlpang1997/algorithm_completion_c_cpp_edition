#pragma once
int Naive( unsigned char *T, int n, unsigned char *P, int m);
int KMP(unsigned char *T, int n, unsigned char *P, int m);
int RK(unsigned char *T, int n, unsigned char *P, int m);
int BMH(unsigned char *T, int n, unsigned char *P, int m);

void get_next(unsigned char *P, int m, int **next);

void get_HpBc(unsigned char *P, int m, int HpBc[256]);

int finite_machine(unsigned char *T, int n, unsigned char *P, int m);
