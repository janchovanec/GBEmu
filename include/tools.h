#pragma once
#include <cstdint>

namespace Tools {
    inline uint8_t HalfCarryOnAddition(uint8_t a, uint8_t b)
    {
        return (((a & 0xf) + (b & 0xf)) & 0x10) << 1;
    }
    inline uint8_t HalfCarryOnAddition(uint8_t a, uint8_t b, uint8_t c)
    {
        return (((a & 0xf) + (b & 0xf) + (c & 0xf)) & 0x10) << 1;
    }
    inline uint8_t HalfCarryOnSubtraction(uint8_t a, uint8_t b)
    {
        return (((a & 0xf) - (b & 0xf)) & 0x10) << 1;
    }
    inline uint8_t HalfCarryOnSubtraction(uint8_t a, uint8_t b, uint8_t c)
    {
        return (((a & 0xf) - (b & 0xf) - (c & 0xf)) & 0x10) << 1;
    }
    inline uint8_t HalfCarryOnAddition16(uint16_t a, uint16_t b)
    {
        return (((a & 0xfff) + (b & 0xfff)) & 0x1000) >> 7;
    }
    inline uint8_t HalfCarryOnSubtraction16(uint16_t a, uint16_t b)
    {
        return (((a & 0xfff) - (b & 0xfff)) & 0x1000) >> 7;
    }
    // Set Z flag
    inline uint8_t ZeroFlag(uint8_t a)
    {
        return a == 0 ? 0b10000000 : 0;
    }
    inline uint8_t ZeroFlag16(uint16_t a)
    {
        return a == 0 ? 0b10000000 : 0;
    }
    // Set C flag
    inline uint8_t CarryOnAddition(uint8_t a, uint8_t b)
    {
        return (((a & 0xff) + (b & 0xff)) & 0x100) >> 4;
    }
    inline uint8_t CarryOnAddition(uint8_t a, uint8_t b, uint8_t c)
    {
        return (((a & 0xff) + (b & 0xff) + (c & 0xff)) & 0x100) >> 4;
    }
    inline uint8_t CarryOnSubtraction(uint8_t a, uint8_t b)
    {
        return (((a & 0xff) - (b & 0xff)) & 0x100) >> 4;
    }
    inline uint8_t CarryOnSubtraction(uint8_t a, uint8_t b, uint8_t c)
    {
        return (((a & 0xff) - (b & 0xff) - (c & 0xff)) & 0x100) >> 4;
    }
    inline uint8_t CarryOnAddition16(uint16_t a, uint16_t b)
    {
        return (((a & 0xffff) + (b & 0xffff)) & 0x10000) >> 12;
    }
    inline uint8_t CarryOnSubtraction16(uint16_t a, uint16_t b)
    {
        return (((a & 0xffff) - (b & 0xffff)) & 0x10000) >> 12;
    }
}