//
// item/item.h
// 2026-10-18
// dungeon_of_the_cod
//

#ifndef item_h
#define item_h
#include <string>
#include "render/render.h"

/*

*/

class Item{
    public:
    std::string name;
    std::string type;

    Fancy_Char* symb;
};

#endif