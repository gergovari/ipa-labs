#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef unsigned int uint;

void seed_rand()
{
	time_t seconds;

	time(&seconds);
	srand((unsigned int)seconds);
}

void flush_buffer()
{
	int c; do c = getchar(); while (c != EOF && c != '\n');
}

void read_num_with_flush(int *input)
{
	if (scanf_s("%u", input) == 0)
	{
		flush_buffer();
	}
}

void generate_random(double *value, double from, double to) {
	(*value) = from + (rand() / (RAND_MAX / (to - from)));
	
}

void generate_route(double **route, uint size)
{
	(*route) = malloc(size * sizeof(double));
	for (uint i = 0; i < size; i++) {
		generate_random((*route) + i, -.5, .5);
	}
}

void free_route(double *route, uint size) {
	for (uint i = 0; i < size; i++) {
		free(route + i);
	}
}

void print_route(double* route, uint size) {
	for (uint i = 0; i < size; i++) {
		printf("x = %u, y = %lf\n", i, *(route+i));
	}
}

void route_to_length(double *route, uint size, double *length) {
	for (uint i = 0; i < size - 1; i++) {
		double y0 = *(route + i);
		double y1 = *(route + i + 1);

		(*length) += pow(pow(y1 - y0, 2) + pow(1, 2), .5);
	}
}

int main(void)
{
	int inSize = 0;
	uint size = 0;
	double* route = NULL;
	
	seed_rand();
	
	while (inSize < 5) {
		printf("Number of points: ");
		read_num_with_flush(&inSize);
		if (inSize < 5) {
			printf("You need at least 5 points.\n");
		}
	}
	size = (uint)inSize;

	generate_route(&route, size);
	print_route(route, size);

	double length = 0;
	route_to_length(route, size, &length);
	printf("Length: %lf\n", length);

	free_route(route, size);
}