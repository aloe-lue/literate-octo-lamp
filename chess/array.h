#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

typedef struct Number {
	int *numbers;
	int size;
	size_t capacity;
} Number;

/*
 * helps with using methods
 */
Number *init_number();

/*
 * push a number in number
 */
int push_number(Number **number, int value);

/*
 * clear all that it contains
 */
void clear_number_numbers(Number **number);

void destroy_number(Number **number);

void print_numbers(Number **number);

#endif /* array.h */
