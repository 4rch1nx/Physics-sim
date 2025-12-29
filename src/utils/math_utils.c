#include "math_utils.h"
#include <stdlib.h>

float clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

float random_float(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}
