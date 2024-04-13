#ifndef BMP_H
#define BMP_H
#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace formats {

class BMP {
      private:
      public:
        // Return 0 on success
        int static loadBMP(std::string s, SDL_Surface*& surface);
};

} // namespace formats

#endif // BMP_H
