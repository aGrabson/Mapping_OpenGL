#include "engine.h"
namespace sf = std::filesystem;
Engine* Engine::instance = NULL;
void Engine::init()
{
    glfwSetWindowSizeLimits(getWindow(), 1024, 576, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwMakeContextCurrent( this->getWindow() );
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
	}
}
void Engine::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		isFullscreen(true);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		isFullscreen(false);
	float cameraSpeed = static_cast<float>(6.0 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->VerticalMove(true, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->VerticalMove(false, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->HorizontalMove(false, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->HorizontalMove(true, cameraSpeed);	
	static int keyState = GLFW_RELEASE;

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && keyState == GLFW_RELEASE) {
		changeMapping();
		keyState = GLFW_PRESS;
	}

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE && keyState == GLFW_PRESS) {
		keyState = GLFW_RELEASE;
	}
}
void Engine::changeMapping() {
	Engine* eng = Engine::getInstance();
	if (eng->state)
	{
		eng->state = false;
	}
	else
	{
		eng->state = true;
	}
}
void Engine::setWindowSize(unsigned int width, unsigned int height)
{
	glfwSetWindowSize(this->window, width, height);
}
void Engine::isFullscreen(bool fullscreen)
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (fullscreen)
	{
		glfwSetWindowMonitor(this->window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(this->window, NULL, mode->width *0.1, mode->height *0.1, mode->width *0.8, mode->height *0.8, mode->refreshRate);
	}
}
GLFWwindow* Engine::getWindow()
{
	return this->window;
}
void Engine::setBackgroundColor(float r, float g, float b, float a)
{
    backgroundColor.r = r/255;
    backgroundColor.g = g/255;
    backgroundColor.b = b/255;
    backgroundColor.a = a/255;
}
void Engine::mainLoop()
{
	glm::vec3 blue(0.0f, 0.0f, 1.0f);
	glm::vec3 pos14(0.0f, 0.0f, 0.0f);
	Cube testcube(pos14, blue);
	

	float respawnTimer = 1.2f;
	float time = 0.0f;
	std::string parentDir = (sf::current_path().sf::path::parent_path()).string();

	std::string texBrickwall = "\\resources\\textures\\brickwall.jpg";
	unsigned int brickwall = bitmapHandler->loadTexture((parentDir + texBrickwall).c_str());

	std::string texNormalMap = "\\resources\\textures\\normal_map.jpg";
	unsigned int normalMap = bitmapHandler->loadTexture((parentDir + texNormalMap).c_str());

	glUniform1i(glGetUniformLocation(programShader2, "diffuseMap"), 0);
	glUniform1i(glGetUniformLocation(programShader2, "normalMap"), 1);

	testcube.scale(16);
	
	glm::vec3 lightPos(0.0f, -3.0f, 0.0f);
	Cube light(lightPos, blue);

	glEnable(GL_TEXTURE_2D);
    while (!glfwWindowShouldClose(getWindow()))
    {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        processInput();
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Engine* eng = Engine::getInstance();

			glUseProgram(programShader2);
			glUniform3f(glGetUniformLocation(programShader2, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(programShader2, "viewPos"), camera->getCameraPos().x, camera->getCameraPos().y, camera->getCameraPos().z);
			glUniform1i(glGetUniformLocation(programShader2, "useNormalMapping"), eng->state ? 1 : 0);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, brickwall);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, normalMap);
			testcube.draw(programShader2, brickwall, 2);
			glUseProgram(programShader2);

			light.draw(programShader2, brickwall, 2);

		time += deltaTime;

		camera->UpdateCamera(programShader2,programShader2);

		glfwSwapBuffers(getWindow());
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(programShader2);
    glfwTerminate();
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	Engine* eng = Engine::getInstance();
	eng->getCamera()->UpdateMouse(xpos, ypos);
}

void MouseButtonCallback(GLFWwindow* window,int button, int action, int mods)
{
	Engine* eng = Engine::getInstance();
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{

	}

}