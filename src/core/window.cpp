#include <core/window.h>

namespace y {

Window::Window() : window_title("SDL3 Window") {
    init_window();
}

Window::Window(i32 width, i32 height)
    : window_title("SDL3 Window"), window_width(width), window_height(height) {
    init_window();
}

Window::Window(string title, i32 width, i32 height)
    : window_title(title), window_width(width), window_height(height) {
    init_window();
}

void Window::init_window() {
    // clang-format off

    SDL_WindowFlags creation_flags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow(
        window_title.c_str(),
        window_width, window_height,
        creation_flags
    );

    if(window == NULL)
        YTHROWT(y::ErrType::SDL, "couldn't create an SDL Window");

    SDL_WindowFlags pos_flags = SDL_WINDOWPOS_CENTERED;
    YSDLCHECK(
        SDL_SetWindowPosition(
            window,
            pos_flags,
            pos_flags
        )
    );

    LOGFMT(PROJNAME, "window", "initialized window successfully");

    // clang-format on
}

void Window::set_title(string title) {
    this->window_title = title;

    YSDLCHECK(SDL_SetWindowTitle(window, window_title.c_str()));

    LOGFMT(PROJNAME, "window",
           "changed window title to: ", YELLOW_TEXT(title.c_str()));
}

void Window::set_size(i32 width, i32 height) {
    this->window_width = width, this->window_height = height;

    YSDLCHECK(SDL_SetWindowSize(window, width, height));

    LOGFMT(PROJNAME, "window",
           "resized window to: ", YELLOW_TEXT("w: ", width, " h: ", height));
}

Window::~Window() {
    if(window) {
        SDL_DestroyWindow(window);
        LOGFMT(PROJNAME, "window", "destroyed SDL window");
    }
}
}  // namespace y
