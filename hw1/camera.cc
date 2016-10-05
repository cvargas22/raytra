#include "camera.h"

using namespace Raytra;

Camera::Camera() {}

Camera::Camera(float x, float y, float z,
               float vx, float vy, float vz,
               float d, float iw, float ih, int pw, int ph)
{
    eye = {.x = x, .y = y, .z = z};

    vector direction = {.x = vx, .y = vy, .z = vz};
    vector up = {.x = 0, .y = 1, .z = 0};

    w = -(direction);
    u = cross(direction, up);
    v = cross(u, direction);

    focal_length = d;

    nx = pw; ny = ph;

    left = -iw/2; bottom = -ih/2; right = iw/2; top = ih/2;
}
