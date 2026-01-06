#ifndef RENDERER_H
#define RENDERER_H

#include <defines.h>
#include <logger.h>
#include <error.h>

#include <SDL3/SDL.h>

namespace y {

struct pixel
{
    u8 r, g, b, a = 0xFF;

    pixel(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}
    pixel(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}
};

class Renderer
{
    private:
    SDL_Renderer* renderer;
    i32 screen_width, screen_height;

    public:
    Renderer(i32 w, i32 h);
    void put_pixel(i32 x, i32 y, pixel px);
    
    void render();

    // getters
    SDL_Renderer* get_sdl_renderer() const { return renderer; }

    ~Renderer();
};

}  // namespace y

#endif  // RENDERER_H