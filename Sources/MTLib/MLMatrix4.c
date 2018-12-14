	#include "MLMatrix4.h"


	// creates identity matrix

	MLMatrix4 MLMatrix4CreateIdentity( )
	{

		MLMatrix4 matrix;
		
		matrix.m00 = 1.0f;
		matrix.m01 = 0.0f;
		matrix.m02 = 0.0f;
		matrix.m03 = 0.0f;
		matrix.m10 = 0.0f;
		matrix.m11 = 1.0f;
		matrix.m12 = 0.0f;
		matrix.m13 = 0.0f;
		matrix.m20 = 0.0f;
		matrix.m21 = 0.0f;
		matrix.m22 = 1.0f;
		matrix.m23 = 0.0f;
		matrix.m30 = 0.0f;
		matrix.m31 = 0.0f;
		matrix.m32 = 0.0f;
		matrix.m33 = 1.0f;
		
		return matrix;

	}



	// creates ortographic projection

	MLMatrix4 MLMatrix4CreateOrtho( 	
		float theLeft 	, 
		float the_right 	,
		float the_bottom , 
		float theTop 	,
		float theNear	, 
		float theFar 	)
	{
	
		float rpl, rml, tpb, tmb, fpn, fmn;
		MLMatrix4 matrix;

		rpl = the_right + theLeft;
		rml = the_right - theLeft;
		tpb = theTop + the_bottom;
		tmb = theTop - the_bottom;
		fpn = theFar + theNear;
		fmn = theFar - theNear;
						
		matrix.m00 = 2.0f / rml;
		matrix.m01 = 0.0f;
		matrix.m02 = 0.0f;
		matrix.m03 = 0.0f;
		matrix.m10 = 0.0f;
		matrix.m11 = 2.0f / tmb;
		matrix.m12 = 0.0f;
		matrix.m13 = 0.0f;
		matrix.m20 = 0.0f;
		matrix.m21 = 0.0f;
		matrix.m22 = -2.0f / fmn;
		matrix.m23 = 0.0f;
		matrix.m30 = -rpl / rml;
		matrix.m31 = -tpb / tmb;
		matrix.m32 = -fpn / fmn;
		matrix.m33 = 1.0f;
		
		return matrix;
				
	}


	// create perspective projection

	MLMatrix4 MLMatrix4CreatePerspective( 	
		float fovyRadians , 
		float aspect , 
		float nearZ , 
		float farZ )
	{
	
		float cotan;
		MLMatrix4 matrix;
			
		cotan = 1.0f / tanf(fovyRadians / 2.0f);
		
		matrix.m00 = cotan / aspect;
		matrix.m01 = 0.0f;
		matrix.m02 = 0.0f;
		matrix.m03 = 0.0f;
		
		matrix.m10 = 0.0f;
		matrix.m11 = cotan;
		matrix.m12 = 0.0f;
		matrix.m13 = 0.0f;
		
		matrix.m20 = 0.0f;
		matrix.m21 = 0.0f;
		matrix.m22 = (farZ + nearZ) / (nearZ - farZ);
		matrix.m23 = -1.0f;
		
		matrix.m30 = 0.0f;
		matrix.m31 = 0.0f;
		matrix.m32 = (2.0f * farZ * nearZ) / (nearZ - farZ);
		matrix.m33 = 0.0f;
		
		return matrix;
		
	}


	// creates lookat

	MLMatrix4 MLMatrix4CreateLookAt( 
		float eyeX		, float eyeY	, float eyeZ	,
		float centerX	, float centerY	, float centerZ	,
		float upX		, float upY		, float upZ		)
	{
	
//		GLKVector3 ev = { eyeX, eyeY, eyeZ };
//		GLKVector3 cv = { centerX, centerY, centerZ };
//		GLKVector3 uv = { upX, upY, upZ };
//		GLKVector3 n = GLKVector3Normalize(GLKVector3Add(ev, GLKVector3Negate(cv)));
//		GLKVector3 u = GLKVector3Normalize(GLKVector3CrossProduct(uv, n));
//		GLKVector3 v = GLKVector3CrossProduct(n, u);
//		
//		GLKMatrix4 m = { u.v[0], v.v[0], n.v[0], 0.0f,
//						 u.v[1], v.v[1], n.v[1], 0.0f,
//						 u.v[2], v.v[2], n.v[2], 0.0f,
//						 GLKVector3DotProduct( GLKVector3Negate(u) , ev ) ,
//						 GLKVector3DotProduct( GLKVector3Negate(v) , ev ) ,
//						 GLKVector3DotProduct( GLKVector3Negate(n) , ev ) ,
//						 1.0f };
//		
		MLMatrix4 matrix;

		return matrix;
		
	}


    MLMatrix4 MLMatrix4CreateScale(
        float the_x ,
		float the_y , 
		float the_z )

    {
    
        MLMatrix4 matrix = MLMatrix4CreateIdentity( );
    
		matrix.m00 *= the_x;
		matrix.m11 *= the_y;
		matrix.m22 *= the_z;
		
		return matrix;
    
    }


	// creates rotation

	MLMatrix4 MLMatrix4CreateRotation( 	
		float the_radians , 
		float the_x , 
		float the_y , 
		float the_z )
	{

		float x, y, z, scale, sin, cos, cosp;
		MLMatrix4 matrix;

		// normalize values
		
		x = the_x;
		y = the_y;
		z = the_z;

		scale = 1.0f / sqrtf( x * x + y * y + z * z );

		x *= scale;
		y *= scale;
		z *= scale;
		
		// precalc
		
		sin = sinf( the_radians );
		cos = cosf( the_radians );
		cosp = 1.0f - cos;
		
		// create matrix
		
		matrix.m00 = cos + cosp * x * x;
		matrix.m01 = cosp * x * y + z * sin;
		matrix.m02 = cosp * x * z - y * sin;
		matrix.m03 = 0.0f;
		matrix.m10 = cosp * x * y - z * sin;
		matrix.m11 = cos + cosp * y * y;
		matrix.m12 = cosp * y * z + x * sin;
		matrix.m13 = 0.0f;
		matrix.m20 = cosp * x * z + y * sin;
		matrix.m21 = cosp * y * z - x * sin;
		matrix.m22 = cos + cosp * z * z;
		matrix.m23 = 0.0f;
		matrix.m30 = 0.0f;
		matrix.m31 = 0.0f;
		matrix.m32 = 0.0f;
		matrix.m33 = 1.0f;
		
		return matrix;
							
	}


	// creates translation matrix
	
	MLMatrix4 MLMatrix4CreateTranslation( float the_x , float the_y , float the_z )
	{
	
		MLMatrix4 result;
		
		result = MLMatrix4CreateIdentity( );
		
		result.m30 = the_x;
		result.m31 = the_y;
		result.m32 = the_z;

		return result;
		
	}


	// multiplies matrices

	MLMatrix4 MLMatrix4Multiply( 	
		MLMatrix4 a ,
		MLMatrix4 b )
	{
		
		MLMatrix4 matrix;
		
		matrix.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
		matrix.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
		matrix.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
		matrix.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
		
		matrix.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
		matrix.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
		matrix.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
		matrix.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
		
		matrix.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
		matrix.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
		matrix.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
		matrix.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
		
		matrix.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
		matrix.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
		matrix.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
		matrix.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;
		
		return matrix;
		
	}

	
	// translates matrix
	
	MLMatrix4 MLMatrix4Translate( 
		MLMatrix4 	other,
		float 		the_x , 
		float 		the_y , 
		float 		the_z )
	{

		MLMatrix4 matrix;

		matrix.m00 = other.m00;
		matrix.m01 = other.m01;
		matrix.m02 = other.m02;
		matrix.m03 = other.m03;
		matrix.m10 = other.m10;
		matrix.m11 = other.m11;
		matrix.m12 = other.m12;
		matrix.m13 = other.m13;
		matrix.m20 = other.m20;
		matrix.m21 = other.m21;
		matrix.m22 = other.m22;
		matrix.m23 = other.m23;
		matrix.m30 = other.m00 * the_x + other.m10 * the_y + other.m20 * the_z + other.m30;
		matrix.m31 = other.m01 * the_x + other.m11 * the_y + other.m21 * the_z + other.m31;
		matrix.m32 = other.m02 * the_x + other.m12 * the_y + other.m22 * the_z + other.m32;
		matrix.m33 = other.m33;
		
		return matrix;

	}

	
	// scales matrix
	
	MLMatrix4 MLMatrix4Scale( 	
		MLMatrix4 	other ,
		float 		the_x , 
		float 		the_y , 
		float		the_z )
	{

		other.m00 *= the_x;
		other.m11 *= the_y;
		other.m22 *= the_z;
		
		return other;
	
	}


	// rotates matrix

	MLMatrix4 MLMatrix4Rotate(  	
		MLMatrix4 	theMatrix  ,
		float 		the_radians , 
		float 		the_x , 
		float 		the_y , 
		float 		the_z )
	{

		MLMatrix4 rotation;
		
		rotation = MLMatrix4CreateRotation( the_radians , the_x , the_y , the_z );
		return MLMatrix4Multiply( theMatrix , rotation );
			
	}


	// inverts matrix
	
	MLMatrix4 MLMatrix4Invert( MLMatrix4 source , char* success )
	{
	
		float determinant;
		MLMatrix4 inverse;

		inverse.m00 = source.m11 * source.m22 * source.m33 -
					  source.m11 * source.m23 * source.m32 -
					  source.m21 * source.m12 * source.m33 +
					  source.m21 * source.m13 * source.m32 +
					  source.m31 * source.m12 * source.m23 -
					  source.m31 * source.m13 * source.m22;

		inverse.m10 = -source.m10* source.m22 * source.m33 +
					  source.m10 * source.m23 * source.m32 +
					  source.m20 * source.m12 * source.m33 -
					  source.m20 * source.m13 * source.m32 -
					  source.m30 * source.m12 * source.m23 +
					  source.m30 * source.m13 * source.m22;

		inverse.m20 = source.m10 * source.m21 * source.m33 -
					  source.m10 * source.m23 * source.m31 -
					  source.m20 * source.m11 * source.m33 +
					  source.m20 * source.m13 * source.m31 +
					  source.m30 * source.m11 * source.m23 -
					  source.m30 * source.m13 * source.m21;

		inverse.m30 = -source.m10* source.m21 * source.m32 +
					  source.m10 * source.m22 * source.m31 +
					  source.m20 * source.m11 * source.m32 -
					  source.m20 * source.m12 * source.m31 -
					  source.m30 * source.m11 * source.m22 +
					  source.m30 * source.m12 * source.m21;

		inverse.m01 = -source.m01* source.m22 * source.m33 +
					  source.m01 * source.m23 * source.m32 +
					  source.m21 * source.m02 * source.m33 -
					  source.m21 * source.m03 * source.m32 -
					  source.m31 * source.m02 * source.m23 + 
					  source.m31 * source.m03 * source.m22;

		inverse.m11 = source.m00 * source.m22 * source.m33 -
					  source.m00 * source.m23 * source.m32 -
					  source.m20 * source.m02 * source.m33 +
					  source.m20 * source.m03 * source.m32 +
					  source.m30 * source.m02 * source.m23 -
					  source.m30 * source.m03 * source.m22;

		inverse.m21 = -source.m00* source.m21 * source.m33 +
					  source.m00 * source.m23 * source.m31 +
					  source.m20 * source.m01 * source.m33 -
					  source.m20 * source.m03 * source.m31 -
					  source.m30 * source.m01 * source.m23 + 
					  source.m30 * source.m03 * source.m21;

		inverse.m31 = source.m00 * source.m21 * source.m32 -
					  source.m00 * source.m22 * source.m31 -
					  source.m20 * source.m01 * source.m32 +
					  source.m20 * source.m02 * source.m31 +
					  source.m30 * source.m01 * source.m22 - 
					  source.m30 * source.m02 * source.m21;

		inverse.m02 = source.m01 * source.m12 * source.m33 -
					  source.m01 * source.m13 * source.m32 -
					  source.m11 * source.m02 * source.m33 +
					  source.m11 * source.m03 * source.m32 +
					  source.m31 * source.m02 * source.m13 -
					  source.m31 * source.m03 * source.m12;

		inverse.m12 = -source.m00* source.m12 * source.m33 +
					  source.m00 * source.m13 * source.m32 +
					  source.m10 * source.m02 * source.m33 -
					  source.m10 * source.m03 * source.m32 -
					  source.m30 * source.m02 * source.m13 + 
					  source.m30 * source.m03 * source.m12;

		inverse.m22 = source.m00 * source.m11 * source.m33 -
					  source.m00 * source.m13 * source.m31 -
					  source.m10 * source.m01 * source.m33 +
					  source.m10 * source.m03 * source.m31 +
					  source.m30 * source.m01 * source.m13 - 
					  source.m30 * source.m03 * source.m11;

		inverse.m32 = -source.m00* source.m11 * source.m32 +
					  source.m00 * source.m12 * source.m31 +
					  source.m10 * source.m01 * source.m32 -
					  source.m10 * source.m02 * source.m31 -
					  source.m30 * source.m01 * source.m12 +
					  source.m30 * source.m02 * source.m11;

		inverse.m03 = -source.m01* source.m12 * source.m23 +
					  source.m01 * source.m13 * source.m22 +
					  source.m11 * source.m02 * source.m23 - 
					  source.m11 * source.m03 * source.m22 - 
					  source.m21 * source.m02 * source.m13 + 
					  source.m21 * source.m03 * source.m12;

		inverse.m13 = source.m00 * source.m12 * source.m23 -
					  source.m00 * source.m13 * source.m22 -
					  source.m10 * source.m02 * source.m23 +
					  source.m10 * source.m03 * source.m22 +
					  source.m20 * source.m02 * source.m13 -
					  source.m20 * source.m03 * source.m12;

		inverse.m23 = -source.m00* source.m11 * source.m23 +
					  source.m00 * source.m13 * source.m21 +
					  source.m10 * source.m01 * source.m23 -
					  source.m10 * source.m03 * source.m21 -
					  source.m20 * source.m01 * source.m13 +
					  source.m20 * source.m03 * source.m11;

		inverse.m33 = source.m00 * source.m11 * source.m22 -
					  source.m00 * source.m12 * source.m21 -
					  source.m10 * source.m01 * source.m22 + 
					  source.m10 * source.m02 * source.m21 + 
					  source.m20 * source.m01 * source.m12 - 
					  source.m20 * source.m02 * source.m11;

		determinant = source.m00 * inverse.m00 +
					  source.m01 * inverse.m10 +
					  source.m02 * inverse.m20 +
					  source.m03 * inverse.m30;
		
		if ( determinant == 0 && success != NULL ) *success = 0;

		MLMatrix4MultiplyWithNumber( &inverse , 1.0 / determinant );
			
		return inverse;
	
	}	


	// transposes matrix
	
	MLMatrix4 MLMatrix4Transpose( MLMatrix4 other )
	{

		MLMatrix4 matrix;

		matrix.m00 = other.m00;
		matrix.m11 = other.m11;
		matrix.m22 = other.m22;
		matrix.m33 = other.m33;
		
		matrix.m10 = other.m01;
		matrix.m01 = other.m10;
		matrix.m20 = other.m02;
		matrix.m02 = other.m20;
		matrix.m30 = other.m03;
		matrix.m03 = other.m30;
		
		matrix.m21 = other.m12;
		matrix.m12 = other.m21;
		matrix.m31 = other.m13;
		matrix.m13 = other.m31;
		matrix.m32 = other.m23;
		matrix.m23 = other.m32;
		
		return matrix;
	
	}


	// multiplies with number

	void MLMatrix4MultiplyWithNumber( MLMatrix4* matrix , float number )
	{

		matrix->m00 *= number;
		matrix->m01 *= number;
		matrix->m02 *= number;
		matrix->m03 *= number;
		matrix->m10 *= number;
		matrix->m11 *= number;
		matrix->m12 *= number;
		matrix->m13 *= number;
		matrix->m20 *= number;
		matrix->m21 *= number;
		matrix->m22 *= number;
		matrix->m23 *= number;
		matrix->m30 *= number;
		matrix->m31 *= number;
		matrix->m32 *= number;
		matrix->m33 *= number;
	
	}


    void MLMatrix4ExtractAngles(  MLMatrix4 matrix , float* x , float* y , float* z )
    {

        float y1,y2,x1,x2,z1,z2;
        
        x1 = x2 = y1 = y2 = z1 = z2 = 0.0;

        if ( fabs(matrix.m20) !=  1 )
        {
            
            y1 = -asinf( matrix.m20 );
            y2 = M_PI - y1;
            x1 = atan2( matrix.m21 / cosf( y1 ) , matrix.m22 / cos( y1 ) );
            x2 = atan2( matrix.m21 / cosf( y2 ) , matrix.m22 / cos( y2 ) );
            z1 = atan2( matrix.m10 / cosf( y1 ) , matrix.m00 / cos( y1 ) );
            z2 = atan2( matrix.m10 / cosf( y2 ) , matrix.m00 / cos( y2 ) );

        }
        else
        {

            z1 = 0;
            
            if ( matrix.m20 == -1.0 )
            {
            
                y1 = M_PI / 2.0;
                x1 = z1 + atan2( matrix.m01 , matrix.m02 );
                
            }
            else
            {
            
                y1 = -M_PI / 2.0;
                x1 = -z1 + atan2( -matrix.m01 , -matrix.m02 );
                
            }
            
        }
        
        printf( "\nangles %f %f %f , %f %f %f" , x1 * 180 / M_PI , y1 * 180 / M_PI, z1* 180 / M_PI , x2* 180 / M_PI , y2* 180 / M_PI , z2* 180 / M_PI );
        
        *x = x1;
        *y = y1;
        *z = z1;
    
    }


	// copies matrix to array

	void MLMatrix4ToArray( MLMatrix4* matrix , float* result )
	{
	
		result[ 0 ] = matrix->m00;
		result[ 1 ] = matrix->m01;
		result[ 2 ] = matrix->m02;
		result[ 3 ] = matrix->m03;
		result[ 4 ] = matrix->m10;
		result[ 5 ] = matrix->m11;
		result[ 6 ] = matrix->m12;
		result[ 7 ] = matrix->m13;
		result[ 8 ] = matrix->m20;
		result[ 9 ] = matrix->m21;
		result[ 10 ] = matrix->m22;
		result[ 11 ] = matrix->m23;
		result[ 12 ] = matrix->m30;
		result[ 13 ] = matrix->m31;
		result[ 14 ] = matrix->m32;
		result[ 15 ] = matrix->m33;
	
	}


	// copies array to matrix

	void MLMatrix4FromArray( MLMatrix4* matrix , float* array )
	{
	
		matrix->m00 = array[ 0 ];
		matrix->m01 = array[ 1 ];
		matrix->m02 = array[ 2 ];
		matrix->m03 = array[ 3 ];
		matrix->m10 = array[ 4 ];
		matrix->m11 = array[ 5 ];
		matrix->m12 = array[ 6 ];
		matrix->m13 = array[ 7 ];
		matrix->m20 = array[ 8 ];
		matrix->m21 = array[ 9 ];
		matrix->m22 = array[ 10 ];
		matrix->m23 = array[ 11 ];
		matrix->m30 = array[ 12 ];
		matrix->m31 = array[ 13 ];
		matrix->m32 = array[ 14 ];
		matrix->m33 = array[ 15 ];
	
	}


	// describes matrix

	void MLMatrix4Describe( MLMatrix4 matrix )
	{
	
		printf( "\n%.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f | %.2f %.2f %.2f %.2f" ,
				matrix.m00 ,
				matrix.m01 ,
				matrix.m02 ,
				matrix.m03 ,
				matrix.m10 ,
				matrix.m11 ,
				matrix.m12 ,
				matrix.m13 ,
				matrix.m20 ,
				matrix.m21 ,
				matrix.m22 ,
				matrix.m23 ,
				matrix.m30 ,
				matrix.m31 ,
				matrix.m32 ,
				matrix.m33 );
	
	}

