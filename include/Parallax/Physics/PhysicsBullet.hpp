#ifndef PARALLAX_PHYSICS_BULLET_HPP_GUARD
#define PARALLAX_PHYSICS_BULLET_HPP_GUARD

#include <Parallax/Physics/Physics.hpp>

namespace Parallax
{
    namespace Physics
    {
        namespace Bullet
        {
            bool Init();
            void Shutdown();

            const char*         GetRendererName();
            PhysicsEngineType   GetRendererType();
        }
    }
}

#endif
