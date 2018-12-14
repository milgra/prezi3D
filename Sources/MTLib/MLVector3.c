//
//  MLVector43.c
//  Cortex
//
//  Created by Milan Toth on 9/18/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#include "MLVector3.h"


	// creates vector

	MLVector3 MLVector3Create(  float the_x ,
                                float the_y ,
                                float theZ )
	{
	
		MLVector3 result;
		
		result.x = the_x;
		result.y = the_y;
		result.z = theZ;
		
		return result;
	
	}


	// adds vectors

	MLVector3 MLVector3Add( MLVector3 a , MLVector3 b )
	{
	
		MLVector3 result;
		
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		result.z = a.z + b.z;
		
		return result;
				
	}


	// substracts vectors
	
	MLVector3 MLVector3Sub( MLVector3 a , MLVector3 b )
	{

		MLVector3 result;
		
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
		
		return result;
				
	}


	float MLVector3Length(
		MLVector3 a )
    {
    
        return sqrtf( a.x * a.x + a.y * a.y + a.z * a.z );
    
    }


	float MLVector3Angle(
		MLVector3 a ,
		MLVector3 b )
    {
    
        return acosf( MLVector3Dot( a , b ) / ( MLVector3Length( a ) * MLVector3Length( b ) )  );

    }


	// creates dot product

	float MLVector3Dot( MLVector3 a , MLVector3 b )
	{
		
		return a.x * b.x + a.y * b.y + a.z * b.z;
				
	}


	// creates cross product

	MLVector3 MLVector3Cross( MLVector3 vectorLeft, MLVector3 vectorRight)
	{
	
		MLVector3 v;
		
		v.x = vectorLeft.y * vectorRight.z - vectorLeft.z * vectorRight.y;
		v.y = vectorLeft.z * vectorRight.x - vectorLeft.x * vectorRight.z;
		v.z = vectorLeft.x * vectorRight.y - vectorLeft.y * vectorRight.x;

		return v;
		
	}


	// scales vector

	MLVector3 MLVector3Scale( MLVector3 a , float f )
	{

		MLVector3 result;

		result.x = a.x * f;
		result.y = a.y * f;
		result.z = a.z * f;
		
		return result;
				
	}
	

	MLVector3 MLVector3Normalize( MLVector3 matrix )
    {
    
		float scale;

		scale = 1.0f / sqrtf( matrix.x * matrix.x + matrix.y * matrix.y + matrix.z * matrix.z );

		matrix.x *= scale;
		matrix.y *= scale;
		matrix.z *= scale;
		
		return matrix;
    
    }


	// intersects vector with plane

	MLVector3 MLVector3IntersectWithPlane(
		MLVector3 lineV1 ,
		MLVector3 lineV2 ,
		MLVector3 planeV ,
		MLVector3 planeN )
	{

		MLVector3 u, w, scale, result;
		float 	  div;

		u = MLVector3Sub( lineV2 , lineV1 );
		w = MLVector3Sub( planeV , lineV1 );
		div = MLVector3Dot( planeN , w ) / MLVector3Dot( planeN , u );
		scale = MLVector3Scale( u , div );
		result = MLVector3Add( lineV1 , scale );

		return result;
		
	}


    MLVector3 MLVector3PerspectivePush(
        MLVector3 vector ,
        float push ,
        float screenX ,
        float screenY ,
        float eyeZ )
    {

        float distX = screenX / 2 - vector.x;
        float distY = screenY / 2 - vector.y;
        
        float newDistZ = eyeZ - push;
        float newDistX = ( distX / eyeZ ) * newDistZ;
        float newDistY = ( distY / eyeZ ) * newDistZ;

        vector.x = screenX / 2 - newDistX;
        vector.y = screenY / 2 - newDistY;
        vector.z = vector.z + push;
        
        return vector;
    
    }


    void MLVector3ToArray( MLVector3* vector , float* result )
    {
    
		result[ 0 ] = vector->x;
		result[ 1 ] = vector->y;
		result[ 2 ] = vector->z;

    }


    MLVector3 MLVector3RotateAroundY( MLVector3 vector , float the_angle )
    {

        float epsilon = 0.00001;
    
        if ( fabs(vector.x) > epsilon || fabs(vector.z) > epsilon )
        {
    
            float angle = atan2( vector.z , vector.x );
            float length = sqrtf( vector.x * vector.x + vector.z * vector.z );
            
            vector.z = sin( angle + the_angle ) * length;
            vector.x = cos( angle + the_angle ) * length;
            
        }
    
        return vector;
    
    }


    MLVector3 MLVector3RotateAroundX( MLVector3 vector , float the_angle )
    {

        float epsilon = 0.00001;

        if ( fabs(vector.y) > epsilon || fabs(vector.z) > epsilon )
        {
    
            float angle = atan2( vector.z , vector.y );
            float length = sqrtf( vector.y * vector.y + vector.z * vector.z );
            
            vector.z = sin( angle + the_angle ) * length;
            vector.y = cos( angle + the_angle ) * length;
            
        }
    
        return vector;
    
    }


    MLVector3 MLVector3RotateAroundZ( MLVector3 vector , float the_angle )
    {

        float epsilon = 0.00001;

        if ( fabs(vector.y) > epsilon || fabs(vector.x) > epsilon )
        {
    
            float angle = atan2( vector.y , vector.x );
            float length = sqrtf( vector.x * vector.x + vector.y * vector.y );
            
            vector.y = sin( angle + the_angle ) * length;
            vector.x = cos( angle + the_angle ) * length;
            
        }
    
        return vector;
    
    }


	MLVector3 MLVector3GetXYUnitRotation(
        MLVector3 the_x ,
        MLVector3 the_y )
    {
    
        MLVector3 rotation;
        
        float angle;
        float epsilon = 0.00001;
        
        // rotate back final_x to base_x on Z axis
        
        if ( fabs(the_x.x) > epsilon || fabs(the_x.y) > epsilon )
        {

            angle = atan2( the_x.y , the_x.x  );

            rotation.z = angle;
            
            the_x = MLVector3RotateAroundZ( the_x , -angle );
            the_y = MLVector3RotateAroundZ( the_y , -angle );

        }
        else rotation.z = 0.0;

        // rotate back final_x to base_x on Y axis

        if ( fabs(the_x.x) > epsilon || fabs(the_x.z) > epsilon )
        {

            angle = atan2( the_x.z , the_x.x  );

            rotation.y = -angle;

            the_x = MLVector3RotateAroundY( the_x , -angle );
            the_y = MLVector3RotateAroundY( the_y , -angle );

        }
        else rotation.y = 0.0;
        
        // finally rotate back final_y to base_y on X axis

        if ( fabs(the_y.y) > epsilon || fabs(the_y.z) > epsilon )
        {

            angle = atan2( the_y.z , the_y.y  );
            
            rotation.x = angle;

            the_x = MLVector3RotateAroundX( the_x , -angle );
            the_y = MLVector3RotateAroundX( the_y , -angle );
            
        }
        else rotation.x = 0.0;
        
        return rotation;
    
    }


    float MLVector3Distance( MLVector3 vectorA , MLVector3 vectorB )
    {
    
        float dx , dy, dz;
        
        dx = vectorB.x - vectorA.x;
        dy = vectorB.y - vectorA.y;
        dz = vectorB.z - vectorA.z;
        
        return sqrtf( dx*dx + dy*dy + dz*dz );
    
    }
