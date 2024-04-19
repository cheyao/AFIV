#include <cstdint>
#include <fstream>

#include "formats/image.h"
#include "formats/ppm.h"
#include "util/log.h"

namespace formats {

// Sorts and finds the image processor
Image* openImage(std::string path) {
        uint64_t signature1, signature2;
        Image* outputImage = nullptr;

        LOG(VERBOSE, "Image: Loading file: %s\n", path.c_str());
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file.is_open()) {
                LOG(ERROR, "Image: Failed to open file: %s\n", path.c_str());
                throw "Image: Failed to open file";
        }
        file.read((char*)&signature1, sizeof(signature1));
        file.read((char*)&signature2, sizeof(signature2));

        LOG(VERBOSE, "Image: signature : 0x%016x, 0x%016x\n", signature1, signature2);

        // BMP: 0x42 0x4D (BM) at offset 0
        if ((signature1 & 0x000000000000FFFF) == 0x4D42) {
                LOG(VERBOSE, "Image: File is BMP\n");
                // formats::BMP::loadBMP(s, mSurface);
        }

        if ((signature1 & 0x000000000000FFFF) == 0x3650) {
                LOG(VERBOSE, "Image: File is PPM\n");
                outputImage = new PPM();
		// TODO: Check if there is another pic
        }

        if (outputImage != nullptr) {
                file.clear();
                file.seekg(0);
                outputImage->loadImage(file);
        } else {
                LOG(VERBOSE, "Image: Unable to recognise image.\n");
        }
	file.close();
        return outputImage; // nullptr if format not found
}

} // namespace formats
