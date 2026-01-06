#include <world/map.h>

namespace y::world {

void Map::load() {
    ifstream file(filepath);

    if(!file.is_open())
        YTHROWT(y::ErrType::Asset, "couldn't load map file: " + filepath);

    LOGFMT(PROJNAME, "MAP", "Parsing world data: ", filepath);

    string line;
    y::math::Polygon curr_poly;
    bool building_poly = false;

    while(std::getline(file, line)) {
        stringstream ss(line);
        string token;

        // skip empty lines
        if(line.empty())
            continue;

        ss >> token;

        // skip comments
        if(token[0] == '#')
            continue;

        if(token == "height") {
            // start a new polygon
            curr_poly.verts.clear();

            f64 h;
            if(ss >> h) {
                curr_poly.height = h;
                building_poly    = true;
            }
        } else if(token == "end") {
            // validate and push
            if(building_poly && !curr_poly.verts.empty()) {
                polygons.push_back(curr_poly);
            }
            building_poly = false;
        } else if(building_poly) {
            // parsing coordinates (x y)
            // reset stream to parse the full line as two doubles
            std::stringstream coordStream(line);
            f64 x, y;
            if(coordStream >> x >> y) {
                curr_poly.verts.push_back({x, y});
            }
        }
    }

    file.close();

    LOGFMT(PROJNAME, "map", "successfully loaded ", polygons.size(),
           " polygons from map file: ", CYAN_TEXT(filepath));
}

Map::Map(string filepath) : filepath(filepath) {
    load();
}

}  // namespace y::world
