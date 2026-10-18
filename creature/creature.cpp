//
// creature.cpp
// 2026-10-17
// dungeon_of_the_cod
//


#include "creature/creature.h"
#include <cmath>

void Creature::damage(std::unordered_map<std::string,uint32_t> & damage_vector){
    if (resistances){
        // nonnull resistances set
        for (auto it = damage_vector.begin(); it != damage_vector.end(); it++){
            if (auto search = resistances->find(it->first); search != resistances->end()){
                // apply damage multipled by resistance
                hp -= static_cast<int>(std::floor((it->second) * (search->second)));
            } else {
                // apply damage at full multiplication
                hp -= it->second;
            }
        }
    } else {
        // default: apply each damage
        for (auto it = damage_vector.begin(); it != damage_vector.end(); it++){
            hp -= it->second;
        }
    }
}