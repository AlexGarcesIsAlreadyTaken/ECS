 #include "Core/Engine.h"

void Engine::keyReleased(int key) {
	this->keys[key] = false;
}

void Engine::keyPressed(int key) {
	this->keys[key] = true;
}

void Engine::update(float dt) {
	this->dt = dt;
}

const float Engine::deltaTime() const {
	return this->dt;
}

const bool Engine::getKey(int key) const {
	return this->keys[key];
}
