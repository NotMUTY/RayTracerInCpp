
#include "..\headers\math.h"
#include "Windows.h"
#include <cmath>
#include <ctime>
#include <cstdint>

//--------------------FVECTOR3D CLASS ACTIONS--------------------

void FVector3D::Normalize(){
    float len = this->GetLength();
        
    if (len == 0.0f){
        *this = FVector3D(0, 0, 0);
        return;
    }            

    *this = *this / len;
}

inline float FVector3D::GetLength() const{
    return sqrt(fx*fx + fy*fy + fz*fz);
}

FVector3D::FVector3D(const Quaternion &q) : fx(q.fx), fy(q.fy), fz(q.fz) {}

float FVector3D::Distance(FVector3D &n){
    // fy - n.fy eklendi
    return sqrt(pow(this->fx - n.fx, 2) + pow(this->fy - n.fy, 2) + pow(this->fz - n.fz, 2));
}

Quaternion FVector3D::ConvertToRotation(){
    float p = this->fx * DEGREESTORADIANS / 2.0f;
    float y = this->fy * DEGREESTORADIANS / 2.0f;
    float r = this->fz * DEGREESTORADIANS / 2.0f;

    float cp = cos(p);
    float sp = sin(p);
    float cy = cos(y);
    float sy = sin(y);
    float cr = cos(r);
    float sr = sin(r);

    Quaternion q;
    q.fw = cr * cp * cy + sr * sp * sy;
    q.fx = cr * sp * cy + sr * cp * sy;
    q.fy = cr * cp * sy - sr * sp * cy;
    q.fz = sr * cp * cy - cr * sp * sy;
    return q;
}



namespace Vector3D {
    inline float GetLength(FVector3D &n){
        return sqrt(n.fx*n.fx + n.fy*n.fy + n.fz*n.fz);
    }
}

//--------------------RAY CLASS ACTIONS--------------------

bool Ray::Trace(){
    return true;
}

//QUATERNION



//--------------------NO CLASS ACTIONS--------------------

float DotProduct(FVector3D a, FVector3D b) {
    return a.fx * b.fx + a.fy * b.fy + a.fz * b.fz;
}

uint32_t PseudoRandom(uint32_t mexclusive){
    static uint32_t state = 123456;
    state = state * 1664525 + 1013904223; 
    return state % mexclusive;
}

uint32_t PseudoRandom(uint32_t mexclusive, uint32_t seed){
    static uint32_t state = 123456;
    seed ++;
    state = state * 1664525 * seed + 1013904223 + (GetTickCount() + 1); 
    return state % mexclusive;
}   
