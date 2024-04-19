#ifndef PPM_H
#define PPM_H
#pragma once

#include <SDL2/SDL.h>

#include "formats/image.h"

namespace formats {

class PPM : public Image {
      public:
        void loadImage(std::ifstream& fileStream);
};

} // namespace formats

#endif
