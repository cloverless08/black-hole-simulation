classDiagram
direction TB
namespace math {
  class Vec3 {
    +array~double~ data
    +Vec3()
    +Vec3(position0, position1, position2)
    +x() double
    +y() double
    +z() double
    +GetVecI() Vec3
    +GetVecJ() Vec3
    +GetVecK() Vec3
    +GetLength() double
    +Normalized() Vec3
    +SetElement(index, val) void
    +IsOrthogonal(rhs, lhs) bool
    +DotProduct(rhs, lhs) double
    +CrossProduct(rhs, lhs) Vec3
    +GetAngleBetween(a, b) double
    +Dot(a, b)$ double
    +Cross(a, b)$ Vec3
    +operator+(o) Vec3
    +operator-(o) Vec3
    +operator*(s) Vec3
    +operator/(s) Vec3
    +operator+=(o) Vec3
    +operator-() Vec3
    +operator at(i) double
  }
  class Vec2 {
    +array~double~ data
    +Vec2()
    +Vec2(x, y)
    +x() double
    +y() double
    +operator-() Vec2
    +operator at(i) double
  }
}
namespace raytrace {
  class Camera {
    -qbVector~double~ m_cameraPosition
    -qbVector~double~ m_cameraLookAt
    -qbVector~double~ m_cameraUp
    -double m_cameraLength
    -double m_cameraHorizontalSize
    -double m_cameraAspectRatio
    -qbVector~double~ m_alignment
    -qbVector~double~ m_projScreenU
    -qbVector~double~ m_projScreenV
    -qbVector~double~ m_projScreenCenter
    +Camera()
    +SetPosition(newPosition) void
    +SetLookAt(newLookAt) void
    +SetUp(upVector) void
    +SetLength(newLength) void
    +SetHorizontalSize(horizontalSize) void
    +SetAspectRatio(aspectRatio) void
    +GetPosition() qbVector~double~
    +GetLookAt() qbVector~double~
    +GetUp() qbVector~double~
    +GetU() qbVector~double~
    +GetV() qbVector~double~
    +GetScreenCenter() qbVector~double~
    +GetLength() double
    +GetHorizontalSize() double
    +GetAspectRatio() double
    +GenerateRay(projScreenX, projScreenY, camRay) bool
    +UpdateCamera() void
  }
  class Ray {
    +qbVector~double~ m_point1
    +qbVector~double~ m_point2
    +qbVector~double~ m_lab
    +Ray()
    +Ray(point1, point2)
    +GetPoint1() qbVector~double~
    +GetPoint2() qbVector~double~
  }
  class ObjectBase {
    +qbVector~double~ m_baseColor
    +qbVector~double~ m_location
    +double m_radius
    +ObjectBase()
    +~ObjectBase()
    +TestIntersection(castRay, intPoint, localNorm, localColor)* bool
    +CheckAreClose(float1, float2) bool
    +GetPosition() qbVector~double~
    +GetRadius() double
  }
  class ObjSphere {
    +ObjSphere(location, radius)
    +~ObjSphere()
    +TestIntersection(castRay, intPoint, localNorm, localColor) bool
    +GetRadius() double
  }
  class LightBase {
    +qbVector~double~ m_color
    +qbVector~double~ m_location
    +double m_intensity
    +LightBase()
    +~LightBase()
    +ComputeIllumination(intPoint, localNorm, objectList, currentObject, color, intensity)* bool
  }
  class PointLight {
    +PointLight()
    +~PointLight()
    +ComputeIllumination(intPoint, localNorm, objectList, currentObject, color, intensity) bool
  }
  class RayIntegrator {
    <<deprecated>>
  }
  class LinearRayIntegrator {
    +LinearRayIntegrator()
    +~LinearRayIntegrator()
    +LinearRayTrace(buffer, Cam, startY, endY, height, width, backgroundColor, factorX, factorY, objectList, lightList)$ void
  }
  class MarchingRayIntegrator {
    +MarchingRayIntegrator()
    +~MarchingRayIntegrator()
    +MarchRayTrace(buffer, Cam, startY, endY, height, width, backgroundColor, factorX, factorY, objectList, lightList)$ void
  }
  class GeodesicRayIntegrator {
    -int NUM_CHECKERBOARD_ROWS = 36
    -int NUM_CHECKERBOARD_COLS = 72
    +GeodesicRayIntegrator()
    +~GeodesicRayIntegrator()
    +GeodesicRayTrace(buffer, Cam, startY, endY, height, width, backgroundColor, factorX, factorY, objectList, lightList)$ void
    -Accel(pos, h2)$ Vec3
    -RK4Step(pos, vel, h2, dt)$ void
    -RenderBackground(dir)$ Vec3
    -AccretionDisk(r)$ Vec3
  }
}
class BlackHole {
  <<not built>>
  -double mass
  +BlackHole(mass)
  +~BlackHole()
}
class PostProcess {
  <<stub>>
  +PostProcess()
  +~PostProcess()
}
class SCREEN_RESOLUTION {
  <<enumeration>>
  STANDARD_W = 640
  STANDARD_H = 480
  MOVING_W = 320
  MOVING_H = 240
}
class SceneMain {
  <<main.cpp>>
  -uint NUMBER_CORES
  -uint AMOUNT_RAM
  -Vec3 BACKGROUND_COLOR
  -Camera cam
  -vector~shared_ptr~ObjectBase~~ objectList
  -vector~shared_ptr~LightBase~~ lightList
  -vector~uint32_t~ pixelBuffer
  +main() int
}
class qbVector~T~ {
  <<library: qbLinearAlgebra>>
  +GetElement(index) T
  +GetNumDims() int
  +Normalize() void
  +Normalized() qbVector~T~
  +norm() T
  +dot(a, b)$ T
  +cross(a, b)$ qbVector~T~
}
ObjectBase <|-- ObjSphere
ObjectBase <|-- BlackHole
LightBase <|-- PointLight
RayIntegrator <|-- GeodesicRayIntegrator
Camera ..> Ray : GenerateRay fills
Camera *-- qbVector : 7 vectors
Ray *-- qbVector : 3 vectors
ObjectBase ..> Ray : tests
LightBase ..> ObjectBase : objectList, currentObject
LinearRayIntegrator ..> Camera : GenerateRay
LinearRayIntegrator ..> ObjectBase : TestIntersection
LinearRayIntegrator ..> LightBase : ComputeIllumination
MarchingRayIntegrator ..> Camera : GenerateRay
MarchingRayIntegrator ..> LightBase : ComputeIllumination
GeodesicRayIntegrator ..> Camera : GenerateRay
GeodesicRayIntegrator ..> Vec3 : RK4 state
SceneMain *-- Camera
SceneMain o-- "2" ObjSphere
SceneMain o-- "1" PointLight
SceneMain ..> SCREEN_RESOLUTION
SceneMain ..> GeodesicRayIntegrator : via CreateGeodesicThreads
