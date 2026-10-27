//
// Created by cdemin on 9/10/26.
//

#pragma once

#include <array>

namespace math {
class Vec3 {    // for 3d space
public:
    std::array<double, 3> data;

    // constructors for empty and 3 arg calls
    Vec3() : data{0.0,0.0,0.0} {}
    Vec3(double position0, double position1, double position2) : data{position0,position1,position2} {}


    // getter functions
     double x() const {
        return data[0];
    }

    double y() const {
        return data[1];
    }

    double z() const {
        return data[2];
    }


    // operator functions
    math::Vec3 operator-() const {
        return math::Vec3{-data[0], -data[1], -data[2]};
    }
    double operator[](int i) const {return data[i];}
    double& operator[](int i) {return data[i];}

    math::Vec3 operator+(const math::Vec3& o) const { return {x()+o.x(), y()+o.y(), z()+o.z()}; }
    math::Vec3 operator-(const math::Vec3& o) const { return {x()-o.x(), y()-o.y(), z()-o.z()}; }
    math::Vec3 operator*(double s) const { return {x()*s, y()*s, z()*s}; }

    // experimenting with something that could replace Vec2
    template <std::size_t N> class Vec { std::array<double,N> data; };

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

class BlackHole {
public:
    // defaults every value to 0 if not otherwise called
    math::Vec3 position = {0.0,0.0,0.0};
    double mass = 0;
    double radius = 0;
};