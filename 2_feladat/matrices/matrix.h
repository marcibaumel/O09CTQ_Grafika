#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(float a[3][3], float b[3][3], float c[3][3]);

void init_identity_matrix(float matrix[3][3]);

void multiply_matrices(float matrix[3][3], int num);

void scalar_multiply(float a[3][3], float b[3][3], float m[3][3]);

#endif // MATRIX_H

