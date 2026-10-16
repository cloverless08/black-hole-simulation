//
// Created by cdemin on 10/15/26.
//

#pragma once

#include "main_utils.h"
#include <iostream>
#include <cmath>
#include <vector>

template <class T>

class VectorMath {
public:
    // default constructors/deconstructors
    VectorMath();

    VectorMath(std::vector<T> input);

    ~VectorMath();

    // basic functions
    int GetNumDims();

    T GetElement(int i);

    // operation functions
};