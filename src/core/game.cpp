#include <core/game.h>

void y::Game::init_game() {
    YSDLCHECK(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS));

    window = new Window("WINDOW", 800, 600);
}

void y::Game::handle_input() {
    // quit
    if(event.type == SDL_EVENT_QUIT) {
        running = false;
    }
}

void y::Game::update(i32 deltatime) {
    SDL_PollEvent(&event);
}

void y::Game::render() {}

y::Game::~Game() {
    delete window;

    SDL_Quit();
}
