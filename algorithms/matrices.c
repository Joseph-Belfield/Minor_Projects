
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Adds mat2 to mat1
void matrix_add(float** mat1, float** mat2, int rows, int cols)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			mat1[row][col] += mat2[row][col];
		}
	}
}

// Recursive function called in wrapper function below.
float recursive_matrix_det(float** mat, int rows)
{
	if (rows == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	float det = 0.0f
	float sign = -1.0f;
	for (int col = 0; col < rows; col++)
	{
		sign *= -1;
		// need to figure out how to get minor matrix
		det += sign * recursive_matrix_det(&mat[][], rows - 1);
	}

	return det;
}

// Gets determinant of matrix. Only works on square matrices, so only need rows.
bool matrix_det(float** mat, int rows, float* output)
{
	if (rows < 2)
	{
		fptrinf(stderr, "Error: Matrix has fewer than 2 rows (%d).", rows);
		return false;
	}

	*output = recursive_matrix_det(mat, rows);
	return true;
}


