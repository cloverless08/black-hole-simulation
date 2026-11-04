//
// Created by cdemin on 10/13/26.
//

#pragma once

#include "../include/cdVector.h"
#include "../include/structs.h"

namespace raytrace {
    class Camera {
    public:
        // default constructor
        Camera();

        // camera parameter functions
        void SetPosition(const math::cdVector<double> &newPosition);
        void SetLookAt(const math::cdVector<double> &newLookAt);
        void SetUp(const math::cdVector<double> &upVector);
        void SetLength(double newLength); // distance from virtual screen

        void SetHorizontalSize(double horizontalSize); // defines aspect ratio
        void SetAspectRatio(double aspectRatio);

        // parameter getter functions
        [[nodiscard]] math::cdVector<double> GetPosition() const;
        [[nodiscard]] math::cdVector<double> GetLookAt() const;
        [[nodiscard]] math::cdVector<double> GetUp() const;
        [[nodiscard]] math::cdVector<double> GetU() const; // screen dimensions getter
        [[nodiscard]] math::cdVector<double> GetV() const; // screen dimension getter
        [[nodiscard]] math::cdVector<double> GetScreenCenter() const;

        double GetLength();
        double GetHorizontalSize();
        double GetAspectRatio();

        // function to get a ray
        bool GenerateRay(float projectScreenX, float projectScreenY,
            raytrace::Ray &camRay); // x and y define position on screen that we generate a ray for

        // update camera geometry
        void UpdateCamera();

    private:
        math::cdVector<double> m_cameraPosition = math::cdVector<double>(3);
        math::cdVector<double> m_cameraLookAt = math::cdVector<double>(3);
        math::cdVector<double> m_cameraUp = math::cdVector<double>(3);
        double m_cameraLength;
        double m_cameraHorizontalSize;
        double m_cameraAspectRatio;

        math::cdVector<double> m_alignment = math::cdVector<double>(3);
        math::cdVector<double> m_projScreenU = math::cdVector<double>(3);
        math::cdVector<double> m_projScreenV = math::cdVector<double>(3);
        math::cdVector<double> m_projScreenCenter = math::cdVector<double>(3);
    };
}