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