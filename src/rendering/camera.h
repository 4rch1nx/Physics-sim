#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

// Complete struct definition
typedef struct Camera {
    float x, y;           // Camera position (world coordinates)
    float zoom;           // Zoom level (1.0 = normal)
    int viewport_width;   // Viewport size in pixels
    int viewport_height;
    float rotation;       // Camera rotation in radians
    bool follow_target;   // Whether to follow a target
    float target_x, target_y;
} Camera;

Camera* camera_create(int viewport_width, int viewport_height);
void camera_destroy(Camera* camera);

// Camera control
void camera_set_position(Camera* camera, float x, float y);
void camera_move(Camera* camera, float dx, float dy);
void camera_set_zoom(Camera* camera, float zoom);
void camera_zoom(Camera* camera, float factor);
void camera_set_rotation(Camera* camera, float rotation);
void camera_rotate(Camera* camera, float angle);
void camera_set_viewport(Camera* camera, int width, int height);

// Target following
void camera_set_target(Camera* camera, float x, float y);
void camera_clear_target(Camera* camera);

// Coordinate transformations
void camera_world_to_screen(const Camera* camera, float world_x, float world_y, int* screen_x, int* screen_y);
void camera_screen_to_world(const Camera* camera, int screen_x, int screen_y, float* world_x, float* world_y);

// Apply camera transformation to renderer
void camera_apply(const Camera* camera, SDL_Renderer* renderer);
void camera_reset(const Camera* camera, SDL_Renderer* renderer);

#endif // CAMERA_H
