//
// Created by cdemin on 9/10/26.
//

#pragma once


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
    Vec3 operator-() const {
        return Vec3{-data[0], -data[1], -data[2]};
    }
    double operator[](int i) const {return data[i];}
    double& operator[](int i) {return data[i];}

    Vec3 operator+(const Vec3& o) const { return {x()+o.x(), y()+o.y(), z()+o.z()}; }
    Vec3 operator-(const Vec3& o) const { return {x()-o.x(), y()-o.y(), z()-o.z()}; }
    Vec3 operator*(double s) const { return {x()*s, y()*s, z()*s}; }

    // experimenting with something that coudld replace Vec2
    template <std::size_t N> class Vec { std::array<double,N> data; };

};

class Ray {
public:
    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction) : dataOrigin(origin), dataDirection(direction) {}

    // getter functions
    const Vec3& origin() const {
        return dataOrigin;
    }
    const Vec3& direction() const {
        return dataDirection;
    }
private:
    Vec3 dataOrigin;
    Vec3 dataDirection;
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

    Vec2 operator-() const {
        return Vec2{-data[0], -data[1]};
    }

    double operator[](int i) const {return data[i];}
    double& operator[](int i) {return data[i];}
};

class BlackHole {
public:
    Vec3 position = {0.0,0.0,0.0};
    double mass = 100;
    double radius = 0.25;
};

class Camera {
public:
    int pitch = 0;
    int yaw = 0;
    int distance = 0;
};
