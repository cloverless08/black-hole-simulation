//
// Created by cdemin on 8/25/26.
//

#include "main_utils.h"
#include <iostream>
#include <random>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#define newline "\n"

void TerminalInfoHeader() {
    std::cout << newline;
    std::cout << GREEN;
    std::cout << "====================================" << std::endl;
    std::cout << "      CSC1060 Black Hole Sim" << std::endl;
    std::cout << "        By Carrick De Min" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << GREEN;
    std::cout << newline;
}

// function for clean, dynamic console output with labels
int StrOut(const std::string& msg, std::string label) {
    if (label != "standard") {
        for (char &c : label) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c))); // changes string 'label' to all upper
        }
        if (label == "ERROR") {
            std::cout << RED << "[" + label + "] " << msg << RESET << std::endl; // output with label
        } else if (label == "WARN") {
            std::cout << YELLOW << "[" + label + "] " << msg << RESET << std::endl; // output with label
        } else if (label == "SETUP") {
            std::cout << CYAN << "[" + label + "] " << msg << RESET << std::endl; // output with label
        } else {
            std::cout << RESET << "[" + label + "] " << msg << RESET << std::endl; // output with custom label
        }
    } else {
        std::cout << RESET << msg << RESET<< std::endl; // output without label
    }

    return 0;
}

// generates random integer
int RandInt(int rangeMin, int rangeMax) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(rangeMin, rangeMax);
    return distr(gen);
}

void SetPixel(uint32_t* buffer, int width, int height, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        uint32_t color = (static_cast<uint32_t>(r) << 24) | (static_cast<uint32_t>(g) << 16) | (static_cast<uint32_t>(b) << 8) | a; // translates base-255 into proper color format
        buffer[(y * width) + x] = color;
    }
}

uint64_t randomUint64(int min, int max) {
    static std::random_device rndm;
    static std::mt19937 gen(rndm());

    std::uniform_int_distribution<int> distrib(min, max);

    return distrib(gen);
}
