//
//  MLVector3.h
//  Cortex
//
//  Created by Milan Toth on 9/18/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#ifndef MLVector3_h
#define MLVector3_h


	#include <math.h>
	#include <stdio.h>

	struct _MLVector3
	{
		float x, y, z;
	};
	typedef struct _MLVector3 MLVector3;
	
	
	MLVector3 MLVector3Create(
		float the_x ,
		float the_y ,
		float theZ );

	MLVector3 MLVector3Add(
		MLVector3 a ,
		MLVector3 b );
	
	MLVector3 MLVector3Sub(
		MLVector3 a ,
		MLVector3 b );

	float MLVector3Length(
		MLVector3 a );

	float MLVector3Angle(
		MLVector3 a ,
		MLVector3 b );

	float MLVector3Dot(
		MLVector3 a ,
		MLVector3 b );

	MLVector3 MLVector3Cross(
		MLVector3 vectorLeft ,
		MLVector3 vectorRight);

	MLVector3 MLVector3Scale(
		MLVector3 a ,
		float f );
	
	MLVector3 MLVector3Normalize(
		MLVector3 v );

	MLVector3 MLVector3IntersectWithPlane(
		MLVector3 lineV1 ,
		MLVector3 lineV2 ,
		MLVector3 planeV ,
		MLVector3 planeN );

    MLVector3 MLVector3PerspectivePush(
        MLVector3 vector ,
        float push ,
        float screenX ,
        float screenY ,
        float eyeZ );

    MLVector3 MLVector3RotateAroundX( MLVector3 vector , float the_angle );
    MLVector3 MLVector3RotateAroundY( MLVector3 vector , float the_angle );
    MLVector3 MLVector3RotateAroundZ( MLVector3 vector , float the_angle );

	MLVector3 MLVector3GetXYUnitRotation(
        MLVector3 the_x ,
        MLVector3 the_y );

    float MLVector3Distance( MLVector3 vectorA , MLVector3 vectorB );

    void MLVector3ToArray( MLVector3* vector , float* array );


#endif
