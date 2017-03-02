#pragma once

#include <memory>
#include <iterator>
#include <sstream>

template<
    typename T, size_t R, size_t C=R,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Matrix2
{
public:
    Matrix2() { data.fill(0); }

    Matrix2(const Matrix2& m) : data(m.data) {}

    Matrix2(Matrix2&& m) : data(std::move(m.data)) {}

    Matrix2(std::initializer_list<std::initializer_list<T>> l)
    {
        auto r = l.begin();
        size_t n = 0;
        for (size_t i = 0; i < R; ++i) {
            if (r != l.end()) {
                auto c = r->begin();
                for (size_t j = 0; j < C; ++j)
                    data[n++] = c != r->end() ? *c++ : 0;
                ++r;
            }
            else {
                for (size_t j = 0; j < C; ++j)
                    data[n++] = 0;
            }
        }
    }

    T& operator()(size_t i, size_t j) { return data.at(index(i, j)); }

    const T& operator()(size_t i, size_t j) const { return data.at(index(i, j)); }

    template<typename T, size_t RR, size_t CC,
        typename = typename std::enable_if<R == RR && C == CC, T>::type>
        bool operator==(const Matrix2<T, RR, CC>& m) const
    {
        if (this == &m)
            return true;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (data[index(i, j)] != m(i, j))
                    return false;
        return true;
    }

    template<typename T, size_t RR, size_t CC,
        typename = typename std::enable_if<R == RR && C == CC, T>::type>
        bool operator!=(const Matrix2<T, RR, CC>& m) const
    {
        return !(*this == m);
    }

    template<typename T, size_t RR, size_t CC>
    Matrix2<typename std::enable_if<C == RR, T>::type, R, CC>
    operator*(const Matrix2<T, RR, CC>& rhs) const
    {
        Matrix2<T, R, CC> m;

        for (size_t i = 0; i < rows(); ++i)
            for (size_t j = 0; j < m.cols(); ++j) {
                T val = 0;
                for (size_t k = 0; k < cols(); ++k)
                    val += data[index(i, k)] * rhs(k, j);
                m(i, j) = val;
            }
        return m;
    }

    static Matrix2 identity()
    {
        Matrix2<T, R, R> m;
        for (size_t i = 0; i < R; ++i)
            m(i, i) = 1;
        return m;
    }

    size_t rows() const { return R; }
    size_t cols() const { return C; }

    std::string to_string() const
    {
        std::stringstream ss;
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j)
                ss << data[index(i, j)] << (j < cols() - 1 ? " " : "");
            ss << std::endl;
        }
        return ss.str();
    }

    Matrix2<T, C, R> transpose()
    {
        Matrix2<T, C, R> m;
        for (size_t i = 0; i < R; ++i)
            for (size_t j = 0; j < C; ++j)
                m(j, i) = data[index(i, j)];
        return m;
    }

private:
    std::array<T, R*C> data;

    size_t total() const { return R * C; }
    size_t index(size_t i, size_t j) const { return (i * C + j); }
};

