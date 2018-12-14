//
//  MLMatrix4Utils.h
//  Cortex
//
//  Created by Milan Toth on 21/12/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#ifndef Cortex_MLMatrix4Vector4_h
#define Cortex_MLMatrix4Vector4_h

#include "MLVector3.h"
#include "MLVector4.h"
#include "MLMatrix4.h"


	MLVector4 MLMatrix4ProjectVector4ToScreen( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight );

	MLVector4 MLMatrix4UnProjectVector4FromScreen( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight );

	MLVector4 MLMatrix4MultiplyVector4( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector );

	MLVector4 MLMatrix4MultiplyVector4( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector );

	void MLMatrix4Extract(
		MLMatrix4 theMatrix , 
		MLVector3* theScale ,
        MLVector3* theRotation ,
        MLVector3* theTranslation );

#endif
