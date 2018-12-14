//
//  MLVector4.c
//  Cortex
//
//  Created by Milan Toth on 9/27/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#include "MLVector4.h"


	MLVector4 MLVector4Create( float the_x ,
							 float the_y , 
							 float theZ ,
							 float theW )
	{
	
		MLVector4 result;
		
		result.x = the_x;
		result.y = the_y;
		result.z = theZ;
		result.w = theW;
		
		return result;
	
	}


    MLVector4 MLVector4Sub(
        MLVector4 a ,
        MLVector4 b )
    {
    
		MLVector4 result;
		
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
		result.w = a.w - b.w;
		
		return result;
    
    }
