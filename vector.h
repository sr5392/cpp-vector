#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>
#include <algorithm>

template<typename T, typename A = std::allocator<T> >
class Vector {
public:
    using size_type = std::size_t;

    Vector();

    explicit Vector(size_type size);

    Vector(std::initializer_list<T> init);

    Vector(const Vector &other);

    Vector &operator=(const Vector &other);

    Vector(Vector &&other) noexcept;

    Vector &operator=(Vector &&other) noexcept;

    ~Vector();

    void reserve(size_type capacity);

    void resize(size_type size);

    void push_back(int i);

    void shrink_to_fit();

    int &operator[](size_type i);

    const int &operator[](size_type i) const;

    [[nodiscard]] size_type size() const;

    [[nodiscard]] size_type capacity() const;

    void swap(Vector &other) noexcept;

    [[nodiscard]] int *begin();

    [[nodiscard]] const int *begin() const;

    [[nodiscard]] int *end();

    [[nodiscard]] const int *end() const;

private:
    size_type m_size;
    size_type m_capacity;
    A m_allocator;
    T *m_data;
};

template<typename T, typename A>
Vector<T, A>::Vector() : m_size{0}, m_capacity{m_size}, m_data{nullptr} {
}

template<typename T, typename A>
Vector<T, A>::Vector(const size_type size) : m_size{size}, m_capacity{m_size},
                                             m_data{m_allocator.allocate(m_capacity)} {
    for (size_type i = 0; i < m_size; ++i) {
        std::construct_at(m_data + i);
    }
}

template<typename T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> init) : m_size{init.size()},
                                                      m_capacity{m_size},
                                                      m_data{m_allocator.allocate(m_capacity)} {
    std::uninitialized_copy(init.begin(), init.end(), m_data);
}

template<typename T, typename A>
Vector<T, A>::Vector(const Vector &other) : m_size{other.m_size},
                                            m_capacity{other.m_capacity},
                                            m_allocator{other.m_allocator},
                                            m_data{m_allocator.allocate(m_capacity)} {
    std::uninitialized_copy(other.begin(), other.end(), m_data);
}

template<typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(const Vector &other) {
    if (this == &other) return *this;

    if (m_capacity < other.m_size) {
        Vector tmp{other};
        swap(tmp);
    } else {
        m_size = other.m_size;
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }

    return *this;
}

template<typename T, typename A>
Vector<T, A>::Vector(Vector &&other) noexcept : m_size{0},
                                                m_capacity{0},
                                                m_data{nullptr} {
    swap(other);
}

template<typename T, typename A>
Vector<T, A> &Vector<T, A>::operator=(Vector &&other) noexcept {
    if (this == &other) return *this;
    swap(other);

    return *this;
}

template<typename T, typename A>
Vector<T, A>::~Vector() {
    std::destroy(m_data, m_data + m_size);
    m_allocator.deallocate(m_data, m_capacity);
}

template<typename T, typename A>
void Vector<T, A>::reserve(const Vector<T, A>::size_type capacity) {
    if (capacity <= m_capacity) return;

    int *data = new int[capacity];
    std::move(m_data, m_data + m_size, data);
    delete[] m_data;
    m_data = data;
    m_capacity = capacity;
}

template<typename T, typename A>
void Vector<T, A>::resize(const Vector<T, A>::size_type size) {
    reserve(size);
    for (auto i = m_size; i < size; ++i) {
        m_data[i] = 0;
    }
    m_size = size;
}

template<typename T, typename A>
void Vector<T, A>::push_back(const int i) {
    if (m_capacity == 0) reserve(1);
    if (m_size == m_capacity) reserve(m_capacity * 2);

    m_data[m_size] = i;
    ++m_size;
}

template<typename T, typename A>
void Vector<T, A>::shrink_to_fit() {
    if (m_size == m_capacity) return;

    int *data = new int[m_size];
    std::move(m_data, m_data + m_size, data);
    delete[] m_data;
    m_data = data;
    m_capacity = m_size;
}

template<typename T, typename A>
int &Vector<T, A>::operator[](const Vector<T, A>::size_type i) {
    return m_data[i];
}

template<typename T, typename A>
const int &Vector<T, A>::operator[](const Vector<T, A>::size_type i) const {
    return m_data[i];
}

template<typename T, typename A>
[[nodiscard]] Vector<T, A>::size_type Vector<T, A>::size() const {
    return m_size;
}

template<typename T, typename A>
[[nodiscard]] Vector<T, A>::size_type Vector<T, A>::capacity() const {
    return m_capacity;
}

template<typename T, typename A>
void Vector<T, A>::swap(Vector &other) noexcept {
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_data, other.m_data);
    std::swap(m_allocator, other.m_allocator);
}

template<typename T, typename A>
[[nodiscard]] int *Vector<T, A>::begin() {
    return m_data;
}

template<typename T, typename A>
[[nodiscard]] const int *Vector<T, A>::begin() const {
    return m_data;
}

template<typename T, typename A>
[[nodiscard]] int *Vector<T, A>::end() {
    return m_data + m_size;
}

template<typename T, typename A>
[[nodiscard]] const int *Vector<T, A>::end() const {
    return m_data + m_size;
}

template<typename T, typename A>
[[nodiscard]] bool operator==(const Vector<T, A> &lhs, const Vector<T, A> &rhs) {
    if (lhs.size() != rhs.size()) return false;

    for (typename Vector<T, A>::size_type i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }

    return true;
}

template<typename T, typename A>
[[nodiscard]] bool operator!=(const Vector<T, A> &lhs, const Vector<T, A> &rhs) {
    return !(lhs == rhs);
}

template<typename T, typename A>
[[nodiscard]] bool operator>=(const Vector<T, A> &lhs, const Vector<T, A> &rhs) {
    const typename Vector<T, A>::size_type size = std::min(lhs.size(), rhs.size());

    for (typename Vector<T, A>::size_type i = 0; i < size; ++i) {
        if (lhs[i] > rhs[i]) return true;
        if (lhs[i] < rhs[i]) return false;
    }

    return lhs.size() >= rhs.size();
}

template<typename T, typename A>
[[nodiscard]] bool operator<=(const Vector<T, A> &lhs, const Vector<T, A> &rhs) {
    const typename Vector<T, A>::size_type size = std::min(lhs.size(), rhs.size());

    for (typename Vector<T, A>::size_type i = 0; i < size; ++i) {
        if (lhs[i] > rhs[i]) return false;
        if (lhs[i] < rhs[i]) return true;
    }

    return lhs.size() <= rhs.size();
}

template<typename T, typename A>
[[nodiscard]] bool operator>(const Vector<T, A> &lhs, const Vector<T, A> &rhs) {
    const typename Vector<T, A>::size_type size = std::min(lhs.size(), rhs.size());

    for (typename Vector<T, A>::size_type i = 0; i < size; ++i) {
        if (lhs[i] < rhs[i]) return false;
        if (lhs[i] > rhs[i]) return true;
    }

    return lhs.size() > rhs.size();
}

template<typename T, typename A>
[[nodiscard]] bool operator<(const Vector<T, A> &lhs, const Vector<T, A> &rhs) {
    const typename Vector<T, A>::size_type size = std::min(lhs.size(), rhs.size());

    for (typename Vector<T, A>::size_type i = 0; i < size; ++i) {
        if (lhs[i] > rhs[i]) return false;
        if (lhs[i] < rhs[i]) return true;
    }

    return lhs.size() < rhs.size();
}

template<typename T, typename A>
void swap(Vector<T, A> &a, Vector<T, A> &b) noexcept {
    a.swap(b);
}

#endif //VECTOR_H
