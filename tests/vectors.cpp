#include <iostream>
#include <gtest/gtest.h>

#include "Vec.h"

template<typename T, size_t N>
::std::ostream& operator<<(::std::ostream& os, const Vec<T, N>& v)
{
    return os << "Vec(" << v.to_string() << ")";
}

TEST(test_vect_creation, def_values)
{
    Vec<float, 3> v;
    ASSERT_EQ(v(0), 0) << "Get 1st value (0 by default)";
    ASSERT_EQ(v(1), 0) << "Get 2nd value (0 by default)";
    ASSERT_EQ(v(2), 0) << "Get 3rd value (0 by default)";
    ASSERT_THROW(v(3), std::out_of_range) << "Get non-existing value";
}

TEST(test_vect_creation, def_specific_values)
{
    Vec<float, 3> v(3.5);
    ASSERT_EQ(v(0), 3.5) << "Get 1st value (0 by default)";
    ASSERT_EQ(v(1), 3.5) << "Get 2nd value (0 by default)";
    ASSERT_EQ(v(2), 3.5) << "Get 3rd value (0 by default)";
    ASSERT_THROW(v(3), std::out_of_range) << "Get non-existing value";
}

TEST(test_vect_creation, create_with_long_init_list)
{
    Vec<int, 3> v = { 1, 2, 3, 4 };
    ASSERT_EQ(v(0), 1) << "Get 1st value (1)";
    ASSERT_EQ(v(1), 2) << "Get 2nd value (2)";
    ASSERT_EQ(v(2), 3) << "Get 3rd value (3)";
    ASSERT_THROW(v(3), std::out_of_range) << "Get non-existing value";
}

TEST(test_vect_creation, create_with_short_init_list)
{
    Vec<int, 3> v = { 1, 2 };
    ASSERT_EQ(v(0), 1) << "Get 1st value (1)";
    ASSERT_EQ(v(1), 2) << "Get 2nd value (2)";
    ASSERT_EQ(v(2), 0) << "Get 3rd value (0 by default)";
    ASSERT_THROW(v(3), std::out_of_range) << "Get non-existing value";
}

TEST(test_vect_creation, copy_constuctor)
{
    Vec<int, 3> v = { 1, 2, 3, 4 };
    auto v2 = v;
    ASSERT_EQ(v2(0), 1) << "Get 1st value (1)";
    ASSERT_EQ(v2(1), 2) << "Get 2nd value (2)";
    ASSERT_EQ(v2(2), 3) << "Get 3rd value (3)";
    ASSERT_THROW(v2(3), std::out_of_range) << "Get non-existing value";
}

TEST(test_vect_operations, comparation)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v2 = { 3, 5, 6 };
    Vec<int, 3> v3 = { 3, 5, 6 };
    ASSERT_NE(v1, v2);
    ASSERT_EQ(v2, v3);
    ASSERT_EQ(v1, v1);
}

TEST(test_vect_operations, arithmetic_add)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v2 = { 3, 5, 6 };
    ASSERT_EQ(v1 + v2, (Vec<int, 3>{5, 8, 10}));
}

TEST(test_vect_operations, arithmetic_sub)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v2 = { 3, 5, 6 };
    ASSERT_EQ(v2 - v1, (Vec<int, 3>{1, 2, 2}));
}

TEST(test_vect_operations, arithmetic_mul_by_const)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    ASSERT_EQ(v1 * 2, (Vec<int, 3>{4, 6, 8}));
}

TEST(test_vect_operations, arithmetic_div_by_const)
{
    Vec<int, 3> v3 = { 5, 8, 10 };
    ASSERT_EQ(v3 / 2, (Vec<int, 3>{2, 4, 5}));
}

TEST(test_vect_operations, arithmetic_element_wide_mult)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v2 = { 3, 5, 6 };
    ASSERT_EQ(v1.mult(v2), (Vec<int, 3>{6, 15, 24}));
}

TEST(test_vect_operations, arithmetic_element_wide_div)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v3 = { 5, 8, 10 };
    ASSERT_EQ(v3.div(v1), (Vec<int, 3>{2, 2, 2}));
}

TEST(test_vect_operations, length)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    ASSERT_NEAR(v1.length(), 5.3852, 0.0001);
}

TEST(test_vect_operations, dot_product)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v2 = { 3, 5, 6 };

    ASSERT_EQ(v1.dot(v2), 45);
}

TEST(test_vect_operations, cross_product)
{
    Vec<int, 3> v1 = { 2, 3, 4 };
    Vec<int, 3> v2 = { 3, 5, 6 };
    ASSERT_EQ(v1.cross(v2), (Vec<int, 3>{-2, 0, 1}));
}

TEST(test_vect_operations, normalize)
{
    Vec<float, 3> v1 = { 2.0, 3.0, 4.0 };
    ASSERT_NEAR(v1.normalize().length(), 1.0, 0.0001);
}

TEST(test_vect_operations, vect_to_matrix)
{
    Vec<int, 4> v1 = { 1, 2, 3, 4 };
    auto m1 = v1.to_matrix_row();
    ASSERT_EQ(m1, (Matrix2<int, 1, 4>{ {1, 2, 3, 4} }));
}

TEST(test_vect_operations, vect_to_matrix_transposed)
{
    Vec<int, 4> v1 = { 1, 2, 3, 4 };
    auto m1 = v1.to_matrix_col();
    ASSERT_EQ(m1, (Matrix2<int, 4, 1>{ { 1 }, { 2 }, { 3 }, { 4 } }));
}
