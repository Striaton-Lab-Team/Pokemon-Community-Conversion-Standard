#include "pccs_utils.h"
#include <strings.h>

static const bool g_cpuLittleEndian = PCCSUtils::isCurrentCPULittleEndian();

// the attribute stuff is to make sure the compiler doesn't optimize this code away.
__attribute__((optimize("O0")))
bool PCCSUtils::isCurrentCPULittleEndian()
{
	short int word = 0x0001;
   char *byte = (char *) &word;
   return (byte[0] ? true : false);
}

u16 PCCSUtils::byteSwapUint16(u16 val)
{
    return __builtin_bswap16(val);
}

u32 PCCSUtils::byteSwapUint32(u32 val)
{
	return __builtin_bswap32(val);
}

u8* PCCSUtils::read(u8 *srcBuffer, u8 *dstBuffer, u32 bytesToRead)
{
    memcpy(dstBuffer, srcBuffer, bytesToRead);
    return srcBuffer + bytesToRead;
}

u8* PCCSUtils::write(const u8* srcBuffer, u8 *dstBuffer, u32 bytesToWrite)
{
    memcpy(dstBuffer, srcBuffer, bytesToWrite);
    return dstBuffer + bytesToWrite;
}

u8* PCCSUtils::readUint16(u8 *srcBuffer, u16& outBytes, Endianness fieldEndianness)
{
    if(!PCCSUtils::read(srcBuffer, (u8*)&outBytes, 2))
    {
        return nullptr;
    }

    if(fieldEndianness == Endianness::LITTLE && !g_cpuLittleEndian)
    {
        outBytes = PCCSUtils::byteSwapUint16(outBytes);
    }
    else if(fieldEndianness == Endianness::BIG && g_cpuLittleEndian)
    {
        outBytes = PCCSUtils::byteSwapUint16(outBytes);
    }
    return srcBuffer + 2;
}

u8* PCCSUtils::writeUint16(u8 *dstBuffer, u16 bytes, Endianness fieldEndianness)
{
    // when reading the data before, we might have done a byte swap. To undo it while writing, we just need to repeat it.
    if(fieldEndianness == Endianness::LITTLE && !g_cpuLittleEndian)
    {
        bytes = PCCSUtils::byteSwapUint16(bytes);
    }
    else if(fieldEndianness == Endianness::BIG && g_cpuLittleEndian)
    {
        bytes = PCCSUtils::byteSwapUint16(bytes);
    }
    PCCSUtils::write((u8*)&bytes, dstBuffer, 2);
    return dstBuffer + 2;
}

u8* PCCSUtils::readUint24(u8 *srcBuffer, u32& outByte, Endianness fieldEndianness)
{
    u8 bytes[3];

    if(!PCCSUtils::read(srcBuffer, bytes, 3))
    {
        return nullptr;
    }

    if(fieldEndianness == Endianness::LITTLE)
    {
        outByte = (((u32)bytes[2]) << 16) | (((u32)bytes[1]) << 8) | bytes[0];
    }
    else
    {
        outByte = (((u32)bytes[0]) << 16) | (((u32)bytes[1]) << 8) | bytes[2];
    }

    return srcBuffer + 3;
}

u8* PCCSUtils::writeUint24(u8 *dstBuffer, u32 bytes, Endianness fieldEndianness)
{
    u8 bytesToWrite[3];

    if(fieldEndianness == Endianness::LITTLE)
    {
        bytesToWrite[0] = (u8)(bytes & 0xFF);
        bytesToWrite[1] = (u8)((bytes & 0xFF00) >> 8);
        bytesToWrite[2] = (u8)((bytes & 0xFF0000) >> 16);
    }
    else
    {
        bytesToWrite[0] = (u8)((bytes & 0xFF0000) >> 16);
        bytesToWrite[1] = (u8)((bytes & 0xFF00) >> 8);
        bytesToWrite[2] = (u8)(bytes & 0xFF);   
    }

    PCCSUtils::write(bytesToWrite, dstBuffer, sizeof(bytesToWrite));
    return dstBuffer + 3;
}

u8* PCCSUtils::readUint32(u8 *srcBuffer, u32& outByte, Endianness fieldEndianness)
{
    if(!PCCSUtils::read(srcBuffer, (u8*)&outByte, 4))
    {
        return nullptr;
    }

    if(fieldEndianness == Endianness::LITTLE && !g_cpuLittleEndian)
    {
        outByte = PCCSUtils::byteSwapUint32(outByte);
    }
    else if(fieldEndianness == Endianness::BIG && g_cpuLittleEndian)
    {
        outByte = PCCSUtils::byteSwapUint32(outByte);
    }
    return srcBuffer + 4;
}

u8* PCCSUtils::writeUint32(u8 *dstBuffer, u32 bytes, Endianness fieldEndianness)
{
    // when reading the data before, we might have done a byte swap. To undo it while writing, we just need to repeat it.
    if(fieldEndianness == Endianness::LITTLE && !g_cpuLittleEndian)
    {
        bytes = PCCSUtils::byteSwapUint32(bytes);
    }
    else if(fieldEndianness == Endianness::BIG && g_cpuLittleEndian)
    {
        bytes = PCCSUtils::byteSwapUint32(bytes);
    }
    PCCSUtils::write((u8*)&bytes, dstBuffer, 4);
    return dstBuffer + 4;
}

void PCCSUtils::extractLehmerCode4(u32 n, u8 out[4])
{
    u32 pool[4] = {0, 1, 2, 3};

    // factorials: (digitsRemaining - 1)!
    // with digitsRemaining the number of digits remaining
    // after we picked the current one
    const u32 fact[4] = {6, 2, 1, 1};
    
    // fact[pos] tells you how many permutations each choice at this position represents.
    // using u32 because that's the native register size for a GBA. #perf
    for (u32 pos = 0; pos < 4; ++pos)
    {
        // n / fact[pos] = “which element to pick among the remaining elements”
        u32 pick = n / fact[pos];
        n %= fact[pos];

        out[pos] = pool[pick];

        // remove picked element from pool
        for (u32 i = pick; i < 3 - pos; ++i)
        {
            pool[i] = pool[i + 1];
        }
    }
}

int PCCSUtils::reverseIVToSeed(u16 first, u16 second, u32 *values, RNGMethod conversion, bool isEvent)
{
    // ABC_E has to reverse two steps instead of one, which is why we have different values for each
    u32 GBA_LCG_MULT = (conversion != ABC_E) ? 0x41C64E6D : 0xC2A29A69;
    u32 GBA_LCG_ADD  = (conversion != ABC_E) ? 0x00006073 : 0xE97E7B6A;

    u32 GBA_REV_STEP = (conversion != ABC_E) ? 0x000067D3 : 0x00003A89;
    u32 GBA_REV_PAT  = (conversion != ABC_E) ? 0x00000D3E : 0x00002E4C;
    u32 GBA_REV_INC  = (conversion != ABC_E) ? 0x00004034 : 0x05259D3A;

    constexpr u32 GBA_LCG_REVERSE_MULT = 0xEEB9EB65;
    constexpr u32 GBA_LCG_REVERSE_ADD  = 0x0A3561A1;

    int count = 0;
    
    for (int i = 0; i < 4; i++)
    {
        u32 firstState  = ((u32)first  << 16) | ((i >> 0) & 0b1) << 31;
        u32 secondState = ((u32)second << 16) | ((i >> 1) & 0b1) << 31;

        u32 diff = (secondState - firstState * GBA_LCG_MULT) >> 16;
        u32 low = ((((diff * GBA_REV_STEP) + GBA_REV_INC) >> 16) * GBA_REV_PAT) % GBA_REV_STEP;

        do
        {
            u32 state = firstState | low;
            u32 nextState = state * GBA_LCG_MULT + GBA_LCG_ADD;

            if ((nextState & 0xFFFF0000) == secondState)
            {
                u32 previousState = state * GBA_LCG_REVERSE_MULT + GBA_LCG_REVERSE_ADD;
                previousState = previousState * GBA_LCG_REVERSE_MULT + GBA_LCG_REVERSE_ADD;
                previousState = previousState * GBA_LCG_REVERSE_MULT + GBA_LCG_REVERSE_ADD; // Do it thrice so we get the seed
                if (conversion == A_CDE || conversion == AB_DE)
                {
                    previousState = previousState * GBA_LCG_REVERSE_MULT + GBA_LCG_REVERSE_ADD; // Do it again!
                }
                if(!isEvent || previousState < 0x10000) // If we have an event Pokemon, the seed needs to be 16 bits only.
                {
                    values[count++] = previousState;
                }
            }
            low += GBA_REV_STEP;

        } while (low < 0x10000);
    }
    return count;
}

Game PCCSUtils::determineGameType(const char* param)
{
#if !ON_GBA
    if(strcasecmp(param, "ruby") == 0)
    {
        return RUBY;
    }
    else if(strcasecmp(param, "sapphire") == 0)
    {
        return SAPPHIRE;
    }
    else if(strcasecmp(param, "emerald") == 0)
    {
        return EMERALD;
    }
    else if(strcasecmp(param, "firered") == 0)
    {
        return FIRERED;
    }
    else if(strcasecmp(param, "leafgreen") == 0)
    {
        return LEAFGREEN;
    }
#endif
    return GAME_UNKNOWN;
}

Language PCCSUtils::determineLanguage(const char* param)
{
#if !ON_GBA
    if(strcasecmp(param, "english") == 0)
    {
        return ENGLISH;
    }
    else if(strcasecmp(param, "japanese") == 0)
    {
        return JAPANESE;
    }
    else if(strcasecmp(param, "french") == 0)
    {
        return FRENCH;
    }
    else if(strcasecmp(param, "italian") == 0)
    {
        return ITALIAN;
    }
    else if(strcasecmp(param, "german") == 0)
    {
        return GERMAN;
    }
    else if(strcasecmp(param, "spanish") == 0)
    {
        return SPANISH;
    }
    else if(strcasecmp(param, "korean") == 0)
    {
        return KOREAN;
    }
#endif
    return LANGUAGE_UNKNOWN;
}