//
// Created by natha on 26/08/2026.
//

#ifndef PROJECT_BANANA_VISION_HPP
#define PROJECT_BANANA_VISION_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <cmath>
#include <numbers>
#include <vector>

#include "Vec2.hpp"

/**
 * @brief A structure representing the vision capabilities of an entity,
 * including range and angle in degrees.
 */
struct Vision {
    int range;
    int angle;

    /**
     *
     * @return a Vec2 vector that will give the list of visible relative coordinates
     */
    std::vector<Vec2> getVisiblePositions() const {
        std::vector<Vec2> visible_positions;

        const float angle_radians =
                static_cast<float>(angle) * std::numbers::pi_v<float> / 180.0f;

        const float half_angle = angle_radians / 2.0f;

        // for (int dx = 0; dx <= range; ++dx)
        // {
        //     for (int dy = -range; dy <= range; ++dy)
        //     {
        //         // The creature itself is not part of its vision.
        //         if (dx == 0 && dy == 0)
        //             continue;
        //
        //         const float point_angle =
        //             std::atan2(
        //                 static_cast<float>(dy),
        //                 static_cast<float>(dx)
        //             );
        //
        //         if (point_angle >= -half_angle &&
        //             point_angle <= half_angle)
        //         {
        //             visible_positions.push_back({dx, dy});
        //         }
        //     }
        // }
        for (int dx = std::cos(half_angle) * range; dx <= range; ++dx) {
            for (int dy = 0; dy <= range; ++dy) {
                if (dx == 0 && dy == 0)
                    continue;

                if (std::atan2<float>(dy, dx) <= half_angle && dx*dx + dy*dy <= range*range) {
                    visible_positions.push_back({dx, dy});
                    if (dy != 0) visible_positions.push_back({dx, -dy});
                }
            }
        }

        std::ranges::sort(visible_positions
                          ,
                          [](const Vec2 &a, const Vec2 &b) {
                              int distance_a = a.x * a.x + a.y * a.y;
                              int distance_b = b.x * b.x + b.y * b.y;

                              return distance_a < distance_b;
                          }
        );

        return visible_positions;
    }
};

inline bool operator==(const Vision &a, const Vision &b) {
    return a.range == b.range &&
           a.angle == b.angle;
}

struct VisionHasher {
    std::size_t operator()(const Vision &vision) const {
        return std::hash<int>{}(vision.range) ^
               (std::hash<int>{}(vision.angle) << 1);
    }
};

#endif // PROJECT_BANANA_VISION_HPP
