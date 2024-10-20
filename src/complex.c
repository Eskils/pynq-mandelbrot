#include "complex.h"

Complex complex_make_rectangular(float real, float imaginary) {
    Complex z = {real, imaginary};
    return z;
}

Complex complex_make_polar(float magnitude, float argument) {
    float real = magnitude * cos(argument);
    float imaginary = magnitude * sin(argument);
    return complex_make_rectangular(real, imaginary);
}

float complex_get_magnitude(Complex z) {
    return hypot(z.x, z.y);
}

float complex_get_argument(Complex z) {
    return atan2(z.y, z.x);
}

Complex complex_pow(Complex z, float power) {
    float magnitude = pow(complex_get_magnitude(z), power);
    float argument = power * complex_get_argument(z);
    return complex_make_polar(magnitude, argument);
}

Complex complex_add(Complex z1, Complex z2) {
    return complex_make_rectangular(
        z1.x + z2.x,
        z1.y + z2.y
    );
}