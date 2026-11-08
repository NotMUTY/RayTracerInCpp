
#pragma once

#include "object.h"
#include "math.h"
#include "..\settings.h"

struct ViewPlane {
    float Distance;
    float Width;
    float HalfWidth;
    float Height;
    float HalfHeight;
};

class OBJCamera : public OBJObject {
    public:
        float FOV;
        ViewPlane VPlane;

    OBJCamera() : OBJObject(OCAMERA), FOV(60.0f) {
        VPlane.Distance = 2.0f;
        VPlane.HalfWidth = VPlane.Distance * tan(FOV / 2 * DEGREESTORADIANS);
        VPlane.Width = 2.0f * VPlane.HalfWidth;
        VPlane.Height = VPlane.Width / STScreenRatio;
        VPlane.HalfHeight = VPlane.Height / 2;
    }

    OBJCamera(FVector3D p, Quaternion r, FVector3D s, bool ia, float f) : OBJObject(p, r, s, OCAMERA, ia), FOV(f) {
        VPlane.Distance = 2.0f;
        VPlane.HalfWidth = VPlane.Distance * tan(FOV / 2 * DEGREESTORADIANS);
        VPlane.Width = 2.0f * VPlane.HalfWidth;
        VPlane.Height = VPlane.Width / STScreenRatio;
        VPlane.HalfHeight = VPlane.Height / 2;
    };

};
