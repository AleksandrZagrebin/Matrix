#pragma once

#include "matrix.hpp"

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, T val)
    : m_rows(rows), m_cols(cols), m_buffer(new T[rows * cols])
{
    for (size_t i = 0; i < rows * cols; ++i)
        m_buffer[i] = val;
}

template<typename T>
template<typename It>
Matrix<T>::Matrix(size_t rows, size_t cols, It begin, It end)
    : m_rows(rows), m_cols(cols), m_buffer(new T[rows * cols])
{
    size_t total = rows * cols;
    size_t count = 0;
    for (It it = begin; it != end && count < total; ++it, ++count)
        m_buffer[count] = *it;
    if (count < total) {
        for (size_t i = count; i < total; ++i)
            m_buffer[i] = T{};
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, std::initializer_list<T> list)
    : Matrix(rows, cols, list.begin(), list.end()) {
}

template<typename T>
Matrix<T>::Matrix(std::istream& is, size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols), m_buffer(new T[rows * cols])
{
    size_t total = rows * cols;
    for (size_t i = 0; i < total; ++i) {
        if (!(is >> m_buffer[i])) {
            throw std::runtime_error("Failed to read matrix data from stream");
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::eye(size_t n, size_t m)
{
    Matrix result(n, m, T{ 0 });
    size_t min_dim = (n < m) ? n : m;
    for (size_t i = 0; i < min_dim; ++i) {
        result[i][i] = T(1);
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::eye(size_t n) {
    return eye(n, n);
}

template<typename T>
Matrix<T>::Matrix(const Matrix& rhs)
    : m_rows(rhs.m_rows), m_cols(rhs.m_cols), m_buffer(new T[rhs.m_rows * rhs.m_cols])
{
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i)
        m_buffer[i] = rhs.m_buffer[i];
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] m_buffer;
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;
    m_buffer = new T[m_rows * m_cols];
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i) {
        m_buffer[i] = rhs.m_buffer[i];
    }
    return *this;
}

template<typename T>
Matrix<T>::Matrix(Matrix&& rhs) noexcept
    : m_buffer(rhs.m_buffer), m_rows(rhs.m_rows), m_cols(rhs.m_cols)
{
    rhs.m_buffer = nullptr;
    rhs.m_rows = 0;
    rhs.m_cols = 0;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) noexcept
{
    if (this == &rhs)
        return *this;
    delete[] m_buffer;
    m_buffer = rhs.m_buffer;
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;
    rhs.m_buffer = nullptr;
    rhs.m_rows = 0;
    rhs.m_cols = 0;
    return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] m_buffer;
}

template<typename T>
T Matrix<T>::trace() const
{
    if (m_rows != m_cols)
        throw std::invalid_argument("Trace: matrix must be square");
    T sum = T(0);
    for (size_t i = 0; i < m_rows; ++i)
        sum += m_buffer[i * m_cols + i];
    return sum;
}

template<typename T>
bool Matrix<T>::equal(const Matrix& other) const
{
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        return false;
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i) {
        if (m_buffer[i] != other.m_buffer[i])
            return false;
    }
    return true;
}

template<typename T>
bool Matrix<T>::less(const Matrix& other) const
{
    if (m_rows != other.m_rows)
        return m_rows < other.m_rows;
    if (m_cols != other.m_cols)
        return m_cols < other.m_cols;
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i) {
        if (m_buffer[i] != other.m_buffer[i])
            return m_buffer[i] < other.m_buffer[i];
    }
    return false;
}

template<typename T>
void Matrix<T>::dump(std::ostream& os) const {
    for (size_t i = 0; i < m_rows; ++i) {
        os << "[";
        for (size_t j = 0; j < m_cols; ++j) {
            os << m_buffer[i * m_cols + j];
            if (j + 1 < m_cols) {
                os << ", ";
            }
        }
        os << "]\n";
    }
}

template<typename T>
Matrix<T>& Matrix<T>::negate()& {
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i) {
        m_buffer[i] = -m_buffer[i];
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::transpose()&
{
    Matrix temp(m_cols, m_rows);
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_cols; ++j)
            temp[j][i] = (*this)[i][j];
    }
    *this = std::move(temp);
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& other) const
{
    if (m_cols != other.m_rows)
        throw std::invalid_argument("Matrix multiplication: incompatible sizes");
    Matrix result(m_rows, other.m_cols, T(0));
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t k = 0; k < m_cols; ++k) {
            T aik = (*this)[i][k];
            for (size_t j = 0; j < other.m_cols; ++j) {
                result[i][j] += aik * other[k][j];
            }
        }
    }
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::multiply_assign(const Matrix& other)
{
    *this = multiply(other);
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::scalar_multiply(const T& scalar) const
{
    Matrix result(m_rows, m_cols);
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i)
        result.m_buffer[i] = m_buffer[i] * scalar;
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::scalar_multiply_assign(const T& scalar)
{
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i)
        m_buffer[i] *= scalar;
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::add(const Matrix& other) const
{
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        throw std::invalid_argument("Matrix addition: incompatible sizes");
    Matrix result(m_rows, m_cols);
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i)
        result.m_buffer[i] = m_buffer[i] + other.m_buffer[i];
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::add_assign(const Matrix& other)
{
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        throw std::invalid_argument("Matrix addition: incompatible sizes");
    size_t total = m_rows * m_cols;
    for (size_t i = 0; i < total; ++i)
        m_buffer[i] += other.m_buffer[i];
    return *this;
}

template<typename T>
T Matrix<T>::determinant() const
{
    if (m_rows != m_cols)
        throw std::invalid_argument("Determinant: matrix must be square");
    size_t n = m_rows;
    if (n == 1) return m_buffer[0];
    if (n == 2) return m_buffer[0] * m_buffer[3] - m_buffer[1] * m_buffer[2];
    Matrix temp = *this;
    T det = T(1);
    for (size_t col = 0; col < n; ++col) {
        size_t pivot = col;
        for (size_t row = col + 1; row < n; ++row) {
            if (std::abs(temp[row][col]) > std::abs(temp[pivot][col]))
                pivot = row;
        }
        if (temp[pivot][col] == T(0))
            return T(0);
        if (pivot != col) {
            temp.swap_rows(col, pivot);
            det = -det;
        }
        for (size_t row = col + 1; row < n; ++row) {
            T factor = temp[row][col] / temp[col][col];
            for (size_t j = col + 1; j < n; ++j)
                temp[row][j] -= factor * temp[col][j];
        }
    }
    for (size_t i = 0; i < n; ++i)
        det *= temp[i][i];
    return det;
}

template<typename T>
void Matrix<T>::swap_rows(size_t row1, size_t row2)
{
    if (row1 >= m_rows || row2 >= m_rows)
        throw std::out_of_range("swap_rows: index out of range");
    if (row1 == row2) return;
    for (size_t j = 0; j < m_cols; ++j)
        std::swap((*this)[row1][j], (*this)[row2][j]);
}

template<typename T>
class Matrix<T>::const_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    const_iterator(T* ptr = nullptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() const { return m_ptr; }

    const_iterator& operator++() { ++m_ptr; return *this; }
    const_iterator operator++(int) { const_iterator tmp = *this; ++m_ptr; return tmp; }

    bool operator==(const const_iterator& other) const { return m_ptr == other.m_ptr; }
    bool operator!=(const const_iterator& other) const { return m_ptr != other.m_ptr; }

protected:
    T* m_ptr;
};

template<typename T>
class Matrix<T>::iterator : public Matrix<T>::const_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator(T* ptr = nullptr) : const_iterator(ptr) {}

    reference operator*() const { return *this->m_ptr; }
    pointer operator->() const { return this->m_ptr; }

    iterator& operator++() { ++this->m_ptr; return *this; }
    iterator operator++(int) { iterator tmp = *this; ++this->m_ptr; return tmp; }

    bool operator==(const iterator& other) const { return this->m_ptr == other.m_ptr; }
    bool operator!=(const iterator& other) const { return this->m_ptr != other.m_ptr; }
};

template<typename T>
typename Matrix<T>::iterator Matrix<T>::begin() {
    return iterator(m_buffer);
}

template<typename T>
typename Matrix<T>::iterator Matrix<T>::end() {
    return iterator(m_buffer + m_rows * m_cols);
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::begin() const {
    return const_iterator(m_buffer);
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::end() const {
    return const_iterator(m_buffer + m_rows * m_cols);
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::cbegin() const {
    return const_iterator(m_buffer);
}

template<typename T>
typename Matrix<T>::const_iterator Matrix<T>::cend() const {
    return const_iterator(m_buffer + m_rows * m_cols);
}

