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