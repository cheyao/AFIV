#include <cstdint>
#include <fstream>

#include "formats/bmp.h"
#include "formats/general.h"
#include "util/log.h"

namespace formats {

typedef struct __attribute__((packed)) BitmapFileHeader {
        uint16_t signature;
        uint32_t size;
        uint32_t reserved;
        uint32_t offBits;
} BitmapFileHeader;

typedef struct __attribute__((packed)) BitmapInfoHeader {
        uint32_t size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bpp;
        uint32_t compression;
        uint32_t imageSize;
        uint32_t xppm;
        uint32_t yppm;
        uint32_t colorsUsed;
        uint32_t importantColors;
} BitmapInfoHeader;

typedef struct __attribute__((packed)) ColorTable {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t reserved;
} ColorTable;

int BMP::loadBMP(std::string s, SDL_Surface*& surface) {
        LOG(VERBOSE, "BMP: Loading BMP file: %s\n", s.c_str());
        std::ifstream file(s, std::ios::in | std::ios::binary);

        if (!file.is_open()) {
                LOG(ERROR, "BMP: Failed to open file %s\n", s.c_str());
                throw "BMP: Failed to open file";
        }

        BitmapFileHeader* header = new BitmapFileHeader;
        BitmapInfoHeader* infoHeader = new BitmapInfoHeader;

        file.seekg(0);
        file.read((char*)header, sizeof(BitmapFileHeader));
        file.seekg(sizeof(BitmapFileHeader));
        file.read((char*)infoHeader, sizeof(BitmapInfoHeader));

        if (header->signature != 0x4D42) {
                LOG(ERROR, "BMP: Uhhh this isn't supposed to happen! The magic number "
                           "should have been already checked.\n");
                throw "BMP: Uhhh this isn't supposed to happen! The magic number "
                      "should have been already checked.";
        }

        size_t fileSize = infoHeader->width * infoHeader->height * (infoHeader->bpp / 8);

        LOG(VERBOSE, "BMP: Loading image of %i size and %i bits\n", fileSize, infoHeader->bpp);

        char* buffer = new char[fileSize];
        file.seekg(header->offBits);
        file.read((char*)buffer, fileSize);

        surface = SDL_CreateRGBSurface(0, infoHeader->width, infoHeader->height, infoHeader->bpp, 0,
                                       0, 0, 0);
        if (surface == NULL) {
                LOG(ERROR, "BMP: Couldn't create surface, %s.\n", SDL_GetError());
                throw "BMP: Couldn't create surface";
        }

        SDL_LockSurface(surface);
        // Pixels are accesible

        SDL_UnlockSurface(surface);

        // Flip
        flipSurface(surface);

        file.close();

        return 0;
}

} // namespace formats
