#include "texture.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <SDL2/SDL.h>
#include <array>

namespace {
constexpr std::array<SDL_Color, 256> paletteColors = {
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x00},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x01},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x02},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x03},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x04},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x05},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x06},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x07},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x08},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x09},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x0A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x0B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x0C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x0D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x0E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x0F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x10},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x11},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x12},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x13},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x14},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x15},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x16},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x17},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x18},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x19},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x1A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x1B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x1C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x1D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x1E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x1F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x20},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x21},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x22},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x23},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x24},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x25},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x26},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x27},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x28},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x29},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x2A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x2B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x2C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x2D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x2E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x2F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x30},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x31},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x32},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x33},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x34},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x35},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x36},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x37},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x38},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x39},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x3A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x3B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x3C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x3D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x3E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x3F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x40},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x41},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x42},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x43},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x44},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x45},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x46},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x47},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x48},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x49},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x4A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x4B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x4C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x4D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x4E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x4F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x50},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x51},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x52},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x53},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x54},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x55},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x56},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x57},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x58},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x59},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x5F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x60},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x61},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x62},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x63},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x64},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x65},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x66},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x67},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x68},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x69},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x6A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x6B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x6C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x6D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x6E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x6F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x70},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x71},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x72},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x73},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x74},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x75},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x76},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x77},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x78},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x79},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x7A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x7B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x7C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x7D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x7E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x7F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x80},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x81},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x82},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x83},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x84},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x85},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x86},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x87},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x88},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x89},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x8A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x8B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x8C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x8D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x8E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x8F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x90},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x91},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x92},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x93},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x94},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x95},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x96},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x97},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x98},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x99},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x9A},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x9B},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x9C},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x9D},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x9E},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0x9F},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA0},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA1},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA2},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA3},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA4},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA5},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA6},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA7},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA8},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xA9},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xAA},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xAB},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xAC},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xAD},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xAE},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xAF},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB0},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB1},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB2},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB3},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB4},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB5},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB6},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB7},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB8},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xB9},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xBA},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xBB},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xBC},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xBD},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xBE},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xBF},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC0},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC1},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC2},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC3},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC4},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC5},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC6},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC7},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC8},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xC9},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xCA},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xCB},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xCC},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xCD},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xCE},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xCF},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD0},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD1},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD2},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD3},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD4},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD5},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD6},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD7},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD8},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xD9},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xDA},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xDB},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xDC},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xDD},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xDE},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xDF},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE0},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE1},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE2},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE3},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE4},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE5},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE6},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE7},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE8},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xE9},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xEA},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xEB},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xEC},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xED},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xEE},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xEF},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF0},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF1},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF2},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF3},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF4},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF5},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF6},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF7},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF8},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xF9},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFA},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFB},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFC},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFD},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFE},
    SDL_Color{.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF},
};
SDL_Palette *palette = nullptr;

enum class InputType { Index, Codepoint };

GlyphTextureInfo DoCreateTexture(SDL_Renderer *renderer,
                                 const stbtt_fontinfo &info, const int &input,
                                 const InputType &type, const float &scale) {
  int bearing;
  int advance;
  int c_x1, c_y1, c_x2, c_y2;

  switch (type) {
  case InputType::Codepoint:
    stbtt_GetCodepointHMetrics(&info, input, &advance, &bearing);
    stbtt_GetCodepointBitmapBox(&info, input, scale, scale, &c_x1, &c_y1, &c_x2,
                                &c_y2);

    break;

  case InputType::Index:
    stbtt_GetGlyphHMetrics(&info, input, &advance, &bearing);
    stbtt_GetGlyphBitmapBox(&info, input, scale, scale, &c_x1, &c_y1, &c_x2,
                            &c_y2);

    break;
  }

  advance = static_cast<int>(roundf(advance * scale));
  bearing = static_cast<int>(roundf(bearing * scale));
  int y = c_y1;

  int width = c_x2 - c_x1;
  int height = c_y2 - c_y1;

  auto surface = SDL_CreateRGBSurfaceWithFormat(
      0, width, height, SDL_BITSPERPIXEL(SDL_PIXELFORMAT_INDEX8),
      SDL_PIXELFORMAT_INDEX8);

  SDL_SetSurfacePalette(surface, palette);

  SDL_LockSurface(surface);
  unsigned char *bitmap = reinterpret_cast<unsigned char *>(surface->pixels);

  switch (type) {
  case InputType::Codepoint:
    stbtt_MakeCodepointBitmap(&info, bitmap, width, height, surface->pitch,
                              scale, scale, input);
    break;

  case InputType::Index:
    stbtt_MakeGlyphBitmap(&info, bitmap, width, height, surface->pitch, scale,
                          scale, input);
    break;
  }

  SDL_UnlockSurface(surface);

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture != nullptr) {
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  }

  SDL_FreeSurface(surface);

  return {
      .texture = texture,
      .advance = advance,
      .dest = {bearing, static_cast<int>(y), width, height},
  };
}
}; // namespace

void InitGlyphTexture() {
  palette = SDL_AllocPalette(paletteColors.size());
  SDL_SetPaletteColors(palette, paletteColors.data(), 0, paletteColors.size());
}

void CleanUpGlyphTexture() { SDL_FreePalette(palette); }

GlyphTextureInfo CreateTextureFromCodePoint(SDL_Renderer *renderer,
                                        const stbtt_fontinfo &info,
                                        const int &codepoint,
                                        const float &scale) {
  return DoCreateTexture(renderer, info, codepoint, InputType::Codepoint, scale);
}

GlyphTextureInfo CreateTextureFromIndex(SDL_Renderer *renderer,
                                    const stbtt_fontinfo &info,
                                    const int &index, const float &scale) {
  return DoCreateTexture(renderer, info, index, InputType::Index, scale);
}