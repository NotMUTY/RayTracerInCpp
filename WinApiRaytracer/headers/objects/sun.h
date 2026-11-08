
#include "object.h"

class OBJSun : public OBJObject{
    public:
        float LightIntensity;

    OBJSun(FVector3D p, Quaternion r, FVector3D s, bool ia, float li) : OBJObject(p, r, s, OSUN, ia), LightIntensity(li) {};

};

