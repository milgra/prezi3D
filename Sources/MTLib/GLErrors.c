//
//  GLErrors.c
//  GameProg
//
//  Created by Milan Toth on 29/01/14.
//  Copyright (c) 2014 Milan Toth. All rights reserved.
//

    #include "GLErrors.h"


    void gl_errors_show( const char* theOp )
    {
    
        GLenum error;
    
        do
        {
        
            error = glGetError( );
            
            if ( error > GL_NO_ERROR ) printf( "\nGL Error at %s : %i" , theOp , error );
        
        }
        while ( error > GL_NO_ERROR );
    
    }