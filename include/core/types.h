#ifndef TYPES_H
#define TYPES_H

#include <defines.h>
#include <logger.h>
#include <error.h>

#define MAX_POLYS 10
#define MAX_VERTS 8

namespace y {

namespace math {

struct vec2
{
    f64 x = 0.0, y = 0.0;
    vec2(f64 x, f64 y) : x(x), y(y) {}
    vec2() {}

    // vector addition/subtraction
    vec2 operator+(vec2 const& rhs) const { return vec2(x + rhs.x, y + rhs.y); }
    vec2 operator-(vec2 const& rhs) const { return vec2(x - rhs.x, y - rhs.y); }

    // component-wise multiplication
    vec2 operator*(vec2 const& rhs) const { return vec2(x * rhs.x, y * rhs.y); }

    // scalar multiplication
    vec2 operator*(f64 mult) const { return vec2(x * mult, y * mult); }
};

struct Line
{
    vec2 p1, p2;

    Line(vec2 p1, vec2 p2) : p1(p1), p2(p2) {}
    Line(f64 ax, f64 ay, f64 bx, f64 by) : p1(vec2(ax, ay)), p2(vec2(bx, by)) {}

    tuple<f64, f64, f64, f64> get() {
        return std::make_tuple(p1.x, p1.y, p2.x, p2.y);
    }
};

struct Polygon
{
    vector<vec2> verts;
    f64 height;
    f64 curr_dist;
};

struct ScreenSpacePoly
{
    vec2 vert[4];
    f64 dist_from_cam;
    i32 planeid_in_poly;
};
}  // namespace math

namespace world {

struct Camera
{
    math::vec2 cam_pos;
    math::vec2 old_cam_pos;

    f64 cam_angle;
    f64 step_wave;

    Camera() {}
    Camera(f64 posx, f64 posy, f64 angle)
        : cam_pos(math::vec2(posx, posy)), cam_angle(angle) {}
};

}  // namespace world

}  // namespace y

#endif  // TYPES_H