# ECS - A CS Student Approach :)

The implementation is based on [Austin Morlan's ECS](https://austinmorlan.com/posts/entity_component_system/). However I did some minor changes (currently):
- Data Structures
- System implementations

Task List:

- [x] Entity Manager
- [x] Component Pool
- [x] Component Manager
- [x] System/Logic Handler
- [x] Coordinator (as class Ecs)
- [x] Entity Handler [Nomad approach](https://medium.com/@savas/nomad-game-engine-part-4-2-adding-handles-8d299d80c7d0)
- [ ] Events

Example:
``` cpp

struct Transform {
    vec2 position;
};

struct Rigidbody {
    vec2 velocity;
};

struct Physics {
    Real gravity;
};

PhysicsSystem::update(Ecs ecs) {
    Real dt = Engine::instance().deltaTime();
    auto applyGravity = [dt](Rigidbody& rb, Phyiscs& p) {
        rb.velocity += p.gravity*dt;
    }

    auto move = [dt](Transform& t, Rigibody& rb) {
        t.position += rb.velocity.y*dt;
    }

    ecs.forEach<Rigidbody, Physics>(applyGravity); 
    ecs.forEach<Transform, Rigidbody>(move); 
}

void Scene::init() {
    ecs.registerComponent<Transform>();
    ecs.registerComponent<Physics>();
    ecs.registerComponent<Rigidbody>();

    Entity a = ecs.createEntity();
    a.addComponent<Transform>();
    a.addComponent<Phyisics>();
    a.addComponent<Rigidbody>();

    a.getComponent<Transform>().position = vec2(100, 100);
    a.getComponent<Rigidbody>().velocity = vec2(0, 10);
    a.getComponent<Physics>().gravity = 3.f;
}

void Scene::update() {
    physicsSystem.update(ecs);
}

```
