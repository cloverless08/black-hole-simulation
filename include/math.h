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

    // friend function
    template <class U> friend VectorMath<U> operator* (const U lhs, const VectorMath<U> &rhs);

    // static functions
    static T dot(const VectorMath<T> &a, const VectorMath<T> &b);
    static VectorMath<T> cross(const VectorMath<T> &a, const VectorMath<T> &b);

private:
    std::vector<T> m_vectorData;
    int M_nDims;
};

// constuctor and deconstructor functions
// ----------------------------------------

template <class T>
VectorMath<T>::VectorMath(std::vector<T> input) {
    m_nDims = input.size();
    m_vectorData = input;
}

template <class T>
VectorMath<T>::~VectorMath() {} // empty deconstructor

template <class T>
int VectorMath<T>::GetNumDims() {
    return m_nDims;
}

// element math_errhandling
//--------------------------------

template<class T>
T VectorMath<T>::GetElement(int i) {
    return m_vectorData[i];
}

// overloaded operators
// -----------------------------
template <class T>
VectorMath<T> VectorMath<T>::operator+ (const VectorMath<T> &rhs) const {
    if (m_nDims != rhs.nDims) {
        throw std::invalid_argument("Vector dimensiobs do not match");
    }

    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) + rhs.m_vectorData.at(i));
    }

    VectorMath<T> result(resultData);
    return result;
}

template <class T>
VectorMath<t> VectorMath<T>::operator- (const VectorMath<T> &rhs) const {
    if (m_nDims != rhs.nDims) {
        throw std::invalid_argument("Vector dimensiobs do not match");
    }

    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) - rhs.m_vectorData.at(i));
    }

    VectorMath<T> result(resultData);
    return result;
}

