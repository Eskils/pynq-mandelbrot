#include <math.h>

typedef struct complex_float2 {
    float x;
    float y;
} complex_float2;

typedef complex_float2 Complex;

Complex complex_make_rectangular(float real, float imaginary);
Complex complex_make_polar(float magnitude, float argument);
float complex_get_magnitude(Complex z);
float complex_get_argument(Complex z);
Complex complex_pow(Complex z, float power);
Complex complex_add(Complex z1, Complex z2);