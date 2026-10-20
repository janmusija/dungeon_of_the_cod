# core
- chunk loading and generation
- proper spawning
- player association to a creature, and movement
  - swimming and such
- autonomous entities
  - enemy ai and pathing
- dungeon generation
  - dungeon placement
  - cell placement
  - proper integration into chunks
- saving and loading (should mostly be  covered by proper chunkloading anyway)
- status effects
  - templateable poison effects rather than a fixed one (-> VX)
- day night cycle
- skills

# mechanics
- creature factions

# structures
- wheels:
  - north wheel:
  - south wheel:
  - east wheel:
  - west wheel: the wheel associated with psychic damage and mind control mobs. usually this is the Most Deathful

# damage types
(not a fixed list just a list of the ones I feel are reasonable to start with)
- edge (physical damage type)
  - inflicted by sharp objects, e.g. knives, arrows, swords...
  - good against things made of soft tissue
  - not very effective versus hard things or the undead
- blunt (also physical)
  - inflicted by heavy objects, e.g. rocks, maces, hammers...
  - pretty uniformly effective against anything corporeal
- fire
  - probably self explanatory
  - not very effective if you are not flammable
  - often comes with associated status effect
- ice
  - probably self explanatory
  - often comes with associated status effect
- psychic
  - usually very effective against things with minds
  - totally without effect against mindless entities
  - weaker against entities with strong mental defenses
- magic
  - generally bypasses regular physical armor
  - not as effective against other magic wielders
- electric
  - probably to some extent in a similar boat to magic. often associated with status effect
  - probably most effective against robotic foes?
- holy
  - good against undead, werewolves, demons
  - portion of damage dealt by silver weapons is holy by default

# creature type ideas
## passive/neutral
### playable creature types
- human. 
- horse. (haha hope you dont mind lacking hands)
- goblin.
- dwarf.
- elf.

### nonplayable creature types
(various animals)

## hostile
obvious/specific ideas:
- gnome. strong enemy; mauls you with hit and run tactics and its absurd damage stat.
- wazir. simple enemy, can only move orthogonally
- zombie. basic undead enemy. invulnerable to psychic damage, but weak to holy.
- demons and such:
  - procedurally generated demon types a la df. particularly strong procedural demons are archdemons.
- angels (angels are god's demons)
  - procedurally generated angels exist; as do archangels.
- wizards: here's a sketch, subject to change: all are resistant to magic and associated damage type, and have ranged attacks and such. 
  - fire wizard. resistant to magic and fire damage.
  - ice wizard. resistant to magic and ice damage.
  - cleric (a cleric is just a holy wizard). resistant to magic and holy damage.
  - psychic wizard (the most !!fun!! kind of wizard). you probably first encounter these at the west wheel. resistant to magic and psychic damage.
  - electric wizard. resistant to magic and electric damage.
- the duck varietals (aero/geo/hydro/pyroducks, maybe electro and metaloduck too):

nonspecific ideas that just deserve to be things:
- fog animal
- dendrogaster
- cççcçcç (outside)
- dreadful eye (outside)
- lightbulb muncher?

## minibosses
(a priori the only distinction from bosses is they generate multiple times in the world)
- Minotaur [could consider: what type of creature this is a hybrid of with human varies]. Generates in labyrinths
- Wise One (procedurally generated)

## bosses
(each boss appears only once in world)
- god [heaven boss]. He lazes around on his marble throne until challenged, of course.
- satan [hell boss]. I imagine you waltz into her cast iron throne room and she reluctantly agrees to fight only once you threaten her.
- cod emperor [endgame boss]
- 4x Master of Nim [a puzzle boss]
- the horsemen of the apocalypse (undead), maybe?
- otzi the iceman
  - just hidden somewhere in some mountain biome. not easy to find
- Gnome Anne [gnome boss]. clearly she possesses a unique legendary item, [the Wand of Death](<https://nethackwiki.com/wiki/Gnome_With_the_Wand_of_Death>).
- 