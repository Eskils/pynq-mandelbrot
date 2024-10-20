#include "color-conversion.h"

rgb rgbFromHue(float hue, float offset) {
    rgb result;

    float k = 2 * M_PI_F * hue + offset;
    
    result.r = (sin(k) + 1) / 2;
    result.g = (sin(k + M_PI_2_F) + 1) / 2;
    result.b = (sin(k + 3 * M_PI_2_F) + 1) / 2;
    
    return result;
}