#ifndef WINDOW_H
#define WINDOW_H

#include <defines.h>
#include <logger.h>

#include <SDL3/SDL.h>

namespace y {

class Window {
    private:
        SDL_Window *window;

        void init_window();

        // TODO: functions for changing window properties

    public:
        Window();
        Window(i32 width, i32 height);
};

} // namespace y

#endif // WINDOW_H