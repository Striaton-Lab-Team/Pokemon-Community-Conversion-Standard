#ifndef POKEBOX_H
#define POKEBOX_H

#include "Gen1Pokemon.h"
#include "Gen2Pokemon.h"
#include "Gen3Pokemon.h"

class PokeBox // Stores up to 30 Pokemon in a box
{
private:
    void convertPkmn(PokemonTables *table, int index);
    Pokemon *boxStorage[30];
    Pokemon *nullMon;
    int currIndex;

public:
    PokeBox();
    bool addPokemon(Pokemon *currPkmn);
    Pokemon *getPokemon(int index);
    GBPokemon *getGBPokemon(int index);
    Gen3Pokemon *getGen3Pokemon(int index);
    bool removePokemon(int index);
    void reset();
    void loadData(int generation, Language nLang, const byte nDataArray[]);
    void convertAll(PokemonTables *table);
    int getNumInBox();
    int getNumValid();
    bool stabilize_mythical;

    bool getContainsMythical();
    bool getContainsInvalid();
    bool getContainsMissingNo();

#if ON_GBA
    bool getHasNewPkmn();
#else
    void print(PokemonTables *pokeTable, std::ostream &os);
    std::string printDataArray();
#endif
};

#endif