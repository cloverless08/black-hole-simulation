//
// Created by cdemin on 11/3/26.
//
//

#include "camera.h"
#include "ray.h"

#include "../include/cdVector.h"

raytrace::Camera::Camera() {
    m_cameraPosition = math::cdVector<double> {std::vector<double> {0.0, -10.0, 0.0}}; // 10 units away form origin
    m_cameraLookAt = math::cdVector<double> {std::vector<double> {0.0, 0.0, 0.0}}; // looking at origin
    m_cameraUp = math::cdVector<double> {std::vector<double> {0.0, 0.0, 1.0}};

    m_cameraLength = 1.0;
    m_cameraAspectRatio = 1.0;
}

//paramter assigning functions
void raytrace::Camera::SetPosition(const math::cdVector<double> &newPosition) {
    m_cameraPosition = newPosition;
}

void raytrace::Camera::SetLookAt(const math::cdVector<double> &newLookAt) {
    m_cameraLookAt = newLookAt;
}

void raytrace::Camera::SetUp(const math::cdVector<double> &newUp) {
    m_cameraUp = newUp;
}

void raytrace::Camera::SetLength(double newLength) {
    m_cameraLength = newLength;
}

void raytrace::Camera::SetHorizontalSize(double horizontalSize) {
    m_cameraHorizontalSize = horizontalSize;
}

void raytrace::Camera::SetAspectRatio(double aspectRatio) {
    m_cameraAspectRatio = aspectRatio;
}

// return paramters of cmaera
// position
math::cdVector<double> raytrace::Camera::GetPosition() const {
    return m_cameraPosition;
}

math::cdVector<double> raytrace::Camera::GetLookAt() const {
    return m_cameraLookAt;
}

//up vector
math::cdVector<double> raytrace::Camera::GetUp() const {
    return m_cameraUp;
}

// length of camera
double raytrace::Camera::GetLength() {
    return m_cameraLength;
}

// return horizontal size
double raytrace::Camera::GetHorizontalSize() {
    return m_cameraHorizontalSize;
}

// aspect ratio
double raytrace::Camera::GetAspectRatio() {
    return m_cameraAspectRatio;
}


// method to return U and V vectors
math::cdVector<double> raytrace::Camera::GetU() const {
    return m_projScreenU;
}

math::cdVector<double> raytrace::Camera::GetV() const {
    return m_projScreenV;
}

// get proj screen center
math::cdVector<double> raytrace::Camera::GetScreenCenter() const {
    return m_projScreenCenter;
}


// comput camera geometry
void raytrace::Camera::UpdateCamera() {
    // compute vector from camera position to lookat position (principle axis)
    m_alignment = m_cameraLookAt - m_cameraPosition;
    m_alignment.Normalize();

    // compute U and V vectors
    m_projScreenU = math::cdVector<double>::cross(m_alignment, m_cameraUp);
    m_projScreenU.Normalize();

    m_projScreenV = math::cdVector<double>::cross(m_projScreenU, m_alignment);
    m_projScreenV.Normalize();

    // compute position of center point of screen
    m_projScreenCenter = m_cameraPosition + (m_cameraLength * m_alignment);

    //modify U and V to match size and asepct ratio
    m_projScreenU = m_projScreenU * m_cameraHorizontalSize; // change unit length to screen dimensions
    m_projScreenV = m_projScreenV * (m_cameraHorizontalSize / m_cameraAspectRatio);

}

bool raytrace::Camera::GenerateRay(float projScreenX, float projScreenY, raytrace::Ray &camRay) {

    // compute location of screen point (in world coordinates) U/V --> X/Y/Z
    math::cdVector<double> screenWorldPart1 = m_projScreenCenter + (m_projScreenU * projScreenX); // transorms U coordinate to world coordinates
    math::cdVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projScreenV * projScreenY);

    camRay.m_point1 = m_cameraPosition;
    camRay.m_point2 = screenWorldCoordinate;

    camRay.m_lab = screenWorldCoordinate - m_cameraPosition;

    // compute ray
    return true;


}
