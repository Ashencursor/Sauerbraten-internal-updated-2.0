#pragma once
#include "../pch.h"

class Vector2 {
public:
    float x{};
    float y{};

    constexpr Vector2() : x{ 0 }, y{ 0 } {}
    friend constexpr Vector2 operator-(const Vector2 lhs, const Vector2& rhs)  {
        return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    constexpr Vector2(float _x, float _y) : x{ _x }, y{ _y } {}
    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
};

class Vector3 {
public:
    float x{};
    float y{};
    float z{};

    // Constructor
    constexpr Vector3() : x(0), y(0), z(0) {}
    constexpr Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // operator- overload
    friend constexpr Vector3 operator-(const Vector3& lhs, const Vector3& rhs)  {
        return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend bool operator==(const Vector3& lhs, const Vector3& rhs) = default;

    // Copy construcor
    Vector3(const Vector3& other) : x{ other.x }, y{ other.y }, z{ other.z } {}
    // Copy assingment operator
    Vector3& operator=(const Vector3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }
    // Move constructor
    Vector3(Vector3&& other) noexcept : x{ other.x }, y{ other.y }, z{ other.z } {
        other.x = 0;
        other.y = 0;
        other.z = 0;
    }
    // Move assingment operator
    Vector3& operator=(Vector3&& other) noexcept {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            other.x = 0;
            other.y = 0;
            other.z = 0;
        }
        return *this;
    }

    // Method to calculate the length of the vector
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Method to calculate the distance to another vector
    inline float distance(const Vector3& other) const {
        return (*this - other).length();
    }
};

class Vector4 {
    float x{};
    float y{};
    float z{};
    float w{};
};