#include "camera.h"

using namespace Raytra;

Camera::Camera() {}

Camera::Camera(float x, float y, float z,
               float vx, float vy, float vz,
               float d, float iw, float ih, int pw, int ph)
{
    eye = {.x = x, .y = y, .z = z};

    vec direction = {.x = vx, .y = vy, .z = vz};
    vec up = {.x = 0, .y = 1, .z = 0};

    w = norm(-(direction));
    u = norm(cross(direction, up));
    v = norm(cross(direction, u));

    focal_length = d;

    nx = pw; ny = ph;

    left = -iw/2; bottom = -ih/2; right = iw/2; top = ih/2;
}

/**
 * Copy values to the passed camera
 * @param camera - copy data to the camera reference
 */
void Camera::copy_to_camera(Camera &camera)
{
    camera.nx = nx; camera.ny = ny;
    camera.left = left; camera.right = right;
    camera.top = top; camera.bottom = bottom;
    camera.focal_length = focal_length;

    camera.eye = eye;
    camera.w = w; camera.u = u; camera.v = v;
}

/**
 * Calculates the direction of camera ray to pixel (x, y)
 * @param x - x coordinate of pixel
 * @param y - y coordinate of pixel
 * @param i - x coordinate of strata
 * @param j - y coordinate of strata
 * @param strata_count - total number of strata
 * @return A vector denoting the direction of the camera
 * ray to pixel (x, y) on the image plane
 */
vec Camera::ray_direction (
        float x,
        float y,
        unsigned int i,
        unsigned int j,
        unsigned int strata_count
)
{
    float x_disp = (get_rand() + i) / strata_count;
    float y_disp = (get_rand() + j) / strata_count;
    float centerX = left + (right - left) * (x + x_disp)/nx;
    float centerY = bottom + (top - bottom) * (y + y_disp)/ny;
    return norm((-focal_length * w) + (centerX * u) + (centerY * v));
}

int Camera::pixelsY() { return ny; }
int Camera::pixelsX() { return nx; }
point Camera::get_center() { return eye; }
