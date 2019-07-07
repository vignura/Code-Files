#ifndef _MAT_OP_H_
#define _MAT_OP_H_

#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

//#define MATOP_PRINT

#define MAT_ERROR_BASE							-1000
#define NULL_PTR_ACCESS							(MAT_ERROR_BASE + 1)
#define INVALID_MAT_ORDER						(MAT_ERROR_BASE + 2)

int printMat(gsl_matrix *in_mat);
int printVec(gsl_vector *in_Vec);
int computeCentringMat(int in_iOrder, gsl_matrix *out_CenteringMat);
int computeCovMat(int in_iOrder, gsl_matrix *in_Mat, gsl_matrix *out_CovMat);
int computeCorrMat(int in_iOrder, gsl_matrix *in_Mat, gsl_matrix *out_CorrMat);
int computeStdDevCol(int in_iOrder, gsl_matrix *in_Mat, gsl_vector *out_StdDev);
int computeDiagMat(gsl_vector *in_Vec, gsl_matrix *out_DiagMat);
int computeInvMat(gsl_matrix *in_Mat, gsl_matrix *out_InvMat);

#endif /* _MAT_OP_H_ */