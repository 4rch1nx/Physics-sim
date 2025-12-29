#include <SDL2/SDL.h>
#include "rendering/renderer.h"
#include "simulation/simulation.h"

int main(int argc, char* argv[]) {
    // Initialize SDL and create window/renderer
    if (!renderer_init(800, 600, "Ultimate Sim")) {
        return 1;
    }

    // Initialize simulation
    simulation_init();

    // Main loop
    int running = 1;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
                // Pass key events to simulation
                simulation_handle_input(event.key.keysym.sym);
            }
        }

        // Update simulation
        simulation_update();

        // Clear screen
        renderer_clear(0, 0, 0, 255);

        // Get simulation state and render
        SimulationState* state = simulation_get_state();
        
        // Render simulation objects
        for (int i = 0; i < state->object_count; i++) {
            GameObject* obj = &state->objects[i];
            renderer_draw_rect(obj->x, obj->y, obj->width, obj->height, 
                             obj->color_r, obj->color_g, obj->color_b, 255);
        }

        // Present frame
        renderer_present();
    }

    // Cleanup
    simulation_cleanup();
    renderer_cleanup();

    return 0;
}
