#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array.h"

int push_number(Number **number, int value)
{
	Number *tmp = *number;

	if (tmp->size == 0) {
		tmp->numbers = malloc(sizeof(int));
		tmp->numbers[0] = value;
		tmp->size++;

		return 0;
	}
	if (tmp->size >= tmp->capacity)
		tmp->capacity *= 2;
	
	tmp->numbers = realloc(tmp->numbers, sizeof(int) * tmp->capacity);
	tmp->numbers[tmp->size] = value;
	tmp->size++;
	
	return 0;
}

Number *init_number()
{
	Number *new_number = malloc(sizeof(Number));

	if (new_number == NULL) {
		fprintf(stderr, "init_number: malloc failure");
		exit(EXIT_FAILURE);
	}

	new_number->size = 0;
	new_number->capacity = 1;

	return new_number;
}

void clear_number_numbers(Number **number)
{
	Number *tmp = *number;
	tmp->size = 0;
	tmp->capacity = 1;

	free(tmp->numbers);
}

void destroy_number(Number **number)
{
	free(*number);
}

void print_numbers(Number **numbers)
{
	Number *tmp = *numbers;

	for (int i = 0; i < tmp->size; i++)
		printf(" %d ", tmp->numbers[i]);
}

