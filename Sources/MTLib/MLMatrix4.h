	#ifndef MLMatrix4_h
	#define MLMatrix4_h

	
	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>


	struct _MLMatrix4
	{
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;
	};
	typedef struct _MLMatrix4 MLMatrix4;


	// creates identity matrix

	MLMatrix4 MLMatrix4CreateIdentity( );

	// creates ortographic projection

	MLMatrix4 MLMatrix4CreateOrtho( 	
		float theLeft 	, 
		float the_right 	,
		float the_bottom , 
		float theTop 	,
		float theNear	, 
		float theFar 	);
		
	// creates perspective matrix
	
	MLMatrix4 MLMatrix4CreatePerspective( 	
		float fovyRadians , 
		float aspect , 
		float nearZ , 
		float farZ );

	// creates look at
		
	MLMatrix4 MLMatrix4CreateLookAt( 
		float eyeX		, float eyeY	, float eyeZ	,
		float centerX	, float centerY	, float centerZ	,
		float upX		, float upY		, float upZ		);

	MLMatrix4 MLMatrix4CreateScale(
        float the_x ,
        float the_y ,
        float theZ );

	// creates rotation

	MLMatrix4 MLMatrix4CreateRotation( 	
		float the_radians , 
		float the_x , 
		float the_y , 
		float theZ );

	// creates translation matrix

	MLMatrix4 MLMatrix4CreateTranslation( 
		float the_x , 
		float the_y , 
		float theZ );

	// multiplies matrixes

	MLMatrix4 MLMatrix4Multiply( 	
		MLMatrix4 theLeft , 
		MLMatrix4 the_right );

	// translates matrix

	MLMatrix4 MLMatrix4Translate( 
		MLMatrix4 	theMatrix,
		float 		the_x , 
		float 		the_y , 
		float 		theZ );

	// scales matrix
	
	MLMatrix4 MLMatrix4Scale( 	
		MLMatrix4 	theMatrix , 
		float 		the_x , 
		float 		the_y , 
		float		theZ );

	// rotates matrix

	MLMatrix4 MLMatrix4Rotate(  	
		MLMatrix4 	theMatrix  ,
		float 		the_radians , 
		float 		the_x , 
		float 		the_y , 
		float 		theZ );

	// inverts matrix

	MLMatrix4 MLMatrix4Invert(
		MLMatrix4 src ,
		char* success );

	// transposes matrix

	MLMatrix4 MLMatrix4Transpose(
		MLMatrix4 src );

	// multiplies with number

	void MLMatrix4MultiplyWithNumber(
		MLMatrix4* matrix ,
		float number );

    void MLMatrix4ExtractAngles(  MLMatrix4 matrix , float* x , float* y , float* z );

	// copies members to array

	void MLMatrix4ToArray(
		MLMatrix4* matrix ,
		float* result );

	// copies array to members

	void MLMatrix4FromArray(
		MLMatrix4* matrix ,
		float* array );

	// describes matrix

	void MLMatrix4Describe(
		MLMatrix4 theMatrix );


	#endif
