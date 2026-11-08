
#include "object.h"

class OBJSphere : public OBJObject {
    public:
        float Radius;

    OBJSphere() : OBJObject(), Radius(1) {};

    OBJSphere(FVector3D p, Quaternion r, FVector3D s, bool ia, float rd) :
        OBJObject(p, r, s, OSPHERE, ia), Radius(rd) {};

};
