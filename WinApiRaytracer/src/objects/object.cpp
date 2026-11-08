

#include "..\..\headers\objects.h"
#include <memory>
#include <utility>

FVector3D OBJObject::GetForwardVector() const {
    float x = 2.0f * (Rotation.fx * Rotation.fz + Rotation.fw * Rotation.fy);
    float y = 2.0f * (Rotation.fy * Rotation.fz - Rotation.fw * Rotation.fx);
    float z = 1.0f - 2.0f * (Rotation.fx * Rotation.fx + Rotation.fy * Rotation.fy);
    return FVector3D(x, y, z);
}

FVector3D OBJObject::GetRightVector() const {
    float x = 1.0f - 2.0f * (Rotation.fy * Rotation.fy + Rotation.fz * Rotation.fz);
    float y = 2.0f * (Rotation.fx * Rotation.fy + Rotation.fw * Rotation.fz);
    float z = 2.0f * (Rotation.fx * Rotation.fz - Rotation.fw * Rotation.fy);
    return FVector3D(x, y, z);
}

    
FVector3D OBJObject::GetUpVector() const {
    float x = 2.0f * (Rotation.fx * Rotation.fy - Rotation.fw * Rotation.fz);
    float y = 1.0f - 2.0f * (Rotation.fx * Rotation.fx + Rotation.fz * Rotation.fz);
    float z = 2.0f * (Rotation.fy * Rotation.fz + Rotation.fw * Rotation.fx);
    return FVector3D(x, y, z);
}


namespace Object {

    

}
