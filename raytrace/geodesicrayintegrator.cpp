/* ========================================================================== */
//  CSC1060 at FRCC
//  Carrick De Min
//  Capstone Project
//
//  File:    raytrace/geodesicrayintegrator.cpp
//  Purpose: Geodesic ray tracer: integrates ray paths bent by gravity
//           around the black hole.
/* ========================================================================== */

#include "rayintegrator.h"
#include "../include/main_utils.h"

#include <algorithm>
#include <cmath>

namespace {
    // geometric units: G = c = 1 and lengths as multiples of M
    constexpr double M = 1.0;
    constexpr double R_HORIZON = 2.0 * M;   // event horizon (schwarzschild radius)
    constexpr double DISK_INNER   = 6.0 * M;   // ISCO, inner edge of the accretion disk
    constexpr double DISK_OUTER = 20.0 * M;  // outer edge of the accretion disk
    constexpr double R_ESCAPE  = 100.0 * M; // past this, the ray is considered gone to the sky
    constexpr int    MAX_STEPS = 2000;

    constexpr double PI = 3.14159265358979323846;
}

namespace raytrace {
    raytrace::GeodesicRayIntegrator::GeodesicRayIntegrator() {

    }

    raytrace::GeodesicRayIntegrator::~GeodesicRayIntegrator() {

    }

    math::Vec3 GeodesicRayIntegrator::Accel(const math::Vec3& pos, double h2) {
        // a = -3 M h^2 pos / r^5
        double r2 = math::Vec3::Dot(pos, pos);
        double r5 = r2 * r2 * std::sqrt(r2);
        return pos * (-3.0 * M * h2 / r5);
    }

    void GeodesicRayIntegrator::RK4Step(math::Vec3& pos, math::Vec3& vel, double h2, double dt) {
        // RK4 on the first-order system: pos' = vel, vel' = Accel(pos)
        // each k value is a pair where knp is the change of position and knv is acelleration

        // k1 measures at the start of the step
        math::Vec3 k1p = vel;
        math::Vec3 k1v = Accel(pos, h2);

        // k2 measures at the halfway point
        math::Vec3 k2p = vel + 0.5 * dt * k1v;
        math::Vec3 k2v = Accel(pos + 0.5 * dt * k1p, h2);

        // uses k2 to guess halfway again
        math::Vec3 k3p = vel + 0.5 * dt * k2v;
        math::Vec3 k3v = Accel(pos + 0.5 * dt * k2p, h2);

        // uses k3 to guess the end of a step and then measure there
        math::Vec3 k4p = vel + dt * k3v;
        math::Vec3 k4v = Accel(pos + dt * k3p, h2);

        // combine
        pos += (dt / 6.0) * (k1p + 2.0 * k2p + 2.0 * k3p + k4p);
        vel += (dt / 6.0) * (k1v + 2.0 * k2v + 2.0 * k3v + k4v);
    }

    math::Vec3 GeodesicRayIntegrator::RenderBackground(const math::Vec3& dir) {
        // direction into spherical angles
        double sphereLatitude = std::acos(std::clamp(dir.z(), -1.0, 1.0)); // theta, 0..pi
        double sphereLongitude   = std::atan2(dir.y(), dir.x()) + PI;          // phi, 0..2pi

        // checkerboard pattern on the render
        int cellsTheta = static_cast<int>(sphereLatitude / PI * 36.0); // hard coded square rows
        int cellsPhi   = static_cast<int>(sphereLongitude / (2.0 * PI) * 72.0); // hard coded square columns
        bool light = ((cellsTheta + cellsPhi) % 2) == 0;
        math::Vec3 color = light ? math::Vec3{40.0, 40.0, 60.0} : math::Vec3{15.0, 15.0, 25.0};

        // starfield
        int starT = static_cast<int>(sphereLatitude * 300.0);
        int starP = static_cast<int>(sphereLongitude * 300.0);
        uint32_t hash = static_cast<uint32_t>(starT) * 73856093u ^ static_cast<uint32_t>(starP) * 19349663u;
        hash ^= hash >> 13;
        hash *= 0x5bd1e995u;
        hash ^= hash >> 15;
        if ((hash % 1000u) < 3u) {
            color = {255.0, 255.0, 255.0};
        }

        return color;
    }

    math::Vec3 GeodesicRayIntegrator::AccretionDisk(double r) {
        // 0 at the inner edge, 1 at the outer edge
        double t = (r - DISK_INNER) / (DISK_OUTER - DISK_INNER);

        // hot (white/yellow) inside, cool (dark red) outside
        math::Vec3 inner{255.0, 230.0, 180.0};
        math::Vec3 outer{140.0, 30.0, 5.0};
        math::Vec3 color = inner * (1.0 - t) + outer * t;

        // brightness falloff
        double brightness = std::pow(DISK_INNER / r, 1.5);

        // faint rings so the warping of the disk shows up
        //double rings = 0.8 + 0.2 * std::cos(r * 4.0);

        return color * std::clamp(brightness, 0.0, 1.0);
    }

    void raytrace::GeodesicRayIntegrator::GeodesicRayTrace(std::vector<uint32_t>& buffer,
    raytrace::Camera& Cam,
    int startY, int endY,
    int height, int width,
    math::Vec3 backgroundColor,
    double factorX, double factorY,
    std::vector<std::shared_ptr<raytrace::ObjectBase>>& objectList, std::vector<std::shared_ptr<raytrace::LightBase>>& lightList) {
        /*
         * This should be repeated one time for every x and y pixel, each frame
         */

        for (int y = startY; y < endY; ++y) {
            for (int x = 0; x < width; ++x) {

                raytrace::Ray camRay; // construct ray for this pixel

                // projection screen coordinates
                double U = (static_cast<double>(x) * factorX) - 1.0;
                double V = (static_cast<double>(y) * factorY) - 1.0;

                Cam.GenerateRay(U, V, camRay);

                // convert to Vec3 for speed
                math::Vec3 pos{camRay.m_point1.GetElement(0), camRay.m_point1.GetElement(1), camRay.m_point1.GetElement(2)};
                math::Vec3 vel = math::Vec3{camRay.m_lab.GetElement(0), camRay.m_lab.GetElement(1), camRay.m_lab.GetElement(2)}.Normalized();

                // angular momentum squared, conserved along the whole ray
                math::Vec3 h = math::Vec3::Cross(pos, vel);
                double h2 = math::Vec3::Dot(h, h); // the "miss distance"" of the ray calculated once at the start

                math::Vec3 color{0.0, 0.0, 0.0}; // default: black (captured, or ran out of steps)

                for (int step = 0; step < MAX_STEPS; ++step) {
                    double r = pos.GetLength();

                    // small steps near the hole where paths bend sharply, big steps far away
                    double dt = std::clamp(0.02 * r * r / (r + 10.0), 0.005, 1.0);

                    math::Vec3 oldPos = pos;
                    RK4Step(pos, vel, h2, dt);
                    double newR = pos.GetLength();

                    // fell into the event horizon, means shadow
                    if (newR < R_HORIZON) {
                        break;
                    }

                    // crossed the disk plane (z=0),check whether it hit the disk
                    if (oldPos.z() * pos.z() < 0.0) {
                        double frac = oldPos.z() / (oldPos.z() - pos.z());
                        math::Vec3 hitPoint = oldPos + (pos - oldPos) * frac;
                        double rc = hitPoint.GetLength();
                        if (rc > DISK_INNER && rc < DISK_OUTER) {
                            color = AccretionDisk(rc);
                            break;
                        }
                    }

                    // excaped
                    if (newR > R_ESCAPE && math::Vec3::Dot(pos, vel) > 0.0) {
                        color = RenderBackground(vel.Normalized());
                        break;
                    }
                }

                SetPixel(buffer.data(), width, height, x, y,
                    static_cast<uint8_t>(color.x()),
                    static_cast<uint8_t>(color.y()),
                    static_cast<uint8_t>(color.z()));
            }
        }
    }
}
