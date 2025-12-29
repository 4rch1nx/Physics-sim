#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdbool.h>

typedef struct {
    float x, y;
    float width, height;
    float velocity_x, velocity_y;
    Uint8 color_r, color_g, color_b;
} GameObject;

typedef struct {
    GameObject* objects;
    int object_count;
    int max_objects;
    bool running;
} SimulationState;

// Simulation lifecycle
void simulation_init();
void simulation_update();
void simulation_cleanup();

// Input handling
void simulation_handle_input(SDL_Keycode key);

// State access
SimulationState* simulation_get_state();

// Object management
void simulation_add_object(float x, float y, float w, float h, 
                          float vx, float vy, Uint8 r, Uint8 g, Uint8 b);

#endif
