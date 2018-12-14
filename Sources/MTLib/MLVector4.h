//
//  MLVector4.h
//  Cortex
//
//  Created by Milan Toth on 9/27/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#ifndef Cortex_MLVector4_h
#define Cortex_MLVector4_h

	struct _MLVector4
	{
		float x, y, z, w;
	};
	typedef struct _MLVector4 MLVector4;
	
	
	MLVector4 MLVector4Create( float the_x ,
							 float the_y , 
							 float theZ ,
							 float theW );

	MLVector4 MLVector4Sub(
		MLVector4 a ,
		MLVector4 b );


#endif
