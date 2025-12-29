#include "simulation.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

static SimulationState g_state = {0};

void simulation_init() {
    g_state.max_objects = 100;
    g_state.objects = malloc(sizeof(GameObject) * g_state.max_objects);
    g_state.object_count = 0;
    g_state.running = true;

    // Add some initial objects
    simulation_add_object(100, 100, 50, 50, 1.0f, 0.5f, 255, 0, 0);
    simulation_add_object(200, 200, 40, 40, -0.5f, 1.0f, 0, 255, 0);
    simulation_add_object(300, 300, 60, 60, 0.7f, -0.3f, 0, 0, 255);
}

void simulation_update() {
    if (!g_state.running) return;

    // Update each object's position
    for (int i = 0; i < g_state.object_count; i++) {
        GameObject* obj = &g_state.objects[i];
        
        // Update position
        obj->x += obj->velocity_x;
        obj->y += obj->velocity_y;

        // Simple boundary checking (bounce)
        if (obj->x <= 0 || obj->x + obj->width >= 800) {
            obj->velocity_x = -obj->velocity_x;
        }
        if (obj->y <= 0 || obj->y + obj->height >= 600) {
            obj->velocity_y = -obj->velocity_y;
        }

        // Keep within bounds
        if (obj->x < 0) obj->x = 0;
        if (obj->y < 0) obj->y = 0;
        if (obj->x + obj->width > 800) obj->x = 800 - obj->width;
        if (obj->y + obj->height > 600) obj->y = 600 - obj->height;
    }
}

void simulation_cleanup() {
    if (g_state.objects) {
        free(g_state.objects);
        g_state.objects = NULL;
    }
    g_state.object_count = 0;
}

void simulation_handle_input(SDL_Keycode key) {
    switch (key) {
        case SDLK_SPACE:
            // Toggle simulation
            g_state.running = !g_state.running;
            break;
        case SDLK_r:
            // Reset simulation
            g_state.object_count = 0;
            simulation_add_object(100, 100, 50, 50, 1.0f, 0.5f, 255, 0, 0);
            break;
        case SDLK_a:
            // Add new object
            simulation_add_object(
                rand() % 700, rand() % 500, 
                30 + rand() % 40, 30 + rand() % 40,
                (rand() % 10 - 5) / 5.0f, (rand() % 10 - 5) / 5.0f,
                rand() % 256, rand() % 256, rand() % 256
            );
            break;
    }
}

SimulationState* simulation_get_state() {
    return &g_state;
}

void simulation_add_object(float x, float y, float w, float h, 
                          float vx, float vy, Uint8 r, Uint8 g, Uint8 b) {
    if (g_state.object_count >= g_state.max_objects) {
        // Resize array if needed
        g_state.max_objects *= 2;
        g_state.objects = realloc(g_state.objects, 
                                 sizeof(GameObject) * g_state.max_objects);
    }

    GameObject* obj = &g_state.objects[g_state.object_count++];
    obj->x = x;
    obj->y = y;
    obj->width = w;
    obj->height = h;
    obj->velocity_x = vx;
    obj->velocity_y = vy;
    obj->color_r = r;
    obj->color_g = g;
    obj->color_b = b;
}
