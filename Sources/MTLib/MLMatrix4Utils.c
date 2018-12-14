//
//  MLMatrix4Utils.c
//  Cortex
//
//  Created by Milan Toth on 21/12/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#include "MLMatrix4Utils.h"


	MLVector4 MLMatrix4MultiplyVector4( 
		MLMatrix4 matrix ,
		MLVector4 vector )
	{
	
		MLVector4 result;

    	result.x = matrix.m00 * vector.x + matrix.m10  * vector.y + matrix.m20 * vector.z + matrix.m30 * vector.w;
		result.y = matrix.m01 * vector.x + matrix.m11  * vector.y + matrix.m21 * vector.z + matrix.m31 * vector.w;
		result.z = matrix.m02 * vector.x + matrix.m12  * vector.y + matrix.m22 * vector.z + matrix.m32 * vector.w;
		result.w = matrix.m03 * vector.x + matrix.m13  * vector.y + matrix.m23 * vector.z + matrix.m33 * vector.w;

	    return result;

	}


	MLVector4 MLMatrix4ProjectVector4ToScreen(
		MLMatrix4 theMVPMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight )
	{

		MLVector4 result;
		MLVector4 vector;

		// printf( "\nVECTORTOSCREEN %f %f %f %f" , theVector.x , theVector.y , theVector.z , theVector.w );
	
		theVector.w = 1;
				
		vector = MLMatrix4MultiplyVector4( theMVPMatrix , theVector );

		// perspective divide to normalized device coordinates
		
		vector.x /= vector.w;
		vector.y /= vector.w;
		vector.z /= vector.w;
		
		// viewport transformation

		result.x = ( vector.x + 1 ) * theWidth * 0.5;
		result.y = ( vector.y + 1 ) * theHeight * 0.5;
		result.z = vector.z;
		result.w = vector.w;
		
		return result;
	
	}


	MLVector4 MLMatrix4UnProjectVector4FromScreen( 
		MLMatrix4 theMVPMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight )
	{

		// printf( "\n\nVECTORFROMSCREEN %f %f %f %f" , theVector.x , theVector.y , theVector.z , theVector.w );

		char success;
		MLVector4 vector;
		MLVector4 result;
		MLMatrix4 invert;
		
		success = 1;
		
		// invert projection matrix

		invert = MLMatrix4Invert( theMVPMatrix , &success );
		
		// get normalized device coordinates

		vector.x = theVector.x / theWidth * 2.0 - 1.0;
		vector.y = theVector.y / theHeight * 2.0 - 1.0;
		vector.z = theVector.z;
		vector.w = 1.0;

		// multiply transposed inverted projection matrix with vector

		result = MLMatrix4MultiplyVector4( invert , vector );

		if ( result.w == 0 ) return result;
		
		// get world space coordinates

		result.w = 1.0 / result.w;
		
		result.x *= result.w;
		result.y *= result.w;
		result.z *= result.w;

		return result;
	
	}


    
	void MLMatrix4Extract(
		MLMatrix4 the_trafo ,
		MLVector3* the_scale ,
        MLVector3* the_rotation ,
        MLVector3* the_translation )
    {
    
        MLVector4 base_o = MLVector4Create( 0 , 0 , 0 , 1 );
        MLVector4 base_x = MLVector4Create( 1 , 0 , 0 , 1 );
        MLVector4 base_y = MLVector4Create( 0 , 1 , 0 , 1 );

        base_o = MLMatrix4MultiplyVector4( the_trafo , base_o );
        base_x = MLMatrix4MultiplyVector4( the_trafo , base_x );
        base_y = MLMatrix4MultiplyVector4( the_trafo , base_y );

        MLVector3 final_o = MLVector3Create( base_o.x , base_o.y , base_o.z );
        MLVector3 final_x = MLVector3Create( base_x.x , base_x.y , base_x.z );
        MLVector3 final_y = MLVector3Create( base_y.x , base_y.y , base_y.z );
        
        the_translation->x = final_o.x;
        the_translation->y = final_o.y;
        the_translation->z = final_o.z;
        
        final_x = MLVector3Sub( final_x , final_o );
        final_y = MLVector3Sub( final_y , final_o );
        
        float scale_factor = MLVector3Length( final_x );
        
        the_scale->x = scale_factor;
        the_scale->y = scale_factor;
        the_scale->z = scale_factor;
        
        *the_rotation = MLVector3GetXYUnitRotation( final_x , final_y );
    
    }
