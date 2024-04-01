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
    int w, h;

  public:
    // return 0 on sucess
    Image();
    ~Image();
    int loadImage(std::string s);
    SDL_Surface* getSurface() { return mSurface; };
    int getWidth() const { return w; };
    int getHeight() const { return h; };
};

} // namespace formats

#endif // IMAGE_H