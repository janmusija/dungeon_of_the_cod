//
// worldgen/structure/labyrinth.h
// 2026-10-18
// dungeon_of_the_cod
//

#ifndef struc_labyrinth_h
#define struc_labyrinth_h

/*

The labyrinth is a special dungeon home to a Minotaur, featuring a confusing, tangled maze.

*/

/*
principle:
- every floor is a maze (something like a spanning tree of a lattice, I guess. Build via kruskal's algorithm, disjoint set data structure, etc)
- maze floors are themselves linked by a network of stairs, in some decidedly noneuclidedan arrangement
- when you leave a floor, associated maze shifts slightly (i.e. cut tree in some random edge then reglue a different one between the two disjoint connected components this creates)
- minotaur generates on one of the floors; other baddies also do so throughout ofc
*/

#endif