#ifndef GAME_H
#define GAME_H

#include <defines.h>
#include <logger.h>
#include <error.h>

#include <core/window.h>
#include <core/renderer.h>

using std::make_unique;
using std::unique_ptr;

namespace y {

class Game
{
    private:
    // NOTE: window declared first beofer renderer
    //  to ensure renderer is destroyed first (RAII)
    unique_ptr<Window> window;
    unique_ptr<Renderer> renderer;
    bool running = false;

    SDL_Event event;

    void init_game();

    public:
    Game() : running(true) {
        init_game();
        running = true;
    }

    // window methods
    inline void window_set_title(string title) { window->set_title(title); }

    inline void window_set_size(i32 width, i32 height) {
        window->set_size(width, height);
    }

    // renderer methods
    inline void load_map(string filepath) {
        renderer->load_map(filepath);
    }
    inline void setup_camera(f64 posx, f64 posy, f64 angle) {
        renderer->init_cam(posx, posy, angle);
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