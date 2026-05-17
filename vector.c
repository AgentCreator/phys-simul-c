//
// Created by Oleksander Krainiak on 17.05.2026.
//

#include "vector.h"

#include <math.h>

struct Vector vec_add(const struct Vector a, const struct Vector b) {
    return (struct Vector){
        .x = a.x + b.x,
        .y = a.y + b.y,
    };
}

struct Vector vec_mult(const struct Vector a, const double scalar) {
    return (struct Vector){
        .x = a.x * scalar,
        .y = a.y * scalar,
    };
}

double vec_mag(const struct Vector a) {
    return hypotl(a.x, a.y);
}

struct Vector vec_norm(const struct Vector a) {
    return vec_mult(a, 1/vec_mag(a));
}
