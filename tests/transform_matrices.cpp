#include <iostream>
#include <gtest/gtest.h>

#include "TransformationMatrix.h"

const double pi = std::acos(-1.0); // pi constant calculated
const double pi_2 = pi / 2.0;
const double eps = 1e-5;
const double angle = pi_2 / 2.0;

typedef TransformationMatrix<double> TMatrix_t;

TEST(test_transformation_matrix, scale)
{
    auto m = TMatrix_t::scale(0.5, 0.5, 0.5);
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            ASSERT_EQ(m(i, j), (i == j && j < 3 ? 0.5 : 0.0));
}

TEST(test_transformation_matrix, x_rotation)
{
    auto m = TMatrix_t::rotate(angle, TMatrix_t::AXIS::X);
    const double s = std::sin(angle);
    const double c = std::cos(angle);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j) {
            if (i == 0 && j == 0) ASSERT_EQ(m(i, j), 1.0);              // X basis
            else if (i == 1 && j == 2) ASSERT_NEAR(m(i, j), s, eps)  << "m(" << i << " " << j << ")";
            else if (i == 2 && j == 1) ASSERT_NEAR(m(i, j), -s, eps) << "m(" << i << " " << j << ")";
            else if (i == 1 && j == 1) ASSERT_NEAR(m(i, j), c, eps)  << "m(" << i << " " << j << ")";
            else if (i == 2 && j == 2) ASSERT_NEAR(m(i, j), c, eps)  << "m(" << i << " " << j << ")";
            else ASSERT_EQ(m(i, j), 0.0);
        }
}

TEST(test_transformation_matrix, y_rotation)
{
    auto m = TMatrix_t::rotate(angle, TMatrix_t::AXIS::Y);
    const double s = std::sin(angle);
    const double c = std::cos(angle);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j) {
            if (i == 1 && j == 1) ASSERT_EQ(m(i, j), 1.0);              // Y basis
            else if (i == 2 && j == 0) ASSERT_NEAR(m(i, j), s, eps)  << "m(" << i << " " << j << ")";
            else if (i == 0 && j == 2) ASSERT_NEAR(m(i, j), -s, eps) << "m(" << i << " " << j << ")";
            else if (i == 0 && j == 0) ASSERT_NEAR(m(i, j), c, eps)  << "m(" << i << " " << j << ")";
            else if (i == 2 && j == 2) ASSERT_NEAR(m(i, j), c, eps)  << "m(" << i << " " << j << ")";
            else ASSERT_EQ(m(i, j), 0.0);
        }
}

TEST(test_transformation_matrix, z_rotation)
{
    auto m = TMatrix_t::rotate(angle, TMatrix_t::AXIS::Z);
    const double s = std::sin(angle);
    const double c = std::cos(angle);

    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j) {
            if (i == 2 && j == 2) ASSERT_EQ(m(i, j), 1.0);              // Z basis
            else if (i == 0 && j == 1) ASSERT_NEAR(m(i, j), s, eps)  << "m(" << i << " " << j << ")";
            else if (i == 1 && j == 0) ASSERT_NEAR(m(i, j), -s, eps) << "m(" << i << " " << j << ")";
            else if (i == 1 && j == 1) ASSERT_NEAR(m(i, j), c, eps)  << "m(" << i << " " << j << ")";
            else if (i == 0 && j == 0) ASSERT_NEAR(m(i, j), c, eps)  << "m(" << i << " " << j << ")";
            else ASSERT_EQ(m(i, j), 0.0);
        }
}
