#include "glad/glad.h"
#include "Utils/Logger.h"
#include "Utils/Window.h"
#include "Core/Engine.h"
#include <GLFW/glfw3.h>


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) Engine::instance()->keyPressed(key);
	else if (action == GLFW_RELEASE) Engine::instance()->keyReleased(key);
}

int main() {
    LOGGER_ASSERT(glfwInit(), "GLFW could not be initialized");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		int width = 640;
    GLFWwindow *window = glfwCreateWindow(width, width / aspect_ratio, "ECS", nullptr, nullptr);
    LOGGER_ASSERT(window, "Window or OpenGL context creation failed");
    
    glfwMakeContextCurrent(window);
    
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    
    glfwSetKeyCallback(window, key_callback);

		double previousTime = glfwGetTime();


    Engine::instance()->init();

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);

				double time = glfwGetTime();
				float dt = time - previousTime;
				Engine::instance()->update(dt);
				previousTime = time;

				if (Engine::instance()->getKey(GLFW_KEY_ESCAPE)) {
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}

        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
