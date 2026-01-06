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

    game->load_map("res/maps/level_0.map");
    game->setup_camera(451.96, 209.24, 0.42);

    while(game->is_running()) {
        game->handle_input();
        game->update(60);
        game->render();
    }

    delete game;

    return 0;
}