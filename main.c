#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define NO_SOLUTION 0
#define ERROR_CANNOT_OPEN_FILE 1
#define ERROR_DATA_INVALID 1
#define ERROR_OUT_OF_MEMORY 1

void free_matrix(float **M, int rows)
{
	if (!M)
		return;
	for (int i = 0; i < rows; i++)
		free(M[i]);
	free(M);
}
void cleanup(FILE *in, FILE *out, float **A, int AR, float **B, int BR)
{
	free_matrix(A, AR);
	free_matrix(B, BR);
	if (in)
		fclose(in);
	if (out)
		fclose(out);
}

<<<<<<< HEAD
void cleanup(FILE *in, FILE *out, float **A, int AR, float **B, int BR)
{
	if (A)
		free_matrix(A, AR);
	if (B)
		free_matrix(B, BR);
	if (in)
		fclose(in);
	if (out)
		fclose(out);
}

float opr(float **mat, int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return mat[0][0];
	if (n == 2)
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	float d = 0;
	for (int j = 0; j < n; j++)
	{
		/* allocate minor with safety (initialize to NULL) */
		float **minor = malloc((n - 1) * sizeof(float *));
		if (!minor)
			return 0;
		for (int i = 0; i < n - 1; i++)
			minor[i] = NULL;

		int ok = 1;
		for (int i = 0; i < n - 1; i++)
		{
			minor[i] = malloc((n - 1) * sizeof(float));
			if (!minor[i])
			{
				ok = 0;
				for (int t = 0; t < i; t++)
					free(minor[t]);
				free(minor);
				break;
			}
		}
		if (!ok)
			return 0;

		for (int r = 1; r < n; r++)
		{
			int cIndex = 0;
			for (int c = 0; c < n; c++)
			{
				if (c == j)
					continue;
				minor[r - 1][cIndex++] = mat[r][c];
			}
		}

		float minorOpr = opr(minor, n - 1);
		if (j % 2 == 0)
			d += mat[0][j] * minorOpr;
		else
			d -= mat[0][j] * minorOpr;

		free_matrix(minor, n - 1);
	}
	return d;
=======
float opr(float **mat, int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return mat[0][0];
	if (n == 2)
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	float d = 0;
	for (int j = 0; j < n; j++)
	{
		float **minor = malloc((n - 1) * sizeof(float *));
		if (!minor)
			return 0;
		for (int i = 0; i < n - 1; i++)
		{
			minor[i] = malloc((n - 1) * sizeof(float));
			if (!minor[i])
				return 0;
		}

		for (int r = 1; r < n; r++)
		{
			int cIndex = 0;
			for (int c = 0; c < n; c++)
			{
				if (c == j)
					continue;
				minor[r - 1][cIndex++] = mat[r][c];
			}
		}

		float minorOpr = opr(minor, n - 1);
		if (j % 2 == 0)
			d += mat[0][j] * minorOpr;
		else
			d -= mat[0][j] * minorOpr;

		free_matrix(minor, n - 1);
	}
	return d;
}

void print_matrix(FILE *out, float **M, int n, int m)
{
	fprintf(out, "%d %d\n", n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(out, "%g", M[i][j]);
			if (j < m - 1)
				fprintf(out, " ");
		}
		fprintf(out, "\n");
	}
>>>>>>> 1f168f2 (main.c)
}

int main(int argc, char *argv[])
{
	int result = SUCCESS;

	FILE *in = NULL;
	FILE *out = NULL;
	float **A = NULL, **B = NULL;
	int AR = 0, AC = 0, BR = 0, BC = 0;

<<<<<<< HEAD
	FILE *in = NULL;
	FILE *out = NULL;
	float **A = NULL, **B = NULL;
	int AR = 0, AC = 0, BR = 0, BC = 0;
	int P = 0;
=======
	if (argc != 3)
	{
		fprintf(stderr, "Incorrect data, an error has occurred.\n");
		result = ERROR_DATA_INVALID;
		goto lCleanup;
	}
>>>>>>> 1f168f2 (main.c)

	in = fopen(argv[1], "r");
	if (!in)
	{
		fprintf(stderr, "The input file cannot be opened, an error has occurred.\n");
		result = ERROR_CANNOT_OPEN_FILE;
		goto lCleanup;
	}

	out = fopen(argv[2], "w");
	if (!out)
	{
		fprintf(stderr, "The output file cannot be opened, an error has occurred.\n");
		result = ERROR_CANNOT_OPEN_FILE;
		goto lCleanup;
	}

	int empty = fgetc(in);
	if (empty == EOF)
	{
		fprintf(stderr, "The input file is empty.\n");
		result = ERROR_DATA_INVALID;
		goto lCleanup;
	}
	ungetc(empty, in);

	char operand;
	if (fscanf(in, " %c", &operand) != 1)
	{
		fprintf(stderr, "Incorrect data, wrong operator.\n");
		result = ERROR_DATA_INVALID;
		goto lCleanup;
	}
	if (operand != '+' && operand != '-' && operand != '*' && operand != '^' && operand != '|')
	{
		fprintf(stderr, "Wrong operator.\n");
		result = ERROR_DATA_INVALID;
		goto lCleanup;
	}

	if (fscanf(in, "%d %d", &AR, &AC) != 2)
	{
		result = ERROR_DATA_INVALID;
		goto lCleanup;
	}

	A = malloc(AR * sizeof(float *));
	if (!A)
	{
		result = ERROR_OUT_OF_MEMORY;
		goto lCleanup;
	}
	for (int i = 0; i < AR; i++)
	{
		A[i] = malloc(AC * sizeof(float));
		if (!A[i])
		{
			result = ERROR_OUT_OF_MEMORY;
			goto lCleanup;
		}
		for (int j = 0; j < AC; j++)
		{
			if (fscanf(in, "%f", &A[i][j]) != 1)
			{
				result = ERROR_DATA_INVALID;
				goto lCleanup;
			}
		}
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
	/* allocate A safely and initialize pointers to NULL */
>>>>>>> 9e5ee12 (resolve merge conflict in main.c)
	A = malloc(AR * sizeof(float *));
	if (!A)
	{
		result = ERROR_OUT_OF_MEMORY;
		goto lCleanup;
	}
	for (int i = 0; i < AR; i++)
		A[i] = NULL;

	for (int i = 0; i < AR; i++)
	{
		A[i] = malloc(AC * sizeof(float));
		if (!A[i])
		{
			result = ERROR_OUT_OF_MEMORY;
			for (int t = 0; t < i; t++)
				free(A[t]);
			free(A);
			A = NULL;
			goto lCleanup;
		}
		for (int j = 0; j < AC; j++)
		{
			if (fscanf(in, "%f", &A[i][j]) != 1)
			{
				result = ERROR_DATA_INVALID;
				goto lCleanup;
			}
		}
	}

	if (operand == '+' || operand == '-' || operand == '*')
	{
		if (fscanf(in, "%d %d", &BR, &BC) != 2)
		{
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}

		B = malloc(BR * sizeof(float *));
		if (!B)
		{
			result = ERROR_OUT_OF_MEMORY;
			goto lCleanup;
		}
		for (int i = 0; i < BR; i++)
			B[i] = NULL;

		for (int i = 0; i < BR; i++)
		{
			B[i] = malloc(BC * sizeof(float));
			if (!B[i])
			{
				result = ERROR_OUT_OF_MEMORY;
				for (int t = 0; t < i; t++)
					free(B[t]);
				free(B);
				B = NULL;
				goto lCleanup;
			}
			for (int j = 0; j < BC; j++)
			{
				if (fscanf(in, "%f", &B[i][j]) != 1)
				{
					result = ERROR_DATA_INVALID;
					goto lCleanup;
				}
			}
		}
	}
	else if (operand == '^')
	{
		if (fscanf(in, "%d", &P) != 1)
		{
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
	}

	if (operand == '+')
	{
		if (AR != BR || AC != BC)
		{
			fprintf(out, "no solution\n");
			result = NO_SOLUTION;
			goto lCleanup;
		}
		for (int i = 0; i < AR; i++)
			for (int j = 0; j < AC; j++)
				A[i][j] += B[i][j];
		print_matrix(out, A, AR, AC);
	}
	else if (operand == '-')
	{
		if (AR != BR || AC != BC)
		{
			fprintf(out, "no solution\n");
			result = NO_SOLUTION;
			goto lCleanup;
		}
		for (int i = 0; i < AR; i++)
			for (int j = 0; j < AC; j++)
				A[i][j] -= B[i][j];
		print_matrix(out, A, AR, AC);
	}
	else if (operand == '*')
	{
		if (AC != BR)
		{
			fprintf(out, "no solution\n");
			result = NO_SOLUTION;
			goto lCleanup;
		}
		float **C = malloc(AR * sizeof(float *));
		if (!C)
		{
			result = ERROR_OUT_OF_MEMORY;
			goto lCleanup;
		}
		for (int i = 0; i < AR; i++)
			C[i] = NULL;

		for (int i = 0; i < AR; i++)
		{
			C[i] = malloc(BC * sizeof(float));
			if (!C[i])
			{
				result = ERROR_OUT_OF_MEMORY;
				for (int t = 0; t < i; t++)
					free(C[t]);
				free(C);
				C = NULL;
				goto lCleanup;
			}
			for (int j = 0; j < BC; j++)
			{
				C[i][j] = 0;
				for (int k = 0; k < AC; k++)
					C[i][j] += A[i][k] * B[k][j];
			}
		}
		print_matrix(out, C, AR, BC);
		free_matrix(C, AR);
	}
	else if (operand == '^')
	{
		if (AR != AC)
		{
			fprintf(out, "no solution\n");
			result = NO_SOLUTION;
			goto lCleanup;
		}
		int n = AR;
		float **res = malloc(n * sizeof(float *));
		float **tmp = malloc(n * sizeof(float *));
		if (!res || !tmp)
		{
			result = ERROR_OUT_OF_MEMORY;
			free(res);
			free(tmp);
			goto lCleanup;
		}
		for (int i = 0; i < n; i++)
		{
			res[i] = NULL;
			tmp[i] = NULL;
		}

		for (int i = 0; i < n; i++)
		{
			res[i] = malloc(n * sizeof(float));
			tmp[i] = malloc(n * sizeof(float));
			if (!res[i] || !tmp[i])
			{
				result = ERROR_OUT_OF_MEMORY;
				for (int t = 0; t < i; t++)
				{
					free(res[t]);
					free(tmp[t]);
				}
				free(res);
				free(tmp);
				res = NULL;
				tmp = NULL;
				goto lCleanup;
			}
			for (int j = 0; j < n; j++)
				res[i][j] = A[i][j];
		}

		for (int p = 1; p < P; p++)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
				{
					tmp[i][j] = 0;
					for (int k = 0; k < n; k++)
						tmp[i][j] += res[i][k] * A[k][j];
				}
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i][j] = tmp[i][j];
		}
		print_matrix(out, res, n, n);
		free_matrix(res, n);
		free_matrix(tmp, n);
	}
	else if (operand == '|')
	{
		if (AR != AC)
		{
			fprintf(out, "no solution\n");
			result = NO_SOLUTION;
			goto lCleanup;
		}
		float det = opr(A, AR);
		fprintf(out, "%g\n", det);
	}
=======
	int P = 0;

	if (operand == '+' || operand == '-' || operand == '*')
	{
		if (fscanf(in, "%d %d", &BR, &BC) != 2)
		{
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}

		B = malloc(BR * sizeof(float *));
		if (!B)
		{
			result = ERROR_OUT_OF_MEMORY;
			goto lCleanup;
		}
		for (int i = 0; i < BR; i++)
		{
			B[i] = malloc(BC * sizeof(float));
			if (!B[i])
			{
				result = ERROR_OUT_OF_MEMORY;
				goto lCleanup;
			}
			for (int j = 0; j < BC; j++)
			{
				if (fscanf(in, "%f", &B[i][j]) != 1)
				{
					result = ERROR_DATA_INVALID;
					goto lCleanup;
				}
			}
		}
	}
	else if (operand == '^')
	{
		if (fscanf(in, "%d", &P) != 1)
		{
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
	}

	if (operand == '+')
	{
		if (AR != BR || AC != BC)
		{
			fprintf(out, "no solution\n");
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
		for (int i = 0; i < AR; i++)
			for (int j = 0; j < AC; j++)
				A[i][j] += B[i][j];
		print_matrix(out, A, AR, AC);
	}
	else if (operand == '-')
	{
		if (AR != BR || AC != BC)
		{
			fprintf(out, "no solution\n");
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
		for (int i = 0; i < AR; i++)
			for (int j = 0; j < AC; j++)
				A[i][j] -= B[i][j];
		print_matrix(out, A, AR, AC);
	}
	else if (operand == '*')
	{
		if (AC != BR)
		{
			fprintf(out, "no solution\n");
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
		float **C = malloc(AR * sizeof(float *));
		if (!C)
		{
			result = ERROR_OUT_OF_MEMORY;
			goto lCleanup;
		}
		for (int i = 0; i < AR; i++)
		{
			C[i] = malloc(BC * sizeof(float));
			if (!C[i])
			{
				result = ERROR_OUT_OF_MEMORY;
				goto lCleanup;
			}
			for (int j = 0; j < BC; j++)
			{
				C[i][j] = 0;
				for (int k = 0; k < AC; k++)
					C[i][j] += A[i][k] * B[k][j];
			}
		}
		print_matrix(out, C, AR, BC);
		free_matrix(C, AR);
	}
	else if (operand == '^')
	{
		if (AR != AC)
		{
			fprintf(out, "no solution\n");
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
		int n = AR;
		float **res = malloc(n * sizeof(float *));
		float **tmp = malloc(n * sizeof(float *));
		if (!res || !tmp)
		{
			result = ERROR_OUT_OF_MEMORY;
			goto lCleanup;
		}
		for (int i = 0; i < n; i++)
		{
			res[i] = malloc(n * sizeof(float));
			tmp[i] = malloc(n * sizeof(float));
			if (!res[i] || !tmp[i])
			{
				result = ERROR_OUT_OF_MEMORY;
				goto lCleanup;
			}
			for (int j = 0; j < n; j++)
				res[i][j] = A[i][j];
		}

		for (int p = 1; p < P; p++)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
				{
					tmp[i][j] = 0;
					for (int k = 0; k < n; k++)
						tmp[i][j] += res[i][k] * A[k][j];
				}
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					res[i][j] = tmp[i][j];
		}
		print_matrix(out, res, n, n);
		free_matrix(res, n);
		free_matrix(tmp, n);
	}
	else if (operand == '|')
	{
		if (AR != AC)
		{
			fprintf(out, "no solution\n");
			result = ERROR_DATA_INVALID;
			goto lCleanup;
		}
		float det = opr(A, AR);
		fprintf(out, "%g\n", det);
	}
>>>>>>> 1f168f2 (main.c)

lCleanup:
	cleanup(in, out, A, AR, B, BR);
	return result;
}
