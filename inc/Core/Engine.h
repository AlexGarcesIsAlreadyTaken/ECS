#ifndef ENGINE_H
#define ENGINE_H

#include "Core/Ecs/Entity.h"
#include "Core/Ecs/Ecs.h"
#include "Core/Ecs/Systems/RenderSystem.h"
#include <GLFW/glfw3.h>

class Engine {
public:
  static Engine* instance() {
		static Engine singleton;
		return &singleton;
	}

  void init();
	void update(float dt);
  void render();

	void keyReleased(int key);
  void keyPressed(int key);

  const bool getKey(int key) const;
	const float deltaTime() const;
    
private:
  Engine() {}

  int keys[GLFW_KEY_LAST];
	float dt;

  Ecs ecs;
  RenderSystem renderSystem;

  Entity entity;
};

#endif
