#ifndef MAP_H
#define MAP_H

#include <defines.h>

namespace world {

// TODO: load maps using a custom file format
//          or use smth like TrenchBroom

constexpr i32 MAP_WIDTH  = 16;
constexpr i32 MAP_HEIGHT = 16;

class Map {
private:
    i32 world_map[MAP_HEIGHT][MAP_WIDTH];

public:
    Map();
};

} // namespace world

#endif // MAP_H