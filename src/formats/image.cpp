#include <cstdint>
#include <fstream>

#include "formats/bmp.h"
#include "formats/image.h"
#include "util/log.h"

namespace formats {

Image::Image() : mSurface{nullptr} {}

// Sorts and finds the image processor
int Image::loadImage(std::string s) {
    uint64_t signature1, signature2;

    LOG(VERBOSE, "Image: Loading file: %s\n", s.c_str());
    std::ifstream file(s, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        LOG(ERROR, "Image: Failed to open file: %s\n", s.c_str());
        throw "Image: Failed to open file";
    }
    file.read((char*)&signature1, sizeof(signature1));
    file.read((char*)&signature2, sizeof(signature2));
    file.close();
    LOG(VERBOSE, "Image: signature : 0x%016x, 0x%016x\n", signature1, signature2);

    // BMP: 0x42 0x4D (BM) at offset 0
    if ((signature1 & 0x000000000000FFFF) == 0x4D42) {
        LOG(VERBOSE, "Image: File is BMP\n");
        return formats::BMP::loadBMP(s, mSurface);
    }

    LOG(VERBOSE, "Image: Unable to recognise image.\n");
    return 1; // Format not found
}

Image::~Image() {
    if (mSurface != nullptr)
        SDL_FreeSurface(mSurface);
}

} // namespace formats