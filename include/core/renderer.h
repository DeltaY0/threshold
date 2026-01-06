#ifndef RENDERER_H
#define RENDERER_H

#include <defines.h>
#include <logger.h>
#include <error.h>
#include <core/types.h>

#include <core/window.h>
#include <world/map.h>

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

    world::Camera cam;
    world::Map map;

    public:
    Renderer(Window* window, i32 w, i32 h);

    // init
    void init_cam(f64 posx, f64 posy, f64 angle);
    void load_map(string mapfile);

    // drawing
    void put_pixel(i32 x, i32 y, pixel px);
    void draw_line(y::math::Line line, y::pixel px);
    void render_map();

    // rendering
    void update_screen();
    void render();

    // getters
    SDL_Renderer* get_sdl_renderer() const { return renderer; }

    ~Renderer();
};

}  // namespace y

#endif  // RENDERER_H