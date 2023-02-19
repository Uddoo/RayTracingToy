//
// Created by yw_li on 2023/2/19.
//

#ifndef RAYTRACINGTOY_RTWEEKEND_H
#define RAYTRACINGTOY_RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>

// Usings
using std::shared_ptr;
using std::make_shared;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }

inline double ffmax(double a, double b) { return a >= b ? a : b; }

// Random
inline double random_double() {
    // 返回[0,1)之间的随机实数
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // 返回[min,max)之间的随机实数
    return min + (max - min) * random_double();
}

// Clamp
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common Headers
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACINGTOY_RTWEEKEND_H