/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    include/vec.h
//  Purpose: Lightweight Vec3 and Vec2 math types used throughout the project.
/* ========================================================================== */

#pragma once

#include <array>
#include <cmath>

namespace math {
class Vec3 {    // for 3d space
public:
    std::array<double, 3> data;

    // constructors for empty and 3 arg calls
    Vec3() : data{0.0,0.0,0.0} {}
    Vec3(double position0, double position1, double position2) : data{position0,position1,position2} {}


    // getter functions
    //=====================================
     double x() const {
        return data[0];
    }

    double y() const {
        return data[1];
    }

    double z() const {
        return data[2];
    }


    // retrieves i vector for standard base vectors
    Vec3 GetVecI() const {
        return {data[0], 0.0, 0.0};
    }

    // retrieves j vector for standard base vectors
    Vec3 GetVecJ() const {
        return {0.0, data[1], 0.0};
    }

    // retrieves k vector for standard base vectors
    Vec3 GetVecK() const {
        return {0.0, 0.0, data[2]};
    }

    double GetLength() const {
        return std::sqrt((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]));
    }


    // other checks that idk how to classify (idk if its even useful)
    //==========================================
    bool IsOrthogonal(Vec3 & rhs, Vec3 & lhs) const {
        if (GetAngleBetween(rhs, lhs) == 90.0) {
            return true;
        } else {
            return false;
        }
    }


    // operator functions
    math::Vec3 operator-() const {
        return math::Vec3{-data[0], -data[1], -data[2]};
    }
    double operator[](int i) const {return data[i];}
    double& operator[](int i) {return data[i];}

    // traditional operator overloaders
    math::Vec3 operator+(const math::Vec3& o) const { return {data[0]+o.data[0], data[1]+o.data[1], data[2]+o.data[2]}; }
    math::Vec3 operator-(const math::Vec3& o) const { return {data[0]-o.data[0], data[1]-o.data[1], data[2]-o.data[2]}; }
    math::Vec3 operator*(double s) const { return {data[0]*s, data[1]*s, data[2]*s}; }

    // setter function to change one element of data
    void SetElement(int index, double val) {
        data[index] = val;
    }


    // computational functions/operators
    double DotProduct(Vec3 & rhs, Vec3 & lhs) const { //returns a scalar value of dot product
        double dot = 0.0;

        for (int i = 0; i < 3; ++i) {
            dot += lhs[i] * rhs[i];
        }

        return dot;
    }

    Vec3 CrossProduct(Vec3 & rhs, Vec3 & lhs) { // returns a vector value of the cross product between two inputted vectors
    // essentially vector multiplication (or a form of it)
    // computes rhs x lhs (first argument crossed with second); order matters, a x b == -(b x a)
    // result is perpendicular to both inputs, with length |a||b|sin(theta)
        return {
            (rhs[1] * lhs[2]) - (rhs[2] * lhs[1]),  // i component
            (rhs[2] * lhs[0]) - (rhs[0] * lhs[2]),  // j component
            (rhs[0] * lhs[1]) - (rhs[1] * lhs[0])   // k component
        };
    }

    double GetAngleBetween(Vec3 & a, Vec3 & b) const { // dereived from dot product, gets angle between two vectors

        double lenA = a.GetLength();
        double lenB = b.GetLength();

        double dot = DotProduct(a, b);

        double tmp = dot / (lenA * lenB);

        return acos(tmp);
    }

};

class Vec2 {   // for 2D space
public:
    std::array<double, 2> data;

    Vec2() : data{0.0,0.0} {};
    Vec2(double x, double y) : data{x,y} {};

    double x() const {
        return data[0];
    }

    double y() const {
        return data[1];
    }

    math::Vec2 operator-() const {
        return math::Vec2{-data[0], -data[1]};
    }

    double operator[](int i) const {return data[i];}
    double& operator[](int i) {return data[i];}
};
} // namespace math