#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <initializer_list>

class Vector {
private:
    std::size_t m_size;
    std::size_t m_capacity;
    int *m_data;

public:
    Vector();

    explicit Vector(std::size_t size);

    Vector(std::initializer_list<int> init);

    Vector(const Vector &other);

    Vector &operator=(const Vector &other);

    Vector(Vector &&other) noexcept;

    Vector &operator=(Vector &&other) noexcept;

    ~Vector();

    void reserve(std::size_t capacity);

    void resize(std::size_t size);

    void push_back(int i);

    int &operator[](std::size_t i);

    const int &operator[](std::size_t i) const;

    [[nodiscard]] std::size_t size() const;

    [[nodiscard]] std::size_t capacity() const;

    void swap(Vector &other) noexcept;

    [[nodiscard]] int *begin();

    [[nodiscard]] const int *begin() const;

    [[nodiscard]] int *end();

    [[nodiscard]] const int *end() const;
};

[[nodiscard]] bool operator==(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator!=(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator>=(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator>(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator<=(const Vector &lhs, const Vector &rhs);

[[nodiscard]] bool operator<(const Vector &lhs, const Vector &rhs);

void swap(Vector &a, Vector &b) noexcept;
#endif //VECTOR_H
