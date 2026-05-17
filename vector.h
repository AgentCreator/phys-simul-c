//
// Created by Oleksander Krainiak on 17.05.2026.
//

#ifndef SIMULC_VECTOR_H
#define SIMULC_VECTOR_H

struct Vector {
    double x, y;
};

struct Vector vec_add(struct Vector a, struct Vector b);

struct Vector vec_mult(struct Vector a, double scalar);

double vec_mag(struct Vector a);

struct Vector vec_norm(struct Vector a);

#endif //SIMULC_VECTOR_H
