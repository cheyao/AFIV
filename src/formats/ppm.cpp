#include <SDL2/SDL.h>
#include <fstream>
#include <string>

#include "formats/ppm.h"
#include "util/log.h"

namespace formats {

void PPM::loadImage(std::ifstream& fileStream) {
	LOG(VERBOSE, "PPM: Loading Image.\n");
	
	// TODO: Plain PPM
	std::string magic;
	fileStream >> magic;

	if (magic != "P6") {
		LOG(ERROR, "PPM: Magic number not recognised");
		return;
	}

	int width, height, maxValue;
	fileStream >> width >> height >> maxValue;
	LOG(VERBOSE, "PPM: Loading image with demensions %ix%i. Max value: %i\n", width, height, maxValue);
	
	mSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
}

}
