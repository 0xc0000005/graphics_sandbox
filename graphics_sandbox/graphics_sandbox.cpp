// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

// graphics_sandbox.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Vec.h"
#include "TransformationMatrix.h"

const double pi = std::acos(-1.0); // pi constant calculated
inline double d2r(double degree) { return degree * pi / 180.0; } // degrees to radians

int main()
{
    auto m = TransformationMatrix<double>::translate(0.5, 0.6, 0.7);
    std::cout << m.to_string() << std::endl;

    return 0;
}