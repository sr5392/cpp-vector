#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <initializer_list>

class Vector {
public:
    using size_type = std::size_t;

    Vector();

    explicit Vector(size_type size);

    Vector(std::initializer_list<int> init);

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
    int *m_data;
};

[[nodiscard]] bool operator==(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator!=(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator>=(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator>(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator<=(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator<(const Vector &lhs, const Vector &rhs);

void swap(Vector &a, Vector &b) noexcept;
#endif //VECTOR_H
