#ifndef GAME_H
#define GAME_H

#include <core/window.h>
#include <error.h>

namespace y {

class Game
{
    private:
    Window* window;
    bool running = false;

    SDL_Event event;

    void init_game();

    public:
    Game() : running(true) {
        init_game();
        running = true;
    }

    // window methods
    inline void window_set_title(string title) {
        window->set_window_title(title);
    }

    inline void window_set_size(i32 width, i32 height) {
        window->set_window_size(width, height);
    }

    // main methods
    void handle_input();
    void update(i32 deltatime);
    void render();

    // getters/setters
    bool is_running() const { return running; }

    // destructor
    ~Game();
};

}  // namespace y

#endif  // GAME_H