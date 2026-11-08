
#ifndef OBJECT
#define OBJECT

#include "..\math.h"
#include "..\settings.h"
#include <utility>

enum eOBJType{
    ONULL,
    OSPHERE,
    OCAMERA,
    OSUN
};

class OBJObject{
    public:
        FVector3D Position;
        Quaternion Rotation;
        FVector3D Scale;
        eOBJType Type;
        bool isActive;

    OBJObject()
        : Position(0, 0, 0), Rotation(0, 0, 0, 1), Scale(1, 1, 1), Type(ONULL), isActive(false) {}

    OBJObject(eOBJType t) 
        : Position(0, 0, 0), Rotation(0, 0, 0, 1), Scale(1, 1, 1), Type(t), isActive(true) {}

    OBJObject(const OBJObject& o) 
        : Position(o.Position), Rotation(o.Rotation), Scale(o.Scale), Type(o.Type), isActive(o.isActive) {}

    OBJObject(const FVector3D& p, const Quaternion& r, const FVector3D& s, eOBJType t, bool i)
        : Position(p), Rotation(r), Scale(s), Type(t), isActive(i) {}
    
    FVector3D GetForwardVector() const;
    FVector3D GetRightVector() const;
    FVector3D GetUpVector() const;

};
extern OBJObject *OBJPool[OBJPoolSize + 1];
extern int OBJObjectCount;


namespace Object {
    template <typename T, typename... Args>
    T* CreateObj(Args&&... args) {
        if (OBJObjectCount == OBJPoolSize) {
            return nullptr;
        }
    
        T* newObj = new T(std::forward<Args>(args)...);
        OBJPool[OBJObjectCount] = newObj; 
        OBJObjectCount++;
    
        return newObj;
    }
}


#endif
