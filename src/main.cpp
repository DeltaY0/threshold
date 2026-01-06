#define MINI_LOGGER_IMPLEMENTATION
#include <logger.h>
#include <defines.h>

#include <SDL3/SDL.h>
#include <iostream>

#include <core/game.h>

int main() {
    LOG_CHANGE_PRIORITY(LOG_WARN);

    y::Game* game = new y::Game;

    game->window_set_title("THRESHOLD");

    while(game->is_running()) {
        game->handle_input();
        game->update(60);
        game->render();
    }

    delete game;

    return 0;
}