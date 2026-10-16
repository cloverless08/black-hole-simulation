//
// Created by cdemin on 10/15/26.
//

#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

// lets user create vectors of any type
template <class T>

class VectorMath {
public:
    // default constructors/deconstructors
    VectorMath();

    VectorMath(std::vector<T> input);

    ~VectorMath();

    // parameter and basic functions
    int GetNumDims(); // number of dims is set as data is added

    T GetElement(int i);

    // overloaded operators
    VectorMath<T> operator+ (const VectorMath<T> &rhs) const;
    VectorMath<T> operator- (const VectorMath<T> &rhs) const;
    VectorMath<T> operator* (T &rhs) const;
};