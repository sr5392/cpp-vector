#include "vector.h"
#include <utility>
#include <algorithm>


Vector::Vector() : m_size{0}, m_capacity{m_size}, m_data{nullptr} {}

Vector::Vector(const std::size_t size) : m_size {size}, m_capacity{m_size}, m_data{new int[m_capacity]} {
    for (std::size_t i = 0; i < m_size; ++i) {
        m_data[i] = 0;
    }
}

Vector::Vector(const std::initializer_list<int> init) :
m_size{init.size()},
m_capacity{m_size},
m_data{new int[m_capacity]} {
    std::copy(init.begin(), init.end(), m_data);
}

Vector::Vector(const Vector& other) :
m_size{other.m_size},
m_capacity{other.m_capacity},
m_data{new int[m_size]} {
    std::copy(other.m_data, other.m_data + m_size, m_data);
}

Vector& Vector::operator=(const Vector &other) {
    if (this == &other) return *this;

    if (m_capacity < other.m_capacity) {
        Vector tmp{other};
        swap(tmp);
    } else {
        m_size = other.m_size;
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }

    return *this;
}

Vector::Vector(Vector&& other) noexcept :
m_size{0},
m_capacity{0},
m_data{nullptr} {
    swap(other);
}


Vector& Vector::operator=(Vector&& other) noexcept {
    if (this == &other) return *this;
    swap(other);

    return *this;
}

Vector::~Vector() {
    delete[] m_data;
}

void Vector::reserve(const std::size_t capacity) {
    if (capacity <= m_capacity) return;

    int* data = new int[capacity];
    std::copy(m_data, m_data + m_size, data);
    delete[] m_data;
    m_data = data;
    m_capacity = capacity;
}

void Vector::resize(const std::size_t size) {
    reserve(size);
    for (std::size_t i = m_size; i < size; ++i) {
        m_data[i] = 0;
    }
    m_size = size;
}

void Vector::push_back(const int i) {
    if (m_capacity == 0) reserve(1);
    if (m_size == m_capacity) reserve(m_capacity * 2);

    m_data[m_size] = i;
    ++m_size;
}

int& Vector::operator[](const std::size_t i) {
    return m_data[i];
}

const int& Vector::operator[](const std::size_t i) const {
    return m_data[i];
}

[[nodiscard]] std::size_t Vector::size() const {
    return m_size;
}

[[nodiscard]] std::size_t Vector::capacity() const {
    return m_capacity;
}

void Vector::swap(Vector &other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
}

void swap(Vector& a, Vector& b) noexcept {
    a.swap(b);
}
