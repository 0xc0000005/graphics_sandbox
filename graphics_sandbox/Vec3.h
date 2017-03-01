#pragma once
#include <cmath>

template<typename T>
struct Vec3
{
    T x, y, z;

    Vec3() : Vec3(0) {}
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
    Vec3(const T& xx) : Vec3(xx, xx, xx) {}
    virtual ~Vec3() {}

    T length() const { return sqrt(dot(*this)); } // sqrt(x * x + y * y + z * z)
    T dot(const Vec3& v) const { return (x * v.x + y * v.y + z * v.z); }
    Vec3 cross(const Vec3& v) const { return Vec3{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x}; }

    Vec3& normalize() {
        T len = length();
        if (len > 0) {
            T invert_len = 1 / len;
            x *= invert_len;
            y *= invert_len;
            z *= invert_len;
        }
        return *this;
    }

    Vec3 operator+ (const Vec3 &v) const { return Vec3{ x + v.x, y + v.y, z + v.z }; }
    Vec3 operator- (const Vec3 &v) const { return Vec3{ x - v.x, y - v.y, z - v.z }; }
    Vec3 operator* (const T &r) const { return Vec3{ x * r, y * r, z * r }; }
    Vec3 operator/ (const T &r) const { return Vec3{ x / r, y / r, z / r }; }
};

template<typename T>
class Point : public Vec3<T>
{
public:
    using Vec3<T>::Vec3;
};

template<typename T>
class Vector : public Vec3<T>
{
public:
    using Vec3<T>::Vec3;
};

