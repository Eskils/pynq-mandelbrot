#include <math.h>

#define M_PI_F 3.1415926536
#define M_PI_2_F 1.5707963268

typedef struct rgb {
  float r, g, b;
} rgb;

rgb rgbFromHue(float hue, float offset);