#ifndef MAP_H
#define MAP_H

#include <defines.h>
#include <logger.h>
#include <error.h>
#include <core/types.h>

using std::ifstream;
using std::stringstream;

namespace y::world {

class Map
{
    private:
    string filepath;  // path to map file
    vector<y::math::Polygon> polygons;

    void load();

    public:
    Map() {}
    Map(string filepath);

    inline void set_map_file(string filepath) { this->filepath = filepath; }

    // getters
    const vector<y::math::Polygon>& get_polygons() const { return polygons; }
};

}  // namespace y::world

#endif  // MAP_H