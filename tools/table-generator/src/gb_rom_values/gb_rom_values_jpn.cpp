#include "gb_rom_values/gb_rom_values.h"

const struct GB_ROM gb_rom_values_jpn[] = {
    {// JPN_GREEN
        .language = JPN_ID,
        .version = GREEN_ID,
        .generation = 1,
        .box_data_size = 0x566,
        .wCurrentBoxNum = 0xD51F,
        .wBoxDataStart = 0xD9B2},
    {// JPN_RED
        .language = JPN_ID,
        .version = RED_ID,
        .generation = 1,
        .box_data_size = 0x566,
        .wCurrentBoxNum = 0xD51F, 
        .wBoxDataStart = 0xD9B2},
    {// JPN_BLUE
        .language = JPN_ID,
        .version = BLUE_ID,
        .generation = 1,
        .box_data_size = 0x566,
        .wCurrentBoxNum = 0xD51F,
        .wBoxDataStart = 0xD9B2},
    {// JPN_YELLOW
        .language = JPN_ID,
        .version = YELLOW_ID,
        .generation = 1,
        .box_data_size = 0x566,
        .wCurrentBoxNum = 0xD51F,
        .wBoxDataStart = 0xD9B2},
    {// JPN_GOLD
        .language = JPN_ID,
        .version = GOLD_ID,
        .generation = 2,
        .box_data_size = 0x548,
        .wCurrentBoxNum = 0x01D8AF, // wCurBox
        .wBoxDataStart = 0x01AD10}, // sBox
    {// JPN_SILVER
        .language = JPN_ID,
        .version = SILVER_ID,
        .generation = 2,
        .box_data_size = 0x548,
        .wCurrentBoxNum = 0x01D8AF, // wCurBox
        .wBoxDataStart = 0x01AD10}, // sBox
    {// JPN_CRYSTAL
        .language = JPN_ID,
        .version = CRYSTAL_ID,
        .generation = 2,
        .box_data_size = 0x548,
        .wCurrentBoxNum = 0x01DB65, // wCurBox
        .wBoxDataStart = 0x01AD10}, // sBox
};

const u16 gb_rom_values_jpn_size = static_cast<u16>(sizeof(gb_rom_values_jpn) / sizeof(struct GB_ROM));