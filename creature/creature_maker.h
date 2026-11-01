//
// creature/creature_maker.h
// 2026-10-25
// dungeon_of_the_cod
//

#ifndef creature_maker_h
#define creature_maker_h

#include "creature/creature.h"
#include <memory>
// all creature types
#include "creature/types/humanoid.h"

std::unique_ptr<Creature> creature_maker(std::string typ,uint32_t HP,short X,short Y,short Z, std::string CH_ID){
    std::unique_ptr<Creature> ret;
        std::cout << typ << " spawning"<< std::endl;
    if (typ == "human"){
        std::cout << "aa" << std::endl;
        ret = std::make_unique<crtr::Human>(HP,X,Y,Z,CH_ID);
    } else {//default:
        std::cout << "bb" << std::endl;
        ret = std::make_unique<Creature>(HP,X,Y,Z,CH_ID);
    }

    return ret;
}

#endif