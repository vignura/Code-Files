#include "matop.h"

int computeCorrMat(int in_iOrder, gsl_matrix *in_Mat, gsl_matrix *out_CorrMat)
{
	int iRetVal = 0;
	gsl_vector *vecStdDev = 0;
	gsl_matrix *mat_C = 0;
	gsl_matrix *mat_D = 0;
	gsl_matrix *mat_XC = 0;
	gsl_matrix *mat_XCD = 0;
	gsl_matrix *mat_XCDT = 0;

	/* input validation */
	if((in_Mat == NULL) || (out_CorrMat == NULL))
	{
		return NULL_PTR_ACCESS;
	}

	if(in_iOrder < 0)
	{
		return INVALID_MAT_ORDER;
	}

	/* allocate memory */
	vecStdDev = gsl_vector_alloc(in_iOrder);
	mat_C = gsl_matrix_alloc(in_iOrder, in_iOrder);
	mat_D = gsl_matrix_alloc(in_iOrder, in_iOrder);
	mat_XC = gsl_matrix_alloc(in_iOrder, in_iOrder);
	mat_XCD = gsl_matrix_alloc(in_iOrder, in_iOrder);
	mat_XCDT = gsl_matrix_alloc(in_iOrder, in_iOrder);

	/* compute the centering matrix */
	computeCentringMat(in_iOrder, mat_C);

	/* compute standrad deviation vector */
	computeStdDevCol(in_iOrder, in_Mat, vecStdDev);

	/* compute inverse of standrad deviation diagnol matrix */
	computeDiagMat(vecStdDev, mat_D);
	computeInvMat(mat_D, mat_D);

	/* compute XC mat */
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                  1.0, mat_C, in_Mat,
                  0.0, mat_XC);

	/* compute XCD */
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                  1.0, mat_XC, mat_D,
                  0.0, mat_XCD);

	/* compute XCD transpose */
	gsl_matrix_transpose_memcpy(mat_XCDT, mat_XCD);

	/* compute correlation matrix */
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                  1.0, mat_XCDT, mat_XCD,
                  0.0, out_CorrMat);	

	/* scale the correlation mat*/
	gsl_matrix_scale(out_CorrMat, (1 / (double)in_iOrder));
	
	/* free memory */
	gsl_matrix_free(mat_C);
	gsl_matrix_free(mat_D);
	gsl_matrix_free(mat_XC);
	gsl_matrix_free(mat_XCD);
	gsl_matrix_free(mat_XCDT);
	gsl_vector_free(vecStdDev);

	return iRetVal;
}

int computeStdDevCol(int in_iOrder, gsl_matrix *in_Mat, gsl_vector *out_StdDev)
{
	int iRetVal = 0;

	gsl_vector *vecCol = 0;
	gsl_vector *vecStdDev = 0;

	/* input validation */
	if((in_Mat == NULL) || (out_StdDev == NULL))
	{
		return NULL_PTR_ACCESS;
	}

	if(in_iOrder < 0)
	{
		return INVALID_MAT_ORDER;
	}

	/* allocate memory */
	vecCol = gsl_vector_alloc(in_iOrder);
	vecStdDev = gsl_vector_alloc(in_iOrder);

	for (int icol = 0; icol < in_Mat->size2; ++icol)
	{
		gsl_matrix_get_col(vecCol, in_Mat, icol);
		gsl_vector_set(vecStdDev, icol, gsl_stats_sd(vecCol->data, vecCol->stride, vecCol->size));
	}

	#ifdef MATOP_PRINT	
		/* print the vector */
		printf("\r\nstandrad deviation: ");
		printVec(vecStdDev);
	#endif

	/* free memory */
	gsl_vector_free(vecStdDev);
	gsl_vector_free(vecCol);

	return iRetVal;
}

int computeDiagMat(gsl_vector *in_Vec, gsl_matrix *out_DiagMat)
{
	int iRetVal = 0;

	/* input validation */
	if((in_Vec == NULL) || (out_DiagMat == NULL))
	{
		return NULL_PTR_ACCESS;
	}

	/* zero the output matrix */
	gsl_matrix_set_zero(out_DiagMat);

	if((in_Vec->size != out_DiagMat->size1) || (in_Vec->size != out_DiagMat->size2))
	{
		return INVALID_MAT_ORDER;
	}

	for (int iele = 0; iele < in_Vec->size; ++iele)
	{
		gsl_matrix_set(out_DiagMat, iele, iele, gsl_vector_get(in_Vec, iele));
	}

	return iRetVal;
}

int computeCovMat(int in_iOrder, gsl_matrix *in_Mat, gsl_matrix *out_CovMat)
{
	int iRetVal = 0;
	gsl_matrix *mat_C = 0;
	gsl_matrix *mat_XC = 0;
	gsl_matrix *mat_XCT = 0;

	/* input validation */
	if((in_Mat == NULL) || (out_CovMat == NULL))
	{
		return NULL_PTR_ACCESS;
	}

	if(in_iOrder < 0)
	{
		return INVALID_MAT_ORDER;
	}

	/* allocate memory */
	mat_C = gsl_matrix_alloc(in_iOrder, in_iOrder);
	mat_XC = gsl_matrix_alloc(in_iOrder, in_iOrder);
	mat_XCT = gsl_matrix_alloc(in_iOrder, in_iOrder);
	
	/* compute the centering matrix */
	computeCentringMat(in_iOrder, mat_C);

	/* compute XC mat */
  	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                  1.0, mat_C, in_Mat,
                  0.0, mat_XC);
	
	#ifdef MATOP_PRINT	
		/* print the matrix */	
		printf("XC matrix:\n");
		printMat(mat_XC);
	#endif

	/* compute XC transpose */
	gsl_matrix_transpose_memcpy(mat_XCT, mat_XC);

	#ifdef MATOP_PRINT
		/* print the matrix */	
		printf("XCT matrix:\n");
		printMat(mat_XCT);
	#endif

	/* compute the covariance matrix */
	gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                  1.0, mat_XCT, mat_XC,
                  0.0, out_CovMat);

	gsl_matrix_scale(out_CovMat, (1 / (double)in_iOrder));

	#ifdef MATOP_PRINT
		/* print the matrix */	
		printf("covariance matrix:\n");
		printMat(out_CovMat);
	#endif

	/* free memory */
	gsl_matrix_free(mat_C);
	gsl_matrix_free(mat_XC);
	gsl_matrix_free(mat_XCT);

	return iRetVal;
}

int computeInvMat(gsl_matrix *in_Mat, gsl_matrix *out_InvMat)
{
	int iRetVal =0;
    int s = 0;

    if((in_Mat == NULL) || (out_InvMat == NULL))
    {
    	return NULL_PTR_ACCESS;
    }

    gsl_matrix *mat_Inv = gsl_matrix_alloc(in_Mat->size1, in_Mat->size2);
    gsl_permutation *p = gsl_permutation_alloc(in_Mat->size1);

    /* Compute the LU decomposition of this matrix */
    gsl_linalg_LU_decomp(in_Mat, p, &s);

    /* Compute the  inverse of the LU decomposition */    
    gsl_linalg_LU_invert(in_Mat, p, mat_Inv);

    /* copy to output */
    gsl_matrix_memcpy(out_InvMat, mat_Inv);

    /* free memory */
    gsl_matrix_free(mat_Inv);
    gsl_permutation_free(p);

    return iRetVal;
}

int computeCentringMat(int in_iOrder, gsl_matrix *out_CenteringMat)
{
	int iRetVal = 0;
	gsl_matrix *mat_Id = 0;
	gsl_matrix *mat_11 = 0;

	/* input validation */
	if(out_CenteringMat == NULL)
	{
		return NULL_PTR_ACCESS;
	}

	if(in_iOrder < 0)
	{
		return INVALID_MAT_ORDER;
	}

	/* generate identity matrix */
	mat_Id = gsl_matrix_alloc(in_iOrder, in_iOrder);
	gsl_matrix_set_identity(mat_Id);
	
	#ifdef MATOP_PRINT
		/* print the matrix */
		printf("Identity matrix:\n");
		printMat(mat_Id);
	#endif

	/* generate all one matrix */
	mat_11 = gsl_matrix_alloc(in_iOrder, in_iOrder);
	gsl_matrix_set_all(mat_11, 1);
	
	#ifdef MATOP_PRINT
		/* print the matrix */
		printf("All one matrix:\n");
		printMat(mat_11);
	#endif

	/* scale the 11 matrix */
	gsl_matrix_scale(mat_11, (1 / (double)in_iOrder));

	#ifdef MATOP_PRINT
		/* print the matrix */
		printf("scaled All one matrix:\n");
		printMat(mat_11);
	#endif

	/* subtract 11 form identity */
	gsl_matrix_sub(mat_Id, mat_11);

	/* copy the centring matrix to output */
	gsl_matrix_memcpy(out_CenteringMat, mat_Id);

	#ifdef MATOP_PRINT
		/* print the matrix */
		printf("centring matrix:\n");
		printMat(out_CenteringMat);
	#endif

	/* free memory */
	gsl_matrix_free(mat_11);
	gsl_matrix_free(mat_Id);

	return iRetVal;
}

int printMat(gsl_matrix *in_Mat)
{
	int iRetVal = 0;

	if(in_Mat == NULL)
	{
		return NULL_PTR_ACCESS;
	}

	for (int irow = 0; irow < in_Mat->size1 ; ++irow)
	{
		for (int icol = 0; icol < in_Mat->size2 ; ++icol)
		{
			printf("%f ", gsl_matrix_get(in_Mat, irow, icol));
		}
		printf("\r\n");	
	}

	return iRetVal;
}

int printVec(gsl_vector *in_Vec)
{
	int iRetVal = 0;

	if(in_Vec == NULL)
	{
		return NULL_PTR_ACCESS;
	}

	for (int iele = 0; iele < in_Vec->size; ++iele)
	{
		printf("%f ", gsl_vector_get(in_Vec, iele));
	}
	printf("\n");

	return iRetVal;
}