#pragma once
#include <cmath>
#include <memory>
#include <iterator>
#include <sstream>
#include <array>

#include "Matrix2.h"

template<
    typename T, size_t N,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class Vec
{
public:
    Vec() : Vec(0) {}

    Vec(const T& x) { data.fill(0); }

    Vec(std::initializer_list<T> l)
    {
        auto i = l.begin();
        for (size_t n = 0; n < N; ++n)
            data[n] = i != l.end() ? *i++ : 0;
    }

    Vec(const Vec& v) : data(v.data) {}

    Vec(Vec&& v) : data(std::move(v.data)) {}

    template<
        typename T, size_t NN,
        typename = typename std::enable_if<N == NN, T>::type>
    T dot(const Vec<T, NN>& v) const
    {
        T result = 0;
        for (size_t i = 0; i < size(); ++i)
            result += data[i] * v.data[i];
        return result;
    }

    double length() { return sqrt(static_cast<double>(dot(*this))); }

    template<typename T, size_t NN>
    Vec<typename std::enable_if<N == NN && NN == 3, T>::type, N>
    cross(const Vec<T, NN>& v) const
    {
        const T& x = data[0];
        const T& y = data[1];
        const T& z = data[2];
        const T& vx = v.data[0];
        const T& vy = v.data[1];
        const T& vz = v.data[2];
        return Vec{ y * vz - z * vy, z * vx - x * vz, x * vy - y * vx };
    }

    Vec& normalize() {
        const double invert_len = 1 / length();
        for (size_t i = 0; i < size(); ++i)
            data[i] = static_cast<T>(data[i] * invert_len);
        return *this;
    }

    T& operator()(size_t i) { return data.at(i); }

    const T& operator()(size_t i) const { return data.at(i); }

    template<typename T, size_t NN>
    Vec<typename std::enable_if<N == NN, T>::type, N>
    mult(const Vec< T, NN>& v) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] * v.data[i];
        return result;
    }

    template<typename T, size_t NN>
    Vec<typename std::enable_if<N == NN, T>::type, N>
    div(const Vec< T, NN>& v) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] / v.data[i];
        return result;
    }

    template<typename T, size_t NN>
    Vec<typename std::enable_if<N == NN, T>::type, N>
    operator+ (const Vec<T, NN>& v) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] + v.data[i];
        return result;
    }

    template<typename T, size_t NN>
    Vec<typename std::enable_if<N == NN, T>::type, N>
    operator- (const Vec<T, NN>& v) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] - v(i);
        return result;
    }

    Vec operator* (const T& x) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] * x;
        return result;
    }

    Vec operator/ (const T& x) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] / x;
        return result;
    }

    template<typename T, size_t NN,
        typename = typename std::enable_if<N == NN, T>::type>
    bool operator==(const Vec<T, NN>& v) const
    {
        if (this == &v)
            return true;
        for (int i = 0; i < N; ++i)
            if (data[i] != v(i))
                return false;
        return true;
    }

    template<typename T, size_t NN,
        typename = typename std::enable_if<N == NN, T>::type>
        bool operator!=(const Vec<T, NN>& v) const
    {
        return !(*this == v);
    }

    std::string to_string() const
    {
        std::stringstream ss;
        for (size_t i = 0; i < size(); ++i)
            ss << data[i] << (i < size() - 1 ? " " : "");
        return ss.str();
    }

    Matrix2<T, 1, N> to_matrix() const
    {
        Matrix2<T, 1, N> m;
        for (size_t i = 0; i < size(); ++i)
            m(0, i) = data[i];
        return m;

    }

    Matrix2<T, N, 1> to_matrix_tr() const // transposed version
    {
        Matrix2<T, N, 1> m;
        for (size_t i = 0; i < size(); ++i)
            m(i, 0) = data[i];
        return m;

    }

    const size_t size() const { return data.size(); }

private:

    std::array<T, N> data;
};

template<typename T, size_t R, size_t C>
Matrix2<T, 1, C> operator*(const Matrix2<T, R, C>& m, const Vec<int, C>& v)
{
    return (m * v.to_matrix());
}

template<typename T, size_t R, size_t C>
Matrix2<T, 1, C> operator*(const Vec<int, C>& v, const Matrix2<T, R, C>& m)
{
    return (v.to_matrix() * m);
}




template<typename T, size_t N>
class Point : public Vec<T, N>
{
public:
    using Vec<T, N>::Vec;
};

template<typename T, size_t N>
class Vector : public Vec<T, N>
{
public:
    using Vec<T, N>::Vec;
};
