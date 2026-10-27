//
// Created by cdemin on 10/15/26.
//

#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

namespace math {
// lets user create vectors of any type
template <class T>

    class cdVector {
    public:
        // default constructors/deconstructors
        cdVector();

        cdVector(std::vector<T> input);

        ~cdVector();

        // parameter and basic functions
        int GetNumDims(); // number of dims is set as data is added

        T GetElement(int i);

        // overloaded operators
        cdVector<T> operator+ (const cdVector<T> &rhs) const;
        cdVector<T> operator- (const cdVector<T> &rhs) const;
        cdVector<T> operator* (T &rhs) const;

        // friend function
        template <class U> friend cdVector<U> operator* (const U lhs, const cdVector<U> &rhs);

        // static functions
        static T dot(const cdVector<T> &a, const cdVector<T> &b);
        static cdVector<T> cross(const cdVector<T> &a, const cdVector<T> &b);

    private:
        std::vector<T> m_vectorData;
        int m_nDims;
    };
}

// constructor and deconstructor functions
// ----------------------------------------

template <class T>
cdVector<T>::cdVector(std::vector<T> input) {
    m_nDims = input.size();
    m_vectorData = input;
}

template <class T>
cdVector<T>::~cdVector() {} // empty deconstructor

template <class T>
int cdVector<T>::GetNumDims() {
    return m_nDims;
}

// element handline
//--------------------------------

template<class T>
T cdVector<T>::GetElement(int i) {
    return m_vectorData[i];
}

// overloaded operators
// -----------------------------
template <class T>
cdVector<T> cdVector<T>::operator+ (const cdVector<T> &rhs) const {
    if (m_nDims != rhs.m_nDims) {
        throw std::invalid_argument("Vector dimensions do not match");
    }

    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) + rhs.m_vectorData.at(i));
    }

    cdVector<T> result(resultData);
    return result;
}

template <class T>
cdVector<T> cdVector<T>::operator- (const cdVector<T> &rhs) const {
    if (m_nDims != rhs.m_nDims) {
        throw std::invalid_argument("Vector dimensions do not match");
    }

    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) - rhs.m_vectorData.at(i));
    }

    cdVector<T> result(resultData);
    return result;
}

template <class T>
cdVector<T> cdVector<T>::operator* (T &rhs) const {

    // scalar multiplication
    std::vector<T> resultData;
    for (int i = 0; i < m_nDims; ++i) {
        resultData.push_back(m_vectorData.at(i) * rhs);
    }

    cdVector<T> result(resultData);
    return result;
}

// friend function
// -----------------------

template <class T>
cdVector<T> operator* (const T &lhs, const cdVector<T> &rhs) {

    std::vector<T> resultData;
    for (int i = 0; i < rhs.m_nDims; ++i) {
        resultData.push_back(rhs.m_vectorData.at(i) * lhs);
    }

    cdVector<T> result(resultData);
    return result;
}

// static functions
// ------------------------

// vector dot product
template <class T>
T cdVector<T>::dot(const cdVector<T> &a, const cdVector<T> &b) {
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
cdVector<T> cdVector<T>::cross(const cdVector<T> &a, const cdVector<T> &b) {

    if (a.m_nDims != b.m_nDims) { // vector dimensions must match
        throw std::invalid_argument("Vector dimensions do not match");
    }

    if (a.m_nDims != 3) { // vector dimensions must equal 3
        throw std::invalid_argument("Cross product can only be computed for 3d vectors");
    }

    // actually compute the cross product
    std::vector<T> resultData;
    resultData.push_back((a.m_vectorData.at(1) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(1)));
    resultData.push_back(-((a.m_vectorData.at(0) * b.m_vectorData.at(2)) - (a.m_vectorData.at(2) * b.m_vectorData.at(0))));
    resultData.push_back((a.m_vectorData.at(0) * b.m_vectorData.at(1)) - (a.m_vectorData.at(1) * b.m_vectorData.at(0)));

    cdVector<T> result(resultData);
    return result;

}