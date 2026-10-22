//
// creature/creature_default_data.h
// 2026-10-21
// dungeon_of_the_cod
//

#ifndef creature_default_data_h
#define creature_default_data_h
#include <unordered_map>
#include "render/render.h"

namespace defaults {
    inline Fancy_Char default_char('@',15);

    inline std::unordered_map<std::string,float> base_resistances =
    {{"edge",1.0},{"blunt",0.5},{"fire",1.0},{"ice",1.0},{"psychic",1.0},{"magic",1.0},{"electric",1.0},{"holy",1.0}};

    inline std::unordered_map<std::string,float> demon_resistances =
    {{"edge",1.0},{"blunt",0.5},{"fire",0.0},{"ice",1.1},{"psychic",1.0},{"magic",0.5},{"electric",1.0},{"holy",1.7}};

    inline std::unordered_map<std::string,float> angel_resistances =
    {{"edge",1.0},{"blunt",0.5},{"fire",1.0},{"ice",1.0},{"psychic",1.0},{"magic",0.6},{"electric",1.0},{"holy",0.0}};

    inline std::unordered_map<std::string,float> zombie_resistances =
    {{"edge",0.7},{"blunt",0.7},{"fire",1.0},{"ice",1.0},{"psychic",0.0},{"magic",1.0},{"electric",1.0},{"holy",2.0}};
}

#endif