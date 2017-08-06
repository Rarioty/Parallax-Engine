#include <Parallax/Physics/PhysicsBullet.hpp>

#include <Parallax/Platform.hpp>

#if PARALLAX_PHYSICS_BULLET_ALLOWED

#include <btBulletDynamicsCommon.h>

namespace Parallax::Physics::Bullet
{
    static btBroadphaseInterface*               s_broadphase = nullptr;
    static btDefaultCollisionConfiguration*     s_collisionConfiguration = nullptr;
    static btCollisionDispatcher*               s_collisionDispatcher = nullptr;
    static btSequentialImpulseConstraintSolver* s_solver = nullptr;
    static btDiscreteDynamicsWorld*             s_dynamicWorld = nullptr;

    bool Init()
    {
        s_broadphase = new btDbvtBroadphase();

        s_collisionConfiguration = new btDefaultCollisionConfiguration();
        s_collisionDispatcher = new btCollisionDispatcher(s_collisionConfiguration);

        s_solver = new btSequentialImpulseConstraintSolver;

        s_dynamicWorld = new btDiscreteDynamicsWorld(s_collisionDispatcher, s_broadphase, s_solver, s_collisionConfiguration);

        return true;
    }

    void Shutdown()
    {
        if (s_broadphase)
            delete s_broadphase;

        if (s_collisionDispatcher)
            delete s_collisionDispatcher;

        if (s_collisionConfiguration)
            delete s_collisionConfiguration;

        if (s_solver)
            delete s_solver;

        if (s_dynamicWorld)
            delete s_dynamicWorld;
    }

    const char* GetRendererName()
    {
        return PARALLAX_PHYSICS_BULLET_NAME;
    }

    PhysicsEngineType   GetRendererType()
    {
        return PhysicsEngineType::BulletEngine;
    }
}
#endif
