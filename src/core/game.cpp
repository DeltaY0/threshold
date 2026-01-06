#include <core/game.h>

void y::Game::init_game() {
    YSDLCHECK(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS));

    window = make_unique<Window>("WINDOW", 800, 600);
}

void y::Game::handle_input() {
    // quit
    if(event.type == SDL_EVENT_QUIT) {
        running = false;
    }
}

void y::Game::update(i32 deltatime) {
    SDL_PollEvent(&event);

    renderer->render();
}

void y::Game::render() {}

y::Game::~Game() {
    SDL_DestroyRenderer(renderer->get_sdl_renderer());
    SDL_DestroyWindow(window->get_sdl_window());
    SDL_Quit();
}
