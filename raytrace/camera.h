//
// Created by cdemin on 10/13/26.
//

#pragma once

#include "../include/structs.h"
#include "ray.h"

namespace raytrace {
    class Camera {
    public:
        // default constructor
        Camera();

        // camera parameter functions
        void SetPosition(const qbVector<double> &newPosition);
        void SetLookAt(const qbVector<double> &newLookAt);
        void SetUp(const qbVector<double> &upVector);
        void SetLength(double newLength); // distance from virtual screen

        void SetHorizontalSize(double horizontalSize); // defines aspect ratio
        void SetAspectRatio(double aspectRatio);

        // parameter getter functions
        [[nodiscard]] qbVector<double> GetPosition() const;
        [[nodiscard]] qbVector<double> GetLookAt() const;
        [[nodiscard]] qbVector<double> GetUp() const;
        [[nodiscard]] qbVector<double> GetU() const; // screen dimensions getter
        [[nodiscard]] qbVector<double> GetV() const; // screen dimension getter
        [[nodiscard]] qbVector<double> GetScreenCenter() const;

        double GetLength();
        double GetHorizontalSize();
        double GetAspectRatio();

        // function to get a ray
        bool GenerateRay(float projectScreenX, float projectScreenY,
            raytrace::Ray &camRay); // x and y define position on screen that we generate a ray for

        // update camera geometry
        void UpdateCamera();

    private:
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
