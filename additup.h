#ifndef ADDITUP_H
#define ADDITUP_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

typedef struct BigInt {
	int digit;
	struct BigInt *next;
	struct BigInt *prev;
} BigInt;
int readline(BigInt**,BigInt**);
void print_big(BigInt*);
void print_backwards(BigInt*);
int add(BigInt*,BigInt*,int,int,BigInt**,BigInt**);
void deep_copy(BigInt*,BigInt**);
void clean_head(BigInt*);
void clean_tail(BigInt*);
void* c_malloc(size_t);

#endif