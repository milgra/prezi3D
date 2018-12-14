#ifndef GLErrors_h
#define GLErrors_h

    #include <stdio.h>
    #ifdef OSX
    #include <OpenGL/gl3.h>
    #elif defined IOS
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
    #endif

    void gl_errors_show( const char* theOp );

#endif
