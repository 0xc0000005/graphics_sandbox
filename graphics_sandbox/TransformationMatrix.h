#pragma once

#include <cmath>
#include "Matrix2.h"

template<typename T>
class TransformationMatrix
{
public:
    ~TransformationMatrix() = delete;

    static Matrix2<T, 4, 4> scale(const T& x_scale, const T& y_scale, const T& z_scale)
    {
        Matrix2<T, 4, 4> m;
        m(0, 0) = x_scale;
        m(1, 1) = y_scale;
        m(2, 2) = z_scale;
        return m;
    }

    enum class AXIS {X, Y, Z};

    static Matrix2<T, 4, 4>rotate(const T& angle, AXIS axis)
    {
        Matrix2<T, 4, 4> m;
        const T s = std::sin(angle);
        const T c = std::cos(angle);

        switch (axis)
        {
        case AXIS::X:
            m(0, 0) = 1;
            m(1, 1) = m(2, 2) = c;
            m(1, 2) = s;
            m(2, 1) = -s;
            break;
        case AXIS::Y:
            m(1, 1) = 1;
            m(0, 0) = m(2, 2) = c;
            m(0, 2) = -s;
            m(2, 0) = s;
            break;
        case AXIS::Z:
            m(2, 2) = 1;
            m(0, 0) = m(1, 1) = c;
            m(0, 1) = s;
            m(1, 0) = -s;
            break;
        }
        return m;
    }

    static Matrix2<T, 4, 4>translate(const T& dx, const T& dy, const T& dz)
    {
        auto m = Matrix2<T, 4, 4>::identity();
        m(3, 0) = dx;
        m(3, 1) = dy;
        m(3, 2) = dz;
        return m;
    }
};

