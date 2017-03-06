#include <iostream>
#include <gtest/gtest.h>

#include "Matrix2.h"

template<typename T, size_t R, size_t C>
::std::ostream& operator<<(::std::ostream& os, const Matrix2<T, R, C>& m)
{
    return os << "Matrix(" << m.to_string() << ")";
}

TEST(test_matrix_creation, def_values)
{
    Matrix2<int, 3, 3> m;
    for (size_t i = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            ASSERT_EQ(m(i, j), 0);

    ASSERT_THROW(m(4, 4), std::out_of_range) << "Get non-existing value";
}

TEST(test_matrix_creation, create_with_long_init_list)
{
    Matrix2<int, 2, 3> m = { { 1, 2, 3},{ 4, 5, 6 } };
    for (size_t i = 0, n = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            ASSERT_EQ(m(i, j), ++n);
    ASSERT_THROW(m(4, 4), std::out_of_range) << "Get non-existing value";
}

TEST(test_matrix_creation, create_with_short_init_list)
{
    Matrix2<int, 5, 3> m = { { 1, 2, 3 },{ 4, 5, 6 } };
    for (size_t i = 0, n = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            ASSERT_EQ(m(i, j), n < 6 ? ++n : 0);
    ASSERT_THROW(m(4, 4), std::out_of_range) << "Get non-existing value";
}

TEST(test_matrix_creation, copy_constuctor)
{
    Matrix2<int, 2, 3> mm = { { 1, 2, 3 },{ 4, 5, 6 } };
    auto m = mm;
    for (size_t i = 0, n = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            ASSERT_EQ(m(i, j), ++n);
    ASSERT_THROW(m(4, 4), std::out_of_range) << "Get non-existing value";
}

TEST(test_matrix_operations, comparation)
{
    Matrix2<int, 2, 3> m1 = { { 1, 2, 3 },{ 4, 5, 6 } };
    Matrix2<int, 2, 3> m2 = { { 6, 5, 4 },{ 3, 2, 1 } };
    Matrix2<int, 2, 3> m3 = { { 1, 2, 3 },{ 4, 5, 6 } };
    ASSERT_NE(m1, m2);
    ASSERT_EQ(m1, m3);
    ASSERT_EQ(m3, m3);
}

TEST(test_matrix_operations, identity_matrix)
{
    auto m = Matrix2<int, 5, 5>::identity();
    for (size_t i = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            ASSERT_EQ(m(i, j), i == j ? 1 : 0);
}

TEST(test_matrix_operations, transpose_matrix)
{
    Matrix2<int, 2, 3> m1 = { { 1, 3, 5 },{ 2, 4, 6 } };
    auto m = m1.transpose();
    for (size_t i = 0, n = 0; i < m.rows(); ++i)
        for (size_t j = 0; j < m.cols(); ++j)
            ASSERT_EQ(m(i, j), ++n);
}

TEST(test_matrix_operations, matrices_multiplication)
{
    Matrix2<int, 2, 3> m1 = { { 1, 2, 3 },{ 4, 5, 6 } };
    auto m2 = m1.transpose();
    auto m = m1 * m2;
    ASSERT_EQ(m.rows(), 2) << "rows in result matrix";
    ASSERT_EQ(m.cols(), 2) << "columns in result matrix";
    ASSERT_EQ(m(0, 0), 14);
    ASSERT_EQ(m(0, 1), 32);
    ASSERT_EQ(m(1, 0), 32);
    ASSERT_EQ(m(1, 1), 77);
}
