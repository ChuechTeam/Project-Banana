//
// Created by natha on 24/08/2026.
//

#ifndef PROJECT_BANANA_VEC2_HPP
#define PROJECT_BANANA_VEC2_HPP
#include <iostream>

/**
 * @brief A simple 2D vector structure for representing positions or directions in a 2D space.
 */
struct Vec2 {
    int x, y;

    Vec2 operator+(const Vec2& other) const
    {
        return {x + other.x, y + other.y};
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }


};

inline bool operator==(const Vec2& a, const Vec2& b)
{
    return a.x == b.x && a.y == b.y;
}

inline std::ostream& operator<<(std::ostream& os, const Vec2& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

struct Vec2Hasher
{
    std::size_t operator()(const Vec2& vec) const
    {
        // Combine the hash of x and y using XOR and bit shifting
        return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
    }
};
#endif //PROJECT_BANANA_VEC2_HPP
