#pragma once

#include "structs.h"

namespace raytrace {
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
}
