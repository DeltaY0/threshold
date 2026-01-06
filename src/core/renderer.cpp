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
    if(x >= screen_width || y >= screen_height)
        return;

    if(x < 0 || y < 0)
        return;

    YSDLCHECK(SDL_SetRenderDrawColor(renderer, px.r, px.g, px.b, px.a));
    YSDLCHECK(SDL_RenderPoint(renderer, x, y));
}

void Renderer::draw_line(y::math::Line line, y::pixel px) {
    auto [fx0, fy0, fx1, fy1] = line.get();

    i32 x0 = static_cast<i32>(fx0);
    i32 y0 = static_cast<i32>(fy0);
    i32 x1 = static_cast<i32>(fx1);
    i32 y1 = static_cast<i32>(fy1);

    // standard DDA implementation
    i32 dx  = abs(x1 - x0);
    i32 dy  = abs(y1 - y0);
    i32 sx  = (x0 < x1) ? 1 : -1;
    i32 sy  = (y0 < y1) ? 1 : -1;
    i32 err = dx - dy;

    for(;;) {
        put_pixel(x0, y0, px);

        if(x0 == x1 && y0 == y1)
            break;

        i32 e2 = 2 * err;
        if(e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if(e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void Renderer::render_map() {
    vector<math::Polygon> polygons = map.get_polygons();

    for(auto poly : polygons) {
        for(size_t i = 0; i < poly.verts.size(); i++) {
            math::vec2 p1 = poly.verts[i];
            math::vec2 p2 = poly.verts[(i + 1) % poly.verts.size()];
            f64 height    = -poly.height;

            // transform pt 1
            f64 dx1 = p1.x - cam.cam_pos.x;
            f64 dy1 = p1.y - cam.cam_pos.y;

            // depth for pt 1
            f64 z1 = dx1 * cos(cam.cam_angle) + dy1 * sin(cam.cam_angle);

            // transform pt 2
            f64 dx2 = p2.x - cam.cam_pos.x;
            f64 dy2 = p2.y - cam.cam_pos.y;

            // depth for pt 2
            f64 z2 = dx2 * cos(cam.cam_angle) + dy2 * sin(cam.cam_angle);

            // near plane culling bug fix
            if(z1 < 0.1 || z2 < 0.1)
                continue;

            // cam rotation to x
            dx1 = dx1 * sin(cam.cam_angle) - dy1 * cos(cam.cam_angle);
            dx2 = dx2 * sin(cam.cam_angle) - dy2 * cos(cam.cam_angle);

            // screen projection
            f64 width_ratio  = screen_width / 2.0;
            f64 height_ratio = (screen_width * screen_height) / 60.0;

            f64 screen_center_h = screen_height / 2.0;
            f64 screen_center_w = screen_width / 2.0;

            f64 x1 = -dx1 * width_ratio / z1;
            f64 x2 = -dx2 * width_ratio / z2;

            f64 y1a = (height - height_ratio) / z1;
            f64 y1b = height_ratio / z1;
            f64 y2a = (height - height_ratio) / z2;
            f64 y2b = height_ratio / z2;

            // draw the wireframe quad
            draw_line(math::Line(screen_center_w + x1, screen_center_h + y1a,
                                 screen_center_w + x2, screen_center_h + y2a),
                      pixel(0x44, 0x88, 0x44));

            draw_line(math::Line(screen_center_w + x1, screen_center_h + y1b,
                                 screen_center_w + x2, screen_center_h + y2b),
                      pixel(0x44, 0x88, 0x44));

            draw_line(math::Line(screen_center_w + x1, screen_center_h + y1a,
                                 screen_center_w + x1, screen_center_h + y1b),
                      pixel(0x44, 0x88, 0x44));

            draw_line(math::Line(screen_center_w + x2, screen_center_h + y2a,
                                 screen_center_w + x2, screen_center_h + y2b),
                      pixel(0x44, 0x88, 0x44));
        }
    }
}

void Renderer::update_screen() {
    YSDLCHECK(SDL_RenderPresent(renderer));
}

void Renderer::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_map();

    update_screen();
}

Renderer::~Renderer() {
    if(renderer) {
        SDL_DestroyRenderer(renderer);
        LOGFMT(PROJNAME, "renderer", "destroyed SDL renderer");
    }
}

}  // namespace y