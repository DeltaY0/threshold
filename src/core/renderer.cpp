#include <core/renderer.h>

namespace y {

Renderer::Renderer(i32 w, i32 h) : screen_width(w), screen_height(h) {
    // TODO: allocate any resources necessary

    // renderer = SDL_CreateRenderer(

    // );
}

void Renderer::put_pixel(i32 x, i32 y, pixel px) {
    if(x > screen_width || y > screen_height)
        return;

    if(x < 0 || y < 0)
        return;

    SDL_SetRenderDrawColor(renderer, px.r, px.g, px.b, px.a);
    SDL_RenderPoint(renderer, x, y);
}

void Renderer::render() {
    SDL_RenderPresent(renderer);
}

Renderer::~Renderer() {
    // TODO: dealloc all aquired resources
}

}  // namespace y