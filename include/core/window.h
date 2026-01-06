#ifndef WINDOW_H
#define WINDOW_H

#include <defines.h>
#include <logger.h>
#include <error.h>

#include <SDL3/SDL.h>

namespace y {

class Window
{
    private:
    SDL_Window* window;
    string window_title;
    i32 window_width = 800, window_height = 600;

    void init_window();

    // TODO: functions for changing window properties

    public:
    // constructors
    Window();
    Window(i32 width, i32 height);
    Window(string title, i32 width, i32 height);

    // setters
    void set_title(string title);
    void set_size(i32 width, i32 height);

    // getters
    string get_title() const { return window_title; }
    i32 get_width() const { return window_width; }
    i32 get_height() const { return window_height; }
    SDL_Window* get_sdl_window() const { return window; }

    ~Window();
};

}  // namespace y

#endif  // WINDOW_H