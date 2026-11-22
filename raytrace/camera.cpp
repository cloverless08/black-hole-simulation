/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/camera.cpp
//  Purpose: Implements the Camera class and builds the virtual screen
//           used to generate primary rays.
/* ========================================================================== */

#include "camera.h"
#include "ray.h"

#include<math.h>
#include<algorithm>

#include "main_utils.h"

raytrace::Camera::Camera() {
    StrOut("Camera: Constructing Camera");

    m_cameraPosition = qbVector<double> {std::vector<double> {0.0, -10.0, 0.0}}; // 10 units away form origin
    m_cameraLookAt = qbVector<double> {std::vector<double> {0.0, 0.0, 0.0}}; // looking at origin
    m_cameraUp = qbVector<double> {std::vector<double> {0.0, 0.0, 1.0}};

    m_cameraLength = 1.0;
    m_cameraAspectRatio = 1.0;

    m_distanceFromOrigin = 30.0;
}

constexpr double MAX_ELEVATION = 85.0 * M_PI / 180.0; // stops you from going 90 degrees above or below holw (converted to radians)

//paramter assigning functions
void raytrace::Camera::SetPosition(const qbVector<double> &newPosition) {
    m_cameraPosition = newPosition;
}

void raytrace::Camera::SetLookAt(const qbVector<double> &newLookAt) {
    m_cameraLookAt = newLookAt;
}

void raytrace::Camera::SetUp(const qbVector<double> &newUp) {
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

void raytrace::Camera::SetDistanceFromOrigin(double newDistanceFromOrigin) {
    m_distanceFromOrigin = newDistanceFromOrigin;
}


// return parameters of camera
// position
qbVector<double> raytrace::Camera::GetPosition() const {
    return m_cameraPosition;
}

qbVector<double> raytrace::Camera::GetLookAt() const {
    return m_cameraLookAt;
}

//up vector
qbVector<double> raytrace::Camera::GetUp() const {
    return m_cameraUp;
}

// length of camera
double raytrace::Camera::GetLength() {
    return m_cameraLength;
}

double raytrace::Camera::GetDistanceFromOrigin() {
    return m_distanceFromOrigin;
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
qbVector<double> raytrace::Camera::GetU() const {
    return m_projScreenU;
}

qbVector<double> raytrace::Camera::GetV() const {
    return m_projScreenV;
}

// get proj screen center
qbVector<double> raytrace::Camera::GetScreenCenter() const {
    return m_projScreenCenter;
}


// comput camera geometry
void raytrace::Camera::UpdateCamera() {
    // compute vector from camera position to lookat position (principle axis)
    m_alignment = m_cameraLookAt - m_cameraPosition;
    m_alignment.Normalize();

    // compute U and V vectors
    m_projScreenU = qbVector<double>::cross(m_alignment, m_cameraUp);
    m_projScreenU.Normalize();

    m_projScreenV = qbVector<double>::cross(m_projScreenU, m_alignment);
    m_projScreenV.Normalize();

    // compute position of center point of screen
    m_projScreenCenter = m_cameraPosition + (m_cameraLength * m_alignment);

    //modify U and V to match size and asepct ratio
    m_projScreenU = m_projScreenU * m_cameraHorizontalSize; // change unit length to screen dimensions
    m_projScreenV = m_projScreenV * (m_cameraHorizontalSize / m_cameraAspectRatio);

}

bool raytrace::Camera::GenerateRay(float projScreenX, float projScreenY, raytrace::Ray &camRay) {

    // compute location of screen point (in world coordinates) U/V --> X/Y/Z
    qbVector<double> screenWorldPart1 = m_projScreenCenter + (m_projScreenU * projScreenX); // transorms U coordinate to world coordinates
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projScreenV * projScreenY);

    camRay.m_point1 = m_cameraPosition;
    camRay.m_point2 = screenWorldCoordinate;

    camRay.m_lab = screenWorldCoordinate - m_cameraPosition;

    // compute ray
    return true;


}

// compute angles for orbit
void raytrace::Camera::Orbit(double deltaAzimuth, double deltaElevation) {
    // azimuth wraps freely around the z axis
    m_azimuth = std::fmod(m_azimuth + deltaAzimuth, 2.0 * M_PI);

    // clamp elevation to avoid NaN errors at poles
    m_elevation = std::clamp(m_elevation + deltaElevation, -MAX_ELEVATION, MAX_ELEVATION);

    const double radius = m_distanceFromOrigin;

    // spherical to cartesian, z is up
    const double x = radius * std::cos(m_elevation) * std::cos(m_azimuth);
    const double y = radius * std::cos(m_elevation) * std::sin(m_azimuth);
    const double z = radius * std::sin(m_elevation);

    SetPosition(qbVector<double>{std::vector<double>{x, y, z}});
    SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    UpdateCamera();
}

// getter functions for orbits
double raytrace::Camera::GetAzimuth() const {
    return m_azimuth;
}

double raytrace::Camera::GetElevation() const {
    return m_elevation;
}