// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// graphics_sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Vec.h"
#include "Matrix2.h"

typedef double VecT;
typedef Vec<VecT, 3> Vec_t;

typedef Point<VecT, 3> Point_t;
typedef Vector<VecT, 3> Vector_t;
typedef Matrix2<VecT, 3, 4> Matrix_t;

int main()
{
    Vec<float, 3> v1 = { 2, 3, 4 };
    auto f = v1.normalize().length();

    //select_type<true, double, int>::type vvv;
    //vvv = 0;

    //select_type<false, double, int>::type fff;
    //fff = 0;

    //Vec_t v1{ 3.0, 3.0, 0 };
    //Vec_t v2{ 4.0, 1.0 };
    //Vec<VecT, 3> vv5{ 4.0, 1.0, 0, 9.9 };
    //Vec<int, 3> vv4;
    //v1 + v2;
    //v1 * 3;
    ////v1 + vv5;

    //VecT scal_proj1 = v1.dot(vv5) / v2.length();
    //Vec_t v3 = v2;
    //v3.normalize();
    //VecT scal_proj2 = v1.dot(v3);

    //Vec_t vc = v1.cross(v2);

    //Point_t p1{ 0 };
    //Vector_t v;

    //Matrix_t m;
    //for (size_t c = 0, i = 0; i < m.rows(); ++i)
    //    for (size_t j = 0; j < m.cols(); ++j)
    //        m(i, j) = ++c;
    //Matrix_t m2 = m;

    //Matrix2<VecT, 2, 3> mm1 = { {3.0, -2.0, 5.0}, {3.0, 0.0, 4.0} };
    //Matrix2<VecT, 3, 2> mm2 = { { 2.0, 3.0}, {-9.0, 0 } };


    //std::cout << mm1.to_string() << std::endl << mm2.to_string() << std::endl;

    //auto mm1t = mm1.transpose();
    //auto mm2t = mm2.transpose();

    //std::cout << mm1t.to_string() << std::endl << mm2t.to_string() << std::endl;

    //auto mm = mm1 * mm2;
    //std::cout << mm.to_string() << std::endl;
    //auto mmt = mm.transpose();
    //std::cout << mmt.to_string() << std::endl;

    //auto identity = Matrix2<int, 5>::identity();
    //std::cout << identity.to_string() << std::endl;

    //Vec<int, 5> vv{ 1, 2, 3, 4, 5 };
    //Matrix2<int, 1, 5> vvm = vv.to_matrix();
    //std::cout << vvm.to_string() << std::endl << (vv * identity).to_string();

    return 0;
}