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
        // outputs in degrees
        return std::abs(DotProduct(rhs, lhs)) < 1e-9;
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
    math::Vec3 operator/(double s) const { return {data[0]/s, data[1]/s, data[2]/s}; }
    math::Vec3& operator+=(const math::Vec3& o) { data[0]+=o.data[0]; data[1]+=o.data[1]; data[2]+=o.data[2]; return *this; }

    // returns a unit-length copy of this vector (same direction, length 1)
    Vec3 Normalized() const {
        double len = GetLength();
        return {data[0]/len, data[1]/len, data[2]/len};
    }

    // const-ref versions of dot/cross so temporaries can be passed in, e.g. Vec3::Dot(a + b, c)
    static double Dot(const Vec3& a, const Vec3& b) {
        return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
    }

    static Vec3 Cross(const Vec3& a, const Vec3& b) {
        return {
            (a[1] * b[2]) - (a[2] * b[1]),
            (a[2] * b[0]) - (a[0] * b[2]),
            (a[0] * b[1]) - (a[1] * b[0])
        };
    }

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

// lets scalars go on the left side too: 0.5 * dt * v
inline Vec3 operator*(double s, const Vec3& v) { return v * s; }

class Vec2 {   // for 2D space
public:
    std::array<double, 2> data;

    Vec2() : data{0.0,0.0} {};
    Vec2(double x, double y) : data{x,y} {};


    // getter functions
    //===========================
    double x() const { // retrieves x coordinate (element 0)
        return data[0];
    }

    double y() const { // retrives y coordinate (element 1)
        return data[1];
    }

    // retrieves I vector for standard base vectors
    Vec2 GetVecI() const {
        return {data[0], 0.0};
    }

    // retrieves J vector for standard base vectors
    Vec2 GetVecJ() const {
        return {0.0, data[1]};
    }


    // operator overloaders
    //============================
    math::Vec2 operator-() const {
        return math::Vec2{-data[0], -data[1]};
    }

    double operator[](int i) const {return data[i];}
    double& operator[](int i) {return data[i];}
};
} // namespace math