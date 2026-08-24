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

inline std::ostream& operator<<(std::ostream& os, const Vec2& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
#endif //PROJECT_BANANA_VEC2_HPP
