#include "matrix.h"

#include <math.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	double g;
	
	/*
	Itt mért kell const ?
	*/
	float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];
	float d[3][3];
	float m[3][3];
	
    init_zero_matrix(b);
	
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    print_matrix(a);
    print_matrix(b);
    
    add_matrices(a, b, c);

    print_matrix(c);
	
	init_identity_matrix(d);
	print_matrix(d);
	
	multiply_matrices(a, 3);
	print_matrix(a);
	
	scalar_multiply(a, b, m);
	
	print_matrix(m);
	
	printf ("Are you done ? (Press a button)" );
	scanf ("%f" , &g);
	
	//shift
	calc_translate_matrix(m, dx, dy);
	
	//elforgatás
	calc_rotation_matrix(m, alpha);
	
	// m = kimeneti mátrix
	calc_scale_matrix(m, sx, sy);
	
	return 0;
}