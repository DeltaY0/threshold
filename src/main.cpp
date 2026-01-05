#define MINI_LOGGER_IMPLEMENTATION
#include <logger.h>
#include <defines.h>

#include <SDL3/SDL.h>
#include <iostream>

#include <core/game.h>

int main() {
    // LOG_CHANGE_PRIORITY(LOG_WARN);

    y::Game game;

    YTHROWT(y::ErrType::Generic, "Failed to do basic math");
    return 0;

    // while(game.is_running()) {
    //     game.handle_input();
    //     game.update(60);
    //     game.render();
    // }

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
    if(!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    bool running = true;
    SDL_Event event;

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}