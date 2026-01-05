#ifndef GAME_H
#define GAME_H

#include <core/window.h>

#include <error.h>

namespace y{

class Game {
    private:
        Window window;
        bool running = false;

        void init_game();

    public:
        Game() : running(true) {
            init_game();
            running = true;
        }

        void handle_input();
        void update(i32 deltatime);
        void render();

        // getters/setters
        bool is_running() const { return running; }
};

}


#endif // GAME_H