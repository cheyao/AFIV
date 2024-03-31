#include <fstream>

#include "util/log.h"
#include "formats/bmp.h"

namespace formats {

int BMP::loadBMP(std::string s, SDL_Surface* surface) {
    LOG(VERBOSE, "BMP: Loading BMP file: %s\n", s.c_str());
    std::ifstream file(s, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        LOG(ERROR, "BMP: Failed to open file %s\n", s.c_str());
        return 1;
    }

    file.close();

    return 0;
}

} // namespace formats
