//

// Created by cdemin on 11/20/26.

//

#pragma once

#include <cstdint>
#include <vector>

namespace postprocessing {
    // adds bloom and better lighting to final rendered frame
    class Bloom {
    public:
        // default constructor and destructor
        Bloom();
        ~Bloom();

        std::vector<uint32_t> ApplyBloom(
        int width, int height,
        std::vector<uint32_t> inputBuffer, double intensity
            );
    private:
        double m_bloomIntensity = 1.0; // change(?)
    };

    // applies dithering effect to hide rendering artifacts
    class Dithering { // may or may not ever actually need this i guess
    public:
        // defauly constructor and destructor
        Dithering();
        ~Dithering();

        std::vector<uint32_t> ApplyDithering(
        int width, int height,
        std::vector<uint32_t> inputBuffer, double intensity
            );
    private:
        double m_ditheringIntensity = 1.0;
    };
}
