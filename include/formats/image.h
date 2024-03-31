#ifndef IMAGE_H
#define IMAGE_H
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

  protected:
    SDL_Surface* mSurface;

  public:
    // return 0 on sucess
    int loadImage(std::string s);
    SDL_Surface* getSurface() { return mSurface; };
};

} // namespace formats

#endif // IMAGE_H