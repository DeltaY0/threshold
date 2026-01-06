#include <core/renderer.h>

namespace y {

Renderer::Renderer(Window* window, i32 w, i32 h)
    : screen_width(w), screen_height(h) {
    // clang-format off

    renderer = SDL_CreateRenderer(
        window->get_sdl_window(),
        SDL_SOFTWARE_RENDERER
    );

    if(renderer == NULL)
        YTHROWT(y::ErrType::Render, "couldn't create an SDL Renderer Context");

    // clang-format on
}

void Renderer::init_cam(f64 posx, f64 posy, f64 angle) {
    cam = world::Camera(posx, posy, angle);
}

void Renderer::load_map(string mapfile) {
    map = world::Map(mapfile);
}

void Renderer::put_pixel(i32 x, i32 y, pixel px) {
    if(x > screen_width || y > screen_height)
        return;

    if(x < 0 || y < 0)
        return;

    YSDLCHECK(SDL_SetRenderDrawColor(renderer, px.r, px.g, px.b, px.a));
    YSDLCHECK(SDL_RenderPoint(renderer, x, y));
}

void Renderer::draw_line(y::math::Line line) {
    // DDA[Digital Differential Analyzer] implementation
    auto [x0, y0, x1, y1] = line.get();

    i32 dx, dy;
    dx = (x1 > x0) ? x1 - x0 : x0 - x1;
    dy = (y1 > y0) ? y1 - y0 : y0 - y1;

    i32 sx  = (x0 < x1) ? 1 : -1;
    i32 sy  = (y0 < y1) ? 1 : -1;
    i32 err = (dx > dy ? dx : -dy) / 2;
    i32 err2;

    while(true) {
        put_pixel(x0, y0, pixel(0x55, 0xAA, 0x33));

        if(x0 == x1 || y0 == y1)
            break;

        err2 = err;
        if(err2 > -dx)
            err -= dy, x0 += sx;

        if(err2 < dy)
            err += dx, y0 += sy;
    }
}

void Renderer::render_map() {
    vector<math::Polygon> polys = map.get_polygons();

    // TODO: render stuff
}

void Renderer::render() {
    YSDLCHECK(SDL_RenderPresent(renderer));
}

Renderer::~Renderer() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
        LOGFMT(PROJNAME, "renderer", "destroyed SDL renderer");
    }
}

}  // namespace y