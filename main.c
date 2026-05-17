#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"

#define dt 7e-4
#define phi_0 (M_PI / 200)
#define g 9.81

int sgn(const double d) {
    return (0 < d) - (d < 0);
}


struct Vector computeAcceleration(const struct Vector a, const double k, const double mass, const double l_0) {
    constexpr auto f_g = (struct Vector){
        0,
        g
    };
    return vec_add(vec_mult(vec_norm(a), -k * (vec_mag(a) - l_0) / mass), f_g);
}

double computeMaxPhi(struct Vector r, const double k, const double mass, FILE *out) {
    const double l_0 = vec_mag(r);
    int heading = sgn(r.x / r.y);
    double maxPhi = -(float) heading * INFINITY;
    struct Vector v = {};
    for (int i = 0;; i++) {
        if (out) fprintf(out, "%d,%f,%f\n", i, r.x, r.y);
        const struct Vector accel = vec_mult(computeAcceleration(r, k, mass, l_0), dt);
        const double prev_phi = r.x / r.y;
        v = vec_add(v, accel);
        r = vec_add(r, vec_mult(v, dt));
        const double new_phi = r.x / r.y;
        if (sgn(new_phi - prev_phi) != heading) {
            if (fabs(new_phi) >= maxPhi) {
                maxPhi = fabs(new_phi);
            } else {
                return maxPhi;
            }
            heading *= -1;
        }
    }
}

double best_close_to_l0(double l_0, double mass, double k, int iterations, double learnRate) {
    struct Vector beg = {
        l_0 * sin(phi_0),
        l_0 * cos(phi_0),
    };
    struct Vector res = beg;
    double res_biggest_angle = computeMaxPhi(beg, k, mass, nullptr);
    for (int i = 0; i < iterations; i++) {
        struct Vector v = beg;
        v = vec_mult(v, 1 + learnRate*(2*(double)rand()/(double)RAND_MAX-1)/l_0); //NOLINT
        double biggest_angle = computeMaxPhi(v, k, mass, nullptr);
        if (biggest_angle > res_biggest_angle) {
            res_biggest_angle = biggest_angle;
            res = v;
        }
    }
    return vec_mag(res);
}

int main(void) {
    srand(time(nullptr)); //NOLINT
    static_assert(dt != 0);
    FILE *f = fopen("/Users/sashko/mystuff/progfrog/cp/simulc/out.txt", "w+");
    double l_0 = 10.5;
    int rep = 0;
    for (int i = 0; i < 200; ++i) {
        double c = best_close_to_l0(l_0, 1, 2, 200, 1);
        if (c == l_0) rep++;
        else rep = 0;
        printf("c: %f; rep: %d\n", c, rep);
        fflush(stdout);
        l_0 = c;
    }

    fclose(f);
    return 0;
}
