
#include "return_codes.h"

#include <malloc.h>
#include <math.h>
#include <stdio.h>

#define swap(x, y, type) \
	{                    \
		type t = x;      \
		x = y;           \
		y = t;           \
	}
const float EPS = 1e-24f;
void processing_error(int code)
{
	if (code == 1)
		printf("Incorrect count of program arguments");
	if (code == 2)
		printf("The input file could not be opened for reading");
	if (code == 3)
		printf("failed to allocate memory");
	if (code == 4)
		printf("Could not open the output file for writing");
	if (code == 5)
		printf("Incorrect first argument");
}

float get_max_element_in_remaining_matrix(const int k, float **slae, const int n, int *order_roots)
{
	int final_row_number = k, final_column_number = k;
	float element = slae[final_row_number][final_column_number];
	for (int i = k; i < n; ++i)
		for (int j = k; j < n; ++j)
			if (fabsf(element) < fabsf(slae[i][j]))
			{
				final_row_number = i;
				final_column_number = j;
				element = slae[i][j];
			}
	swap(slae[k], slae[final_row_number], float *);
	for (int i = 0; i < n; ++i)
	{
		swap(slae[i][k], slae[i][final_column_number], float);
	}
	swap(order_roots[k], order_roots[final_column_number], int);
	return element;
}

int direct_course(float **slae, int n, int *order_roots)
{
	for (int k = 0; k < n; ++k)
	{
		float x = get_max_element_in_remaining_matrix(k, slae, n, order_roots);
		if (x != 1)
		{
			for (int j = n; j >= k; --j)
				slae[k][j] /= x;
		}

		for (int i = k + 1; i < n; ++i)
			for (int j = n; j >= k; --j)
				slae[i][j] -= slae[k][j] * slae[i][k];

		for (int i = 0; i < n; ++i)
		{
			int cnt = 0;
			for (int j = 0; j < n; ++j)
				if (fabsf(slae[i][j]) < EPS)
					cnt++;

			if (cnt == n)
			{
				if (fabsf(slae[i][n]) < EPS)
					return 1;
				else
					return 2;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		processing_error(1);
		return ERROR_INVALID_DATA;
	}

	FILE *read = fopen(argv[1], "r");
	if (read == NULL)
	{
		processing_error(2);
		return ERROR_FILE_NOT_FOUND;
	}

	int n;
	fscanf(read, "%d", &n);
	float **slae = (float **)malloc(n * sizeof(float *));
	if (slae == NULL)
	{
		processing_error(3);
		fclose(read);
		return ERROR_OUTOFMEMORY;
	}

	for (int i = 0; i < n; ++i)
	{
		slae[i] = (float *)malloc((n + 1) * sizeof(float));
		if (slae[i] == NULL)
		{
			processing_error(3);
			free(slae);
			fclose(read);
			return ERROR_OUTOFMEMORY;
		}
	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= n; ++j)
			fscanf(read, "%f", &slae[i][j]);
	fclose(read);

	FILE *write = fopen(argv[2], "w");
	if (write == NULL)
	{
		processing_error(4);
		for (int i = 0; i < n; ++i)
			free(slae[i]);
		free(slae);
		return ERROR_FILE_NOT_FOUND;
	}

	int *order_roots = (int *)malloc(n * sizeof(int));
	if (order_roots == NULL)
	{
		processing_error(3);
		for (int i = 0; i < n; ++i)
			free(slae[i]);
		free(slae);
		fclose(write);
		return ERROR_OUTOFMEMORY;
	}
	for (int i = 0; i < n; ++i)
		order_roots[i] = i;

	int check = direct_course(slae, n, order_roots);
	if (check == 1 || check == 2)
	{
		if (check == 1)
			fprintf(write, "many solutions");
		if (check == 2)
			fprintf(write, "no solution");
		for (int i = 0; i < n; ++i)
			free(slae[i]);
		free(slae);
		free(order_roots);
		fclose(write);
		return ERROR_SUCCESS;
	}

	float *roots = (float *)malloc(n * sizeof(float));
	if (roots == NULL)
	{
		processing_error(3);
		for (int i = 0; i < n; ++i)
			free(slae[i]);
		free(slae);
		fclose(write);
		return ERROR_OUTOFMEMORY;
	}

	for (int i = 0; i < n; ++i)
		roots[i] = slae[i][n];

	for (int i = n - 2; i >= 0; --i)
		for (int j = i + 1; j < n; ++j)
			roots[i] -= roots[j] * slae[i][j];

	float *final_result = (float *)malloc(n * sizeof(float));
	if (final_result == NULL)
	{
		processing_error(3);
		free(roots);
		free(order_roots);
		free(final_result);
		fclose(write);
		return ERROR_OUTOFMEMORY;
	}

	for (int i = 0; i < n; ++i)
		final_result[order_roots[i]] = roots[i];

	for (int i = 0; i < n; ++i)
		fprintf(write, "%g\n", final_result[i]);

	free(roots);
	free(order_roots);
	free(final_result);
	fclose(write);
	return ERROR_SUCCESS;
}