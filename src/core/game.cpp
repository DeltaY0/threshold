#include <core/game.h>

void y::Game::init_game() {
    YSDLCHECK(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS));

    if(1 + 1 == 3) {
        YTHROWT(y::ErrType::Generic, "Failed to do basic math");
    }
}

void y::Game::handle_input() {}

void y::Game::update(i32 deltatime) {}

void y::Game::render() {}
