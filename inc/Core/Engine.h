#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>

class Engine {
public:
  static Engine* instance() {
		static Engine singleton;
		return &singleton;
	}

	void update(float dt);

	void keyReleased(int key);
  void keyPressed(int key);

  const bool getKey(int key) const;
	const float deltaTime() const;
    
private:
  int keys[GLFW_KEY_LAST];
	float dt;
};

#endif
