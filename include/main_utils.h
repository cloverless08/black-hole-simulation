
//
// Created by cdemin on 8/25/26.
//
#pragma once

#include <iostream>
#include <random>
#include <string>

// Added for std::toupper
#include <cctype>

#include "../qbLinearAlgebra/qbVector.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

#define newline "\n"


// declarations
// --------------

inline int StrOut(const std::string& msg = "Nothing to output (edit strOut() to fix)", std::string label = "standard");

inline int RandInt(int rangeMin, int rangeMax);

inline void SetPixel(uint32_t* buffer, int width, int height, int x, int y, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);

inline void TerminalInfoHeader();

inline int LengthInt(int p1, int p2);

inline double LengthDouble(int p1, int p2);

inline double Length3D(qbVector<double> point, qbVector<double> point2);

// definitions
// -----------------

inline void TerminalInfoHeader() {
    std::cout << newline;
    std::cout << GREEN;
    std::cout << "====================================" << std::endl;
    std::cout << "      CSC1060 Black Hole Sim" << std::endl;
    std::cout << "        By Carrick De Min" << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << RESET;
    std::cout << newline;
}

// function for clean, dynamic console output with labels
inline int StrOut(const std::string& msg, std::string label) {
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
inline int RandInt(int rangeMin, int rangeMax) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(rangeMin, rangeMax);
    return distribution(gen);
}

inline void SetPixel(uint32_t* buffer, int width, int height, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        uint32_t color = (static_cast<uint32_t>(r) << 24) | (static_cast<uint32_t>(g) << 16) | (static_cast<uint32_t>(b) << 8) | a; // translates base-255 into proper color format
        buffer[(y * width) + x] = color;
    }
}

inline int LengthInt(int p1, int p2) { // might change soon, dunno if this works in 3d
    return (p1 * p1 + p2 * p2);
}

inline double LengthDouble(int p1, int p2) {
    return (p1 * p1 + p2 * p2);
}

inline double Length3D(qbVector<double> point1, qbVector<double> point2) {
    if (point1.GetNumDims() != 3 || point2.GetNumDims() != 3) {
        std::cout << "ERROR: number of diensions must equal 3" << std::endl;
        return 10000.0;
    } else {
        double result;

        auto x1 = static_cast<double>(point1.GetElement(0));
        auto x2 = static_cast<double>(point2.GetElement(0));

        auto y1 = static_cast<double>(point1.GetElement(1));
        auto y2 = static_cast<double>(point2.GetElement(1));

        auto z1 = static_cast<double>(point1.GetElement(2));
        auto z2 = static_cast<double>(point2.GetElement(2));

        result = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2) + pow((z2-z1), 2));
        return result;
    }
}