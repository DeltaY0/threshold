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
    i32 width = 800, height = 600;

    void init_window();

    // TODO: functions for changing window properties

    public:
    // constructors
    Window();
    Window(i32 width, i32 height);
    Window(string title, i32 width, i32 height);

    // setters
    void set_window_title(string title);
    void set_window_size(i32 width, i32 height);

    // getters
    i32 get_width() const { return width; }
    i32 get_height() const { return height; }

    // destructor
    ~Window();
};

}  // namespace y

#endif  // WINDOW_H