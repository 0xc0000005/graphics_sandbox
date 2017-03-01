#pragma once
#include <cmath>
#include <memory>
#include <iterator>
#include <sstream>
#include <array>

#include "Matrix2.h"

template<typename T, size_t N>
class Vec
{
public:
    Vec() : Vec(0) {}
    
    Vec(const T& x) { data.fill(0); }
    
    Vec(std::initializer_list<T> l)
    {
        size_t n = 0;
        for (auto i = l.begin(); i != l.end() && n < size(); ++i, ++n)
            data[n] = *i;
    }
    
    Vec(const Vec& v) : data(v.data) {}

    Vec(Vec&& v) : data(std::move(v.data)) {}

    template<typename TT, size_t NN>
    T dot(const Vec<TT, NN>& v, Vec<typename std::enable_if<N == NN, T>::type, N>* = nullptr) const
    {
        T result = 0;
        for (size_t i = 0; i < size(); ++i)
            result += data[i] * v.data[i];
        return result;
    }
    
    T length() { return sqrt(dot(*this)); }

    template<typename TT, size_t NN>
    Vec<typename std::enable_if<N == NN && NN == 3, T>::type, N>
    cross(const Vec<TT, NN>& v) const
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
        const T invert_len = 1 / length();
        for (size_t i = 0; i < size(); ++i)
            data[i] *= invert_len;
        return *this;
    }

    T& operator()(size_t i) { return data.at(i); }

    template<typename TT, size_t NN>
    Vec<typename std::enable_if<N == NN, T>::type, N>
    operator+ (const Vec<TT, NN>& v) const
    {
        Vec<T, N> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] + v.data[i];
        return result;
    }

    template<typename TT, size_t NN>
    Vec<typename std::enable_if<N == NN, T>::type, N>
    operator- (const Vec &v) const
    {
        Vec<T, size> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] - v(i);
        return result;
    }

    Vec operator* (const T& x) const
    {
        Vec<T, size()> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] * x;
        return result;
    }

    Vec operator/ (const T& x) const
    {
        Vec<T, size()> result;
        for (size_t i = 0; i < size(); ++i)
            result(i) = data[i] / x;
        return result;
    }

    std::string to_string() const
    {
        std::stringstream ss;
        for (size_t i = 0; i < size(); ++i)
            ss << data[i] << " ";
        return ss.str();
    }

    operator Matrix2<T>() const
    {
        Matrix2<T> m(1, size());
        for (size_t i = 0; i < size(); ++i)
            m(0, i) = data[i];
        return m;
    }

    const size_t size() const { return data.size(); }

private:

    std::array<T, N> data;
};

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

template<typename T, size_t N>
Matrix2<T> operator*(const Matrix2<T>& m, const Vec<int, N>& v)
{
    return (m * static_cast<Matrix2<T>>(v));
}

template<typename T, size_t N>
Matrix2<T> operator*(const Vec<int, N>& v, const Matrix2<T>& m)
{
    return (static_cast<Matrix2<T>>(v) * m);
}
