#ifndef PARALLAX_PHYSICS_HPP_GUARD
#define PARALLAX_PHYSICS_HPP_GUARD

#include <Parallax/Platform.hpp>

namespace Parallax
{
    namespace Physics
    {
        enum PhysicsEngineType
        {
#if PARALLAX_PHYSICS_PHYSX_ALLOWED
            PhysxEngine,
#endif
#if PARALLAX_PHYSICS_BULLET_ALLOWED
            BulletEngine,
#endif

            COUNT
        };

        bool Init(std::string physics_engine_name);
        void Shutdown();

        const char*         GetRendererName();
        PhysicsEngineType   GetRendererType();
    }
}

#endif
