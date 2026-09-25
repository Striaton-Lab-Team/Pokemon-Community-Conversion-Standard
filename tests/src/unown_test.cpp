#include "catch_amalgamated.hpp"
#include "GBPokemon.h"
#include "Gen1Pokemon.h"
#include "Gen2Pokemon.h"
#include "Gen3Pokemon.h"
TEST_CASE("Full Unown test - make sure every DV set is valid", "[unit][gen1][pokemonparsing]")
{
    PokemonTables table;
    // This is easier than creating an Unown from scratch
    static const byte cyndaquil_data[] = {
        0x9B, 0x00, 0x21, 0x2B, 0x6C, 0x00, 0x1D, 0x29, 0x00, 0x00, 0xCD, 0x00, 0x32, 0x00, 0x41, 0x00,
        0x40, 0x00, 0x2B, 0x00, 0x2C, 0x59, 0x7B, 0x21, 0x1E, 0x14, 0x00, 0x4C, 0x00, 0x85, 0x01, 0x06};
    const byte cyndaquil_name[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x8A, 0x50}; // ABCDEFGHIJ
    const byte cyndaquil_ot[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x8A, 0x50}; // ABCDEFGHIJ
    static const byte cyndaquil_id = 0x9B;

    Gen2Pokemon unown(ENGLISH, &table);
    unown.loadData(ENGLISH, cyndaquil_data, cyndaquil_name, cyndaquil_ot, cyndaquil_id);

    Gen3Pokemon converted(&table);
    unown.setSpeciesIndexNumber(201);

    for (int dvs = 0; dvs < (1 << 16); dvs++)
    {
        for (int i = 0; i < 4; i++)
        {
            unown.setDV((Stat)(i + 1), (dvs >> (4 * i)) & 0b1111);
        }
        INFO("Unown conversion failed on DV combination: " << dvs);
        CHECK(unown.convertToGen3(&converted, LEGAL));
    }
}

TEST_CASE("Full Gender test - make sure every DV set is valid for genders", "[unit][gen1][pokemonparsing]")
{
    PokemonTables table;
    // This is easier than creating a mon from scratch
    static const byte cyndaquil_data[] = {
        0x9B, 0x00, 0x21, 0x2B, 0x6C, 0x00, 0x1D, 0x29, 0x00, 0x00, 0xCD, 0x00, 0x32, 0x00, 0x41, 0x00,
        0x40, 0x00, 0x2B, 0x00, 0x2C, 0x59, 0x7B, 0x21, 0x1E, 0x14, 0x00, 0x4C, 0x00, 0x85, 0x01, 0x06};
    const byte cyndaquil_name[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x8A, 0x50}; // ABCDEFGHIJ
    const byte cyndaquil_ot[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x8A, 0x50}; // ABCDEFGHIJ
    static const byte cyndaquil_id = 0x9B;

    #define NUM_GENDER_TESTS 11
    const byte ids_for_genders[11] = {
        HITMONLEE,  // 0:1
        BULBASAUR,  // 1:7
        GROWLITHE,  // 1:3
        CATERPIE,   // 1:1
        CLEFAIRY,   // 3:1
                    // 7:1 does not exist in Gen 1/2
        CHANSEY,    // 1:0
        MAGNEMITE,  // 0:0
        // And then the Nidos because they're special
        NIDORAN_M,
        NIDORAN_F,
        // Plus Ditto as an unbreedable
        DITTO,
        // And Mewtwo as a static encounter
        MEWTWO, 
    };

    for (int index = 0; index < NUM_GENDER_TESTS; index++)
    {
        Gen2Pokemon mon(ENGLISH, &table);
        mon.loadData(ENGLISH, cyndaquil_data, cyndaquil_name, cyndaquil_ot, cyndaquil_id);

        Gen3Pokemon converted(&table);
        mon.setSpeciesIndexNumber(ids_for_genders[index]);

        for (int dvs = 0; dvs < (1 << 16); dvs++)
        {
            for (int i = 0; i < 4; i++)
            {
                mon.setDV((Stat)(i + 1), (dvs >> (4 * i)) & 0b1111);
            }
            INFO("Gender conversion failed on DV and Pokemon Index combination: " << dvs << "/" << index);
            CHECK(mon.convertToGen3(&converted, LEGAL));
        }
    }
}