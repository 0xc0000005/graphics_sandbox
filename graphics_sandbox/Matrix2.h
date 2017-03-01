#pragma once

#include <memory>
#include <iterator>
#include <sstream>

template<typename T>
class Matrix2
{
public:
    Matrix2(size_t rs, size_t cs) : r(rs), c(cs), data(std::make_unique<T[]>(rs * cs)) { std::fill_n(data.get(), total(), 0); }

    Matrix2(const Matrix2& m) : r(m.r), c(m.c), transposed(m.transposed), data(std::make_unique<T[]>(m.total())) {
        std::copy(m.data.get(), m.data.get() + m.total(), stdext::checked_array_iterator<T*>(data.get(), m.total()));
    }

    Matrix2(Matrix2&& m) : r(m.r), c(m.c), transposed(m.transposed), data(std::move(m.data)) {}

    Matrix2(std::initializer_list<std::initializer_list<T>> l) : r(l.size()), c(l.begin() != l.end() ? l.begin()->size() : 0)
    {
        data = std::make_unique<T[]>(r * c);
        int i = 0, t = total();
        for (auto lr = l.begin(); lr != l.end(); ++lr) {
            for (auto lc = lr->begin(); lc != lr->end(); ++lc) {
                if (i >= t) throw std::invalid_argument("Too many arguments");
                data.get()[i++] = *lc;
            }
        }
        if (i != t) throw std::invalid_argument("Not enough arguments");
    }

    T& operator()(size_t i, size_t j) { return get(i, j); }

    Matrix2 operator*(Matrix2& rhs) const
    {
        if (cols() != rhs.rows())
            throw std::invalid_argument("Matrices sizes does not match multiplication criteria");

        Matrix2 m(rows(), rhs.cols());

        for (size_t i = 0; i < rows(); ++i)
            for (size_t j = 0; j < m.cols(); ++j) {
                T val = 0;
                for (size_t k = 0; k < cols(); ++k)
                    val += get(i, k) * rhs.get(k, j);
                m(i, j) = val;
            }
        return m;
    }

    size_t rows() const { return transposed ? c : r; }
    size_t cols() const { return transposed ? r : c; }

    std::string to_string()
    {
        std::stringstream ss;
        for (size_t i = 0; i < rows(); ++i) {
            for (size_t j = 0; j < cols(); ++j)
                ss << get(i, j) << " ";
            ss << std::endl;
        }
        return ss.str();
    }

    void transpose() { transposed = !transposed; }

private:
    bool transposed = false;
    const size_t r;
    const size_t c;
    std::unique_ptr<T[]> data;

    size_t total() const { return r * c; }
    size_t index(size_t i, size_t j) const { return transposed ? (i + j * c) : (i * c + j); }
    T& get(size_t i, size_t j) const { return data.get()[index(i, j)]; }
};
