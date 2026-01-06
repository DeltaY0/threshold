#include <core/window.h>

namespace y {

Window::Window() : window_title("SDL3 Window") {
    init_window();
}

Window::Window(i32 width, i32 height)
    : window_title("SDL3 Window"), width(width), height(height) {
    init_window();
}

Window::Window(string title, i32 width, i32 height)
    : window_title(title), width(width), height(height) {
    init_window();
}

void Window::init_window() {
    // clang-format off

    SDL_WindowFlags creation_flags = SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow(
        window_title.c_str(),
        width, height,
        creation_flags
    );

    SDL_WindowFlags pos_flags = SDL_WINDOWPOS_CENTERED;
    SDL_SetWindowPosition(
        window,
        pos_flags,
        pos_flags
    );

    LOGFMT(PROJNAME, "window", "initialized window successfully");

    // clang-format on
}

void Window::set_window_title(string title) {
    this->window_title = title;

    YSDLCHECK(SDL_SetWindowTitle(window, window_title.c_str()));

    LOGFMT(PROJNAME, "window",
           "changed window title to: ", YELLOW_TEXT(title.c_str()));
}

void Window::set_window_size(i32 width, i32 height) {
    this->width = width, this->height = height;

    YSDLCHECK(SDL_SetWindowSize(window, width, height));

    LOGFMT(PROJNAME, "window",
           "resized window to: ", YELLOW_TEXT("w: ", width, " h: ", height));
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

}  // namespace y
