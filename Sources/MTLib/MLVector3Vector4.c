    #include "MLVector3Vector4.h"


    MLVector3 MLVector3FromVector4( MLVector4 theVector )
    {
    
        return MLVector3Create( theVector.x , theVector.y , theVector.z );
    
    }