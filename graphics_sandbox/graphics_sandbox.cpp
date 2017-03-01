// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// graphics_sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Vec3.h"
#include "Matrix2.h"

typedef double VecT;
typedef Vec3<VecT> Vec_t;

typedef Point<VecT> Point_t;
typedef Vector<VecT> Vector_t;

int main()
{
    Vec_t v1{ 3.0, 3.0, 0 };
    Vec_t v2{ 4.0, 1.0, 0 };

    VecT scal_proj1 = v1.dot(v2) / v2.length();
    Vec_t v3 = v2;
    v3.normalize();
    VecT scal_proj2 = v1.dot(v3);

    Vec_t vc = v1.cross(v2);

    Point_t p1{ 0 };
    Vector_t v;

    Matrix2<VecT> m(3, 4);
    for (size_t c = 0, i = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            m(i, j) = ++c;
    Matrix2<VecT> m2 = m;

    Matrix2<VecT> mm1 = { {3.0, -2.0, 5.0}, {3.0, 0.0, 4.0} };
    Matrix2<VecT> mm2 = { { 2.0, 3.0}, {-9.0, 0 }, { 0.0, 4.0 } };

    std::cout << mm1.to_string() << std::endl << mm2.to_string() << std::endl;

    mm1.transpose();
    mm2.transpose();

    std::cout << mm1.to_string() << std::endl << mm2.to_string() << std::endl;

    Matrix2<VecT> mm = mm1 * mm2;
    std::cout << mm.to_string() << std::endl;
    mm.transpose();
    std::cout << mm.to_string() << std::endl;

    return 0;
}

