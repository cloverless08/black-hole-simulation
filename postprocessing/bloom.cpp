//
// Created by cdemin on 11/20/26.
//

#include "postprocessing.h"

// definition of defeault constructor
postprocessing::Bloom::Bloom() {

}

// definition of default destructor
postprocessing::Bloom::~Bloom() {

}

std::vector<uint32_t> postprocessing::Bloom::ApplyBloom(int width, int height, std::vector<uint32_t> inputBuffer, double intensity) {
    for (x = 0; x < width; ++x) {
        for (y = 0; y < height; ++y) {
            // repeats for every pixel in buffer, applies effect (? (idk how that works (yet)))
        }
    }
}
