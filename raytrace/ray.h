#pragma once

#include "structs.h"

namespace raytrace {
    class Ray {
        public:
            Ray() {}
            Ray(const math::Vec3& origin, const math::Vec3& direction) : dataOrigin(origin), dataDirection(direction) {}

            // getter functions
            const math::Vec3& origin() const {
                return dataOrigin;
            }
            const math::Vec3& direction() const {
                return dataDirection;
            }
        private:
            math::Vec3 dataOrigin;
            math::Vec3 dataDirection;
        };
}
