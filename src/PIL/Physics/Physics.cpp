#include <Parallax/Physics/Physics.hpp>

#include <Parallax/Physics/PhysicsBullet.hpp>
#include <Parallax/Debug/Debug.hpp>

namespace Parallax::Physics
{
    static std::string s_physics_engine = "";

    inline bool IsPhysicsEngineAllowed(std::string renderer)
    {
        if (renderer == "physx")
        {
#if PARALLAX_PHYSICS_PHYSX_ALLOWED
            return true;
#else
            return false;
#endif
        }
        else if (renderer == "bullet")
        {
#if PARALLAX_PHYSICS_BULLET_ALLOWED
            return true;
#else
            return false;
#endif
        }

        return false;
    }

    bool Init(std::string physics_engine_name)
    {
        bool result = IsPhysicsEngineAllowed(physics_engine_name);

        PARALLAX_FATAL(true == result, "Physics engine %s is not compiled with Parallax Engine !");

        result = false;
#if PARALLAX_PHYSICS_PHYSX_ALLOWED
        if (physics_engine_name == "physx")
        {
            result = PhysX::Init();
        }
#endif
#if PARALLAX_PHYSICS_BULLET_ALLOWED
        if (physics_engine_name == "bullet")
        {
            result = Bullet::Init();
        }
#endif

        return result;
    }

    void Shutdown()
    {
#if PARALLAX_PHYSICS_PHYSX_ALLOWED
        if (s_physics_engine == "physx")
        {
            PhysX::Shutdown();
        }
#endif
#if PARALLAX_PHYSICS_BULLET_ALLOWED
        if (s_physics_engine == "bullet")
        {
            Bullet::Shutdown();
        }
#endif
    }

    const char* GetRendererName()
    {
#if PARALLAX_PHYSICS_PHYSX_ALLOWED
        if (s_physics_engine == "physx")
        {
            return PhysX::GetRendererName();
        }
#endif
#if PARALLAX_PHYSICS_BULLET_ALLOWED
        if (s_physics_engine == "bullet")
        {
            return Bullet::GetRendererName();
        }
#endif

        return nullptr;
    }

    PhysicsEngineType GetRendererType()
    {
#if PARALLAX_PHYSICS_PHYSX_ALLOWED
        if (s_physics_engine == "physx")
        {
            return PhysX::GetRendererType();
        }
#endif
#if PARALLAX_PHYSICS_BULLET_ALLOWED
        if (s_physics_engine == "bullet")
        {
            return Bullet::GetRendererType();
        }
#endif

        return PhysicsEngineType::COUNT;
    }
}
