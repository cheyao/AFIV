#ifndef BMP_H
#define BMP_H
#pragma once

#include "formats/image.h"

namespace formats {

class BMP {
  private:

  public:
    // Return 0 on success
    int static loadBMP(std::string s, SDL_Surface* surface);
};

} // namespace formats

#endif // BMP_H