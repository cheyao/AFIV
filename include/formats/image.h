#ifndef IMAGE_H
#define IMAGE_H
#include <SDL2/SDL_surface.h>
#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace formats {

/*
 * Generic Image class
 * Sorts the requests and unifies all to the same surface
 */
class Image {
      private:
        int w, h;

      public:
        // Virtual destructor
        virtual ~Image() {
                if (mSurface != nullptr)
                        SDL_FreeSurface(mSurface);
        }

        virtual void loadImage(std::ifstream& fileStream) = 0;
        int getWidth() const { return w; };
        int getHeight() const { return h; };
	
        SDL_Surface* mSurface;
};

Image* openImage(std::string path);

} // namespace formats

#endif // IMAGE_H
