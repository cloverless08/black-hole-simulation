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
    int m_nDims;
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
    if (m_nDims != rhs.m_nDims) {
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
VectorMath<T> VectorMath<T>::operator- (const VectorMath<T> &rhs) const {
    if (m_nDims != rhs.m_nDims) {
        throw std::invalid_argument("Vector dimensiobs do not match");
    }

    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) - rhs.m_vectorData.at(i));
    }

    VectorMath<T> result(resultData);
    return result;
}

template <class T>
VectorMath<T> VectorMath<T>::operator* (T &rhs) const {

    // scalar multiplication
    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) * rhs);
    }

    VectorMath<T> result(resultData);
    return result;
}

// friend function
// -----------------------

template <class T>
VectorMath<T> operator* (const T &lhs, const VectorMath<T> &rhs) {

    std::vector<T> resultData;
    for (int i = 0; i < rhs.m_nDims; ++i) {
        resultData.push_back(rhs.m_vectorData.at(i) * lhs);
    }

    VectorMath<T> result(resultData);
    return result;
}

// static functions
// ------------------------

// vector dot product
template <class T>
T VectorMath<T>::dot(const VectorMath<T> &a, const VectorMath<T> &b) {
    if (a.m_nDims != b.m_nDims) {
        throw std::invalid_argument("Vector dimensions do not match");
    }

    T sum = static_cast<T>(0.0);
    for (int i = 0; i < a.m_nDims; ++i) {
        sum += a.m_vectorData.at(i) * b.m_vectorData.at(i);
    }

    return sum;
}

// vector cross product
template <class T>
VectorMath<T> VectorMath<T>::cross(const VectorMath<T> &a, const VectorMath<T> &b) {

    if (a.m_nDims != b.m_nDims) { // vector dimensions must match
        throw std::invalid_argument("Vector dimensios do not match");
    }

    if (a.m_nDims != 3) { // vector dimensions must equal 3
        throw std::invalid_argument("Cross product can only be computed for 3d vectors");
    }

    // actually compute the cross product
    std::vector<T> resultData;
    resultData.push_back((a.m_vectorData.at(1) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(1)));
    resultData.push_back(-((a.m_vectorData.at(0) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(0))));
    resultData.push_back((a.m_vectorData.at(0) * b.m_vectorData.at(1)) - (a.m_vectorData.at(1) * b.m_vectorData.at(0)));

    VectorMath<T> result(resultData);
    return result;

}