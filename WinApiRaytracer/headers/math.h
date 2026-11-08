#ifndef MATH
#define MATH

#include <cstdint>
#include <cmath>

constexpr float PI = 3.14159265f;
constexpr float DEGREESTORADIANS = PI / 180;

class Quaternion;

class FVector3D {
public:
    float fx;
    float fy;
    float fz;

    FVector3D(float x, float y, float z) : fx(x), fy(y), fz(z) {};
    FVector3D(const Quaternion &q);
    FVector3D() : fx(0.0f), fy(0.0f), fz(0.0f) {};

    static FVector3D Unit() {
        return FVector3D(1.0f, 1.0f, 1.0f);
    };

    FVector3D& operator=(const FVector3D &n) { 
        fx = n.fx; fy = n.fy; fz = n.fz; 
        return *this; 
    }
    FVector3D operator+(const FVector3D &n) const { return FVector3D(fx + n.fx, fy + n.fy, fz + n.fz); }
    FVector3D operator-(const FVector3D &n) const { return FVector3D(fx - n.fx, fy - n.fy, fz - n.fz); }
    FVector3D operator*(const FVector3D &n) const { return FVector3D(fx * n.fx, fy * n.fy, fz * n.fz); }
    FVector3D operator/(const FVector3D &n) const { return FVector3D(fx / n.fx, fy / n.fy, fz / n.fz); }

    FVector3D operator*(const int n) const { return FVector3D(fx * n, fy * n, fz * n); }
    FVector3D operator/(const int n) const { return FVector3D(fx / n, fy / n, fz / n); }

    FVector3D operator*(const float n) const { return FVector3D(fx * n, fy * n, fz * n); }
    FVector3D operator/(const float n) const { return FVector3D(fx / n, fy / n, fz / n); }

    FVector3D operator*(const double n) const { return FVector3D(fx * n, fy * n, fz * n); }
    FVector3D operator/(const double n) const { return FVector3D(fx / n, fy / n, fz / n); }

    void Normalize();
    Quaternion ConvertToRotation();
    
    inline float GetLength() const;
    float Distance(FVector3D &n);

};

namespace Vector3D{
    inline float GetLength(FVector3D &n);
}


class Quaternion {
    public:
        float fx;
        float fy;
        float fz;
        float fw;

    Quaternion(float x, float y, float z, float w) : fx(x), fy(y), fz(z), fw(w) {};
    Quaternion(const FVector3D &n) {
        float p = n.fx * DEGREESTORADIANS / 2.0f;
        float y = n.fy * DEGREESTORADIANS / 2.0f;
        float r = n.fz * DEGREESTORADIANS / 2.0f;

        float cp = cos(p);
        float sp = sin(p);
        float cy = cos(y);
        float sy = sin(y);
        float cr = cos(r);
        float sr = sin(r);

        this->fw = cr * cp * cy + sr * sp * sy;
        this->fx = cr * sp * cy + sr * cp * sy;
        this->fy = cr * cp * sy - sr * sp * cy;
        this->fz = sr * cp * cy - cr * sp * sy;
    }
    Quaternion() : fx(0.0f), fy(0.0f), fz(0.0f), fw(1.0f) {};

    Quaternion& operator=(const Quaternion &n) { 
        fx = n.fx; fy = n.fy; fz = n.fz; fw = n.fw; 
        return *this; 
    }
    Quaternion operator+(const Quaternion &n) const { return Quaternion(fx + n.fx, fy + n.fy, fz + n.fz, fw + n.fw); }
    Quaternion operator-(const Quaternion &n) const { return Quaternion(fx - n.fx, fy - n.fy, fz - n.fz, fw - n.fw); }
    
    Quaternion operator*(const Quaternion &n) const {
        return Quaternion(
            fw * n.fx + fx * n.fw + fy * n.fz - fz * n.fy,
            fw * n.fy - fx * n.fz + fy * n.fw + fz * n.fx,
            fw * n.fz + fx * n.fy - fy * n.fx + fz * n.fw,
            fw * n.fw - fx * n.fx - fy * n.fy - fz * n.fz
        );
    } 

    Quaternion Conjugate() const {
        return Quaternion(-fx, -fy, -fz, fw);
    }

    float SquaredNorm() const {
        return fx * fx + fy * fy + fz * fz + fw * fw;
    }

    Quaternion Inverse() const {
        float normSq = SquaredNorm();
        if (normSq == 0.0f) return Quaternion(0, 0, 0, 0);
        return Conjugate() * (1.0f / normSq);
    }

    Quaternion operator/(const Quaternion &n) const {
        return (*this) * n.Inverse();
    }

    Quaternion operator*(const float n) const { return Quaternion(fx * n, fy * n, fz * n, fw * n); }
    Quaternion operator/(const float n) const { return Quaternion(fx / n, fy / n, fz / n, fw / n); }

};


class Ray{
    public:
        FVector3D Start;
        Quaternion Direction;
        float Length;
    
    Ray() : Start(FVector3D()), Direction(Quaternion()), Length(0) {}    
    Ray(FVector3D s, Quaternion r, float l) : Start(s), Direction(r), Length(l) {}    

    bool Trace();
};

FVector3D Normalize(const FVector3D &n);
float DotProduct(FVector3D a, FVector3D b);

uint32_t PseudoRandom(uint32_t mexclusive);
uint32_t PseudoRandom(uint32_t mexclusive, uint32_t seed);

#endif