#include <core/game.h>

void y::Game::init_game() {
    YSDLCHECK(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS));

    window   = make_unique<Window>("WINDOW", 800, 600);
    renderer = make_unique<Renderer>(window.get(), window->get_width(),
                                     window->get_height());
}

void y::Game::handle_input() {
    SDL_PollEvent(&event);

    // quit
    if(event.type == SDL_EVENT_QUIT) {
        running = false;
    }
}

void y::Game::update(i32 deltatime) {}

void y::Game::render() {
    renderer->render();
}

y::Game::~Game() {
    SDL_Quit();
}
