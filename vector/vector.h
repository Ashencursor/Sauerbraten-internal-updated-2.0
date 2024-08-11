#pragma once
#include "../pch.h"

class Vector2 {
    float x{};
    float y{};
};

class Vector3 {
public:
    float x;
    float y;
    float z;

    // Constructor
    constexpr Vector3() : x(0), y(0), z(0) {}
    constexpr Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    // operator- overload
    constexpr Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    bool operator==(const Vector3& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
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