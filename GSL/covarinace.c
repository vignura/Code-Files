#include <stdio.h>
#include "matop.h"

#define MAT_ORDER		3

int main()
{
	gsl_matrix *mat_X = 0;
	gsl_matrix *mat_COV = 0;
	gsl_matrix *mat_CORR = 0;

	/* allocate memory */
	mat_X = gsl_matrix_alloc(MAT_ORDER, MAT_ORDER);
	mat_COV = gsl_matrix_alloc(MAT_ORDER, MAT_ORDER);
	mat_CORR = gsl_matrix_alloc(MAT_ORDER, MAT_ORDER);
	
	/* fill X with all ones */
	// gsl_matrix_set_all(mat_X, 2);
	// gsl_matrix_set_identity(mat_X);

	for (int i = 0; i < MAT_ORDER; ++i)
	{
		for (int j = 0; j < MAT_ORDER; ++j)
		{
			gsl_matrix_set(mat_X, i, j, sqrt((i + 1) + (j + 1)));
		}
	}

	/* print the matrix */	
	printf("Input matrix:\n");
	printMat(mat_X);

	/* compute the covraince matrix */
	computeCovMat(MAT_ORDER, mat_X, mat_COV);

	/* print the matrix */	
	printf("covariance matrix:\n");
	printMat(mat_COV);

	/* compute the correlation matrix */
	computeCorrMat(MAT_ORDER, mat_X, mat_CORR);

	/* print the matrix */	
	printf("correlation matrix:\n");
	printMat(mat_CORR);
}