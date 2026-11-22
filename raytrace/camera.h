/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/camera.h
//  Purpose: Declares the Camera class: position, look-at, up vector,
//           screen geometry, and primary ray generation.
/* ========================================================================== */

#pragma once

#include "../include/vec.h"
#include "ray.h"

namespace raytrace {
    class Camera {
    public:
        // default constructor
        Camera();

        // camera parameter and setter functions
        void SetPosition(const qbVector<double> &newPosition);
        void SetLookAt(const qbVector<double> &newLookAt);
        void SetUp(const qbVector<double> &upVector);
        void SetLength(double newLength); // distance from virtual screen

        void SetHorizontalSize(double horizontalSize); // defines aspect ratio
        void SetAspectRatio(double aspectRatio);
        void SetDistanceFromOrigin(double newDistanceFromOrigin);

        // parameter getter functions
        [[nodiscard]] qbVector<double> GetPosition() const;
        [[nodiscard]] qbVector<double> GetLookAt() const;
        [[nodiscard]] qbVector<double> GetUp() const;
        [[nodiscard]] qbVector<double> GetU() const; // screen dimensions getter
        [[nodiscard]] qbVector<double> GetV() const; // screen dimension getter
        [[nodiscard]] qbVector<double> GetScreenCenter() const;

        // getter functions
        double GetLength();
        double GetHorizontalSize();
        double GetAspectRatio();
        double GetDistanceFromOrigin();

        // function to get a ray
        bool GenerateRay(float projectScreenX, float projectScreenY,
            raytrace::Ray &camRay); // x and y define position on screen that we generate a ray for

        // update camera geometry
        void UpdateCamera();

        // camera rotation around hole
        void Orbit(double deltaAzimuth, double deltaElevation);
        double GetAzimuth() const; // get angles of rotation left and right
        double GetElevation() const; // get angles of rotation up/down

    private:

        // member variables for orbiting
        double m_azimuth = -M_PI / 2.0;              // start on the -y axis
        double m_elevation = std::asin(3.0 / 30.0);  // ~5.7 deg above the disk

        double m_distanceFromOrigin;

        qbVector<double> m_cameraPosition = qbVector<double>(3);
        qbVector<double> m_cameraLookAt = qbVector<double>(3);
        qbVector<double> m_cameraUp = qbVector<double>(3);
        double m_cameraLength;
        double m_cameraHorizontalSize;
        double m_cameraAspectRatio;

        qbVector<double> m_alignment = qbVector<double>(3);
        qbVector<double> m_projScreenU = qbVector<double>(3);
        qbVector<double> m_projScreenV = qbVector<double>(3);
        qbVector<double> m_projScreenCenter = qbVector<double>(3);
    };
}
