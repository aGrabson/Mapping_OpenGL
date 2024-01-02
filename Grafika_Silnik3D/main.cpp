#include "engine.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float deltaTime = 0.0f;	
float lastFrame = 0.0f;

int main()
{
    Engine engine(1024,576,"Symulacja wypuklosci",NULL);

    glfwSetFramebufferSizeCallback(engine.getWindow(), framebuffer_size_callback);
    engine.setBackgroundColor(0, 0, 0, 10);
    engine.mainLoop();
    glfwTerminate();
    return 0;
}
