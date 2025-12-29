#include "camera.h"
#include <math.h>
#include <stdlib.h>

Camera* camera_create(int viewport_width, int viewport_height) {
    Camera* camera = (Camera*)malloc(sizeof(Camera));
    if (!camera) return NULL;
    
    camera->x = 0;
    camera->y = 0;
    camera->zoom = 1.0f;
    camera->viewport_width = viewport_width;
    camera->viewport_height = viewport_height;
    camera->rotation = 0.0f;
    camera->follow_target = false;
    camera->target_x = 0;
    camera->target_y = 0;
    
    return camera;
}

void camera_destroy(Camera* camera) {
    free(camera);
}

void camera_set_position(Camera* camera, float x, float y) {
    camera->x = x;
    camera->y = y;
}

void camera_move(Camera* camera, float dx, float dy) {
    camera->x += dx / camera->zoom;
    camera->y += dy / camera->zoom;
}

void camera_set_zoom(Camera* camera, float zoom) {
    camera->zoom = zoom;
    if (camera->zoom < 0.1f) camera->zoom = 0.1f;
    if (camera->zoom > 10.0f) camera->zoom = 10.0f;
}

void camera_zoom(Camera* camera, float factor) {
    camera->zoom *= factor;
    if (camera->zoom < 0.1f) camera->zoom = 0.1f;
    if (camera->zoom > 10.0f) camera->zoom = 10.0f;
}

void camera_set_target(Camera* camera, float x, float y) {
    camera->follow_target = true;
    camera->target_x = x;
    camera->target_y = y;
}

void camera_clear_target(Camera* camera) {
    camera->follow_target = false;
}

void camera_world_to_screen(const Camera* camera, float world_x, float world_y, int* screen_x, int* screen_y) {
    // Apply rotation
    float cos_angle = cos(-camera->rotation);
    float sin_angle = sin(-camera->rotation);
    
    // Translate to camera space
    float tx = world_x - camera->x;
    float ty = world_y - camera->y;
    
    // Apply rotation
    float rx = tx * cos_angle - ty * sin_angle;
    float ry = tx * sin_angle + ty * cos_angle;
    
    // Apply zoom and translate to screen center
    *screen_x = (int)(rx * camera->zoom + camera->viewport_width / 2);
    *screen_y = (int)(ry * camera->zoom + camera->viewport_height / 2);
}

void camera_screen_to_world(const Camera* camera, int screen_x, int screen_y, float* world_x, float* world_y) {
    // Translate to camera space
    float tx = (screen_x - camera->viewport_width / 2) / camera->zoom;
    float ty = (screen_y - camera->viewport_height / 2) / camera->zoom;
    
    // Apply inverse rotation
    float cos_angle = cos(camera->rotation);
    float sin_angle = sin(camera->rotation);
    
    float rx = tx * cos_angle - ty * sin_angle;
    float ry = tx * sin_angle + ty * cos_angle;
    
    // Translate to world space
    *world_x = rx + camera->x;
    *world_y = ry + camera->y;
}

void camera_apply(const Camera* camera, SDL_Renderer* renderer) {
    // SDL doesn't have built-in transformation matrices for 2D,
    // so we handle transformations manually in rendering functions
    // This function sets up the renderer for camera transformations
}

void camera_reset(const Camera* camera, SDL_Renderer* renderer) {
    // Reset any transformations
    // In SDL2, we typically handle camera transforms manually
}
