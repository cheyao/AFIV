#include <SDL2/SDL.h>

#include "formats/image.h"
#include "ui/preview.h"

namespace ui {

void Preview::draw(SDL_Surface* dstSurface, SDL_Rect* dstRect, formats::Image* image) {
	// Resize image
	SDL_BlitSurface(image->mSurface, NULL, dstSurface, dstRect);
}

} // namespace ui
