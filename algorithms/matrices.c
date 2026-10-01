
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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
float recursive_matrix_det(int rows, float mat[rows][rows])
{
	if (rows == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	float det = 0.0f;
	float sign = -1.0f;
	for (int col = 0; col < rows; col++) // iterates through a rectangle (slightly wider than tall), but skips a row to compensate
	{
		sign *= -1;
		
		float temp[rows - 1][rows - 1];
		for (int i = 1; i < rows; i++)
		{
			for (int j = 0, temp_j = 0; j < rows; j++)
			{
				if (j == col) continue;

				temp[i - 1][temp_j++] = mat[i][j];  // tracks increment of temp list, skips iteration on overlap
			}
		}

		det += sign * mat[0][col] * recursive_matrix_det(rows - 1, temp);
	}
	return det;
}

// Gets determinant of matrix. Only works on square matrices, so only need rows.
bool matrix_det(int rows, float mat[rows][rows], float* output)
{
	if (rows < 2)
	{
		fprintf(stderr, "Error: Matrix has fewer than 2 rows (%d).", rows);
		return false;
	}
	
	// rows + 1 will never appear in initial for loop, therefore does not matter for skip row
	*output = recursive_matrix_det(rows, mat);
	return true;
}

int main()
{
	float matrix[4][4] = { {3.0f, 5.0f, 2.0f, 1.0f}, {5.0f, 2.0f, 7.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {6.0f, 4.0f, 2.0f, 0.0f} };
	float output;
	matrix_det(4, matrix, &output);
	printf("Det: %.1f\n", output);
}
