//
// creature/types/humanoid.h
// 2026-10-25
// dungeon_of_the_cod
//

#ifndef creature_humanoid_h
#define creature_humanoid_h

#include "creature/creature.h"

namespace crtr{
    class Human : public Creature{
        public: 
        static uint32_t base_hp;
        static Fancy_Char base_symb;
        Human (uint32_t HP, short X, short Y, short Z, std::string CH_ID): Creature(HP, X, Y, Z, CH_ID){};
        void initialize_default_stats() {
            hp = base_hp; symb = &base_symb;
        }
    };

    class Elf : public Creature{
        public: 
        static uint32_t base_hp;
        static Fancy_Char base_symb;
        Elf (uint32_t HP, short X, short Y, short Z, std::string CH_ID): Creature(HP, X, Y, Z, CH_ID){};
        void initialize_default_stats() {
            hp = base_hp; symb = &base_symb;
        }
    };

    class Goblin : public Creature{
        public: 
        static uint32_t base_hp;
        static Fancy_Char base_symb;
        Goblin (uint32_t HP, short X, short Y, short Z, std::string CH_ID): Creature(HP, X, Y, Z, CH_ID){};
        void initialize_default_stats() {
            hp = base_hp; symb = &base_symb;
        }
    };
}

#endif