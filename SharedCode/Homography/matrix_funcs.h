/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxAppUtils for documentation
 *
 */

#pragma once


//
// 3x3 matrix manipulation routines for
// projection warping from a modified Theo example on the OF forums:
// http://threeblindmiceandamonkey.com/?p=31
//

class MatrixFuncs {
	public :
	// multiply matrix: c = a * b
	static void multiplyMatrix(double a[3][3], double b[3][3], double c[3][3]);

	// determinant of a 2x2 matrix
	static double det2(double a, double b, double c, double d);

	// adjoint matrix: b = adjoint(a); returns determinant(a)
	static double adjointMatrix(double a[3][3], double b[3][3]);

	#define MATRIX_TOLERANCE 1e-13
	#define MATRIX_ZERO(x) ((x)<MATRIX_TOLERANCE && (x)>-MATRIX_TOLERANCE)

	// calculate matrix for unit square to quad mapping
	static void mapSquareToQuad(double quad[4][2],  // vertices of quadrilateral
					 double SQ[3][3]) ;

	// calculate matrix for general quad to quad mapping
	static void mapQuadToQuad( double in[4][2],    // starting quad
                    double out[4][2],   // target quad
				   double ST[3][3]) ;

	

};
