
#include <stdio.h>
#include <stdbool.h>

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

// only works for 3x3 matrices, still less efficient than Laplace expansion
float matrix_det_RuleOfSarrus(float mat[3][3])
{
	// modulo simulates the matrix being expanded to repeat the i and j columns
	float downwardSum = 0.0f;
	for (int i = 0; i < 3; i++) downwardSum += mat[0][i] * mat[1][(i + 1) % 3] * mat[2][(i + 2) % 3];
		
	float upwardSum = 0.0f;
	for (int i = 0; i < 3; i++) upwardSum += mat[2][i] * mat[1][(i + 1) % 3] * mat[0][(i + 2) % 3];

	return downwardSum - upwardSum;
}

float matrix_det_LaplaceExpansion_hardcoded_3x3(float mat[3][3])
{
	float a = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]);
	float b = mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]);
	float c = mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
	return a - b + c;
}

float matrix_det_GeneralizedLaplaceExpansion_hardcoded_4x4(float mat[4][4])
{
	float leftDet[6];
	float rightDet[6];

	// Left
	leftDet[0] = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];	// rows 0 & 1
	leftDet[1] = mat[0][0] * mat[2][1] - mat[0][1] * mat[2][0]; // rows 0 & 2, etc.
	leftDet[2] = mat[0][0] * mat[3][1] - mat[0][1] * mat[3][0]; 
	leftDet[3] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
	leftDet[4] = mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0];
	leftDet[5] = mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0];

	// Right
	rightDet[0] = mat[0][2] * mat[1][3] - mat[0][3] * mat[1][2];	
	rightDet[1] = mat[0][2] * mat[2][3] - mat[0][3] * mat[2][2]; 
	rightDet[2] = mat[0][2] * mat[3][3] - mat[0][3] * mat[3][2]; 
	rightDet[3] = mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2];
	rightDet[4] = mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2];
	rightDet[5] = mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2];

	return (leftDet[0] * rightDet[5]) - (leftDet[1] * rightDet[4]) + (leftDet[2] * rightDet[3]) + (leftDet[3] * rightDet[2]) - (leftDet[4] * rightDet[1]) + (leftDet[5] * rightDet[0]);
}

float matrix_det_GeneralizedLaplaceExpansion_hardcoded_6x6(float mat[6][6])
{
	// might be more pain than it's worth
}

// Recursive function called in wrapper function below for NxN matrices bigger than 4x4.
float matrix_det_LaplaceExpansion(int rows, float mat[rows][rows])
{
	if (rows == 4) return matrix_det_GeneralizedLaplaceExpansion_hardcoded_4x4(mat);
	
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

		det += sign * mat[0][col] * matrix_det_LaplaceExpansion(rows - 1, temp);
	}
	return det;
}

float matrix_det_GaussianElimination(int rows, float mat[rows][rows])
{
	// works kinda like simplex
	for (int col = 0; col < rows; col++)
	{
		// find the row with the greatest absolute value in pivot position
		float pivotRow = col;
		for (int row = col; row < rows; row++)
		{
			if (fabsf(mat[row][col]) > fabsf(mat[largestPivot][col]) largestPivot = row;
		}

		// swap row with greatest pivot to current pivot position
		for (int i = 0; i < rows; i ++)
		{
			float temp = mat[col][i];
			mat[col][i] = mat[largestPivot][i];
			mat[largestPivot][i] = temp;
		}

		// find the row multiple for each row, then subtract lots of pivot row until column below pivot is 0.
		for (int row = col; row < rows; row++)
		{
			float rowMultiple = mat[row][col] / row[col][col];

			// continue from here
		}
	}	
}

// Gets determinant of matrix. Only works on square matrices, so only need rows.
bool matrix_det(int rows, float mat[rows][rows], float* output)
{
	if (rows < 2)
	{
		fprintf(stderr, "Error: Matrix has fewer than 2 rows (%d).", rows);
		return false;
	}

	// hard-coded 
	if (rows == 4)
	{
		*output = matrix_det_GeneralizedLaplaceExpansion_hardcoded_4x4(mat);
		return true;
	}
	else if (rows == 3)
	{
		*output = matrix_det_LaplaceExpansion_hardcoded_3x3(mat);;
		return true;
	}
	else if (rows == 2)
	{   
		*output = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
		return true;
	}

	*output = matrix_det_GaussianElimination(rows, mat);
	return true;
}

bool matrix_inverse(int rows, float mat[rows][rows], float output [rows][rows])
{
	float det;
	matrix_det(rows, mat, &det);

	// temp
	return false;
}

int main()
{
	float matrix3[3][3] = { {3.0f, 2.0f, 5.0f}, {7.0f, 2.0f, 6.0f}, {6.0f, 2.0f, 5.0f} }; // 6
	float matrix4[4][4] = { {3.0f, 5.0f, 2.0f, 1.0f}, {5.0f, 2.0f, 7.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {6.0f, 4.0f, 2.0f, 0.0f} }; // -78
	float output;
	matrix_det(3, matrix3, &output);
	printf("Det: %.1f\n", output);
}
