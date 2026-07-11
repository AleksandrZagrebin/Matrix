#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <numeric>


template<typename T>
class Matrix
{
    static_assert(std::is_arithmetic_v<T>,
        "Matrix can only be instantiated with arithmetic types");
    T* m_buffer;
    size_t m_rows;
    size_t m_cols;

    struct ProxyRow
    {
        T* row;
        size_t cols;

        const T& operator[](size_t n) const
        {
            if (n >= cols)
                throw std::out_of_range("ProxyRow::operator[]: column index out of range");
            return row[n];
        }

        T& operator[](size_t n)
        {
            if (n >= cols) {
                throw std::out_of_range("ProxyRow::operator[]: column index out of range");
            }
            return row[n];
        }
    };

public:
    Matrix(size_t rows, size_t cols, T val = T{});
    template<typename It>
    Matrix(size_t rows, size_t cols, It begin, It end);
    Matrix(size_t rows, size_t cols, std::initializer_list<T> list);
    Matrix(std::istream& is, size_t rows, size_t cols);
    static Matrix eye(size_t n, size_t m);
    static Matrix eye(size_t n);

    Matrix(const Matrix& rhs);
    Matrix(Matrix&& rhs) noexcept;

    Matrix& operator=(const Matrix& rhs);
    Matrix& operator=(Matrix&& rhs) noexcept;

    ~Matrix();

    size_t nrows() const { return m_rows; }
    size_t ncols() const { return m_cols; }

    T trace() const;
    bool equal(const Matrix& other) const;
    bool less(const Matrix& other) const;
    void dump(std::ostream& os) const;

    Matrix& negate()&;
    Matrix& transpose()&;

    ProxyRow operator[](size_t n) {
        if (n >= m_rows)
            throw std::out_of_range("Matrix::operator[]: row index out of range");
        return ProxyRow{ m_buffer + n * m_cols, m_cols };
    }

    const ProxyRow operator[](size_t n) const {
        if (n >= m_rows)
            throw std::out_of_range("Matrix::operator[]: row index out of range");
        return ProxyRow{ m_buffer + n * m_cols, m_cols };
    }

    Matrix multiply(const Matrix& other) const;
    Matrix add(const Matrix& other) const;
    Matrix scalar_multiply(const T& scalar) const;
    Matrix& multiply_assign(const Matrix& other);
    Matrix& add_assign(const Matrix& other);
    Matrix& scalar_multiply_assign(const T& scalar);

    T determinant() const;
    void swap_rows(size_t row1, size_t row2);

public:
    class const_iterator;
    class iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
};

#include "matrix_impl.hpp"


