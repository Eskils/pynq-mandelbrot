#include "complex.h"
#include <libpynq.h>
#include "color-conversion.h"

int main() {

    display_t displayRef;

    pynq_init();
    display_init(&displayRef);

    displayFillScreen(&displayRef, RGB_BLUE);

    int iterations = 100;
    float fIterations = (float)iterations;
    float width = (float)displayRef._width;
    float height = (float)displayRef._height;
    Complex offset = complex_make_rectangular(-0.7, -0.5);
    Complex scale = complex_make_rectangular(2.25, 2.25);
    Complex coordinate = complex_make_rectangular(0, 0);
    Complex result = complex_make_rectangular(0, 0);
    float resultMagnitude = 0;
    uint16_t gidX;
    uint16_t gidY;
    int i;
    float threshold = 0;

    for (gidY = 0; gidY < height; gidY++) {
        for (gidX = 0; gidX < width; gidX++) {
            coordinate.x = scale.x * ((float)gidX / width + offset.x);
            coordinate.y = scale.y * ((float)gidY / height + offset.y);

            result.x = 0;
            result.y = 0;

            for (i = 0; i < iterations; i++) {
                result = complex_add(
                    complex_pow(result, 2.0f),
                    coordinate
                );
                resultMagnitude = complex_get_magnitude(result);

                if (resultMagnitude > 2.0f) {
                    threshold = 1 - ((float)i / fIterations);
                    rgb color = rgbFromHue(threshold, 0.2);
                    uint16_t color16 = rgb_conv(
                        (uint16_t)(255 * color.r), 
                        (uint16_t)(255 * color.g), 
                        (uint16_t)(255 * color.b)
                    );
                    displayDrawPixel(&displayRef, gidX, gidY, color16);
                    i = iterations;
                }
            }

            if (resultMagnitude <= 2.0f) {
                displayDrawPixel(&displayRef, gidX, gidY, RGB_BLACK);
            }
        }
    }

    display_destroy(&displayRef);
    pynq_destroy();

    return 0;
}