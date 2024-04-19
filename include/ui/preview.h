#ifndef PREVIEW_H
#define PREVIEW_H
#pragma once

#include "formats/image.h"
#include <SDL2/SDL.h>

namespace ui {

class Preview {
      private:
      public:
        void draw(SDL_Surface* dstSurface, SDL_Rect* dstRect, formats::Image* image);
};

} // namespace ui

#endif // PREVIEW_H
