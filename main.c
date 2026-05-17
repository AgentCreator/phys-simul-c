#include <math.h>
#include <stdio.h>
#include "vector.h"
#include <math.h>

#define dt 0.0007
#define g 9.81

int sgn(double d) {
    return (0 < d) - (d < 0);
}


struct Vector computeAcceleration(const struct Vector a, const double k, const double mass, const double l_0) {
    constexpr auto f_g = (struct Vector){
        0,
        g
    };
    return vec_add(vec_mult(vec_norm(a), -k * (vec_mag(a) - l_0) / mass), f_g);
}

double computeMaxPhi(
    struct Vector *r, const double k, const double mass, FILE *out) {
    const double l_0 = vec_mag(*r);
    int heading = sgn(r->x / r->y);
    double maxPhi = -(float)heading * INFINITY;
    struct Vector v = {};
    if (out) fprintf(out, "0,%f,%f", r->x, r->y);
    while (true) {
        const struct Vector accel = vec_mult(computeAcceleration(*r, k, mass, l_0), dt);
        const double prev_phi = r->x/r->y;
        v = vec_add(v, accel);
        *r = vec_add(*r, vec_mult(v, dt));
        const double new_phi = r->x/r->y;
        if (sgn(new_phi-prev_phi) != heading) {
            if (fabs(new_phi) >= maxPhi) {
                maxPhi = fabs(new_phi);
            } else {
                return maxPhi;
            }
            heading *= -1;
        }
    }
    // double
}

int main(void) {
    constexpr double l_0 = 19;
    constexpr double phi_0 = M_PI / 200;
    struct Vector v_0 = {
        l_0 * sin(phi_0),
        l_0 * cos(phi_0),
    };
    const double maxPhi = computeMaxPhi(&v_0, 2, 1, nullptr);
    printf("maxPhi: %f\n", maxPhi);
    return 0;
}
