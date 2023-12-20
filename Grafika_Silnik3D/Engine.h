#pragma once
#ifndef engine_h
#define engine_h
#include <string>
#include "Point3D.h"
#include "Camera.h"
#include "BitmapHandler.h"
#include <time.h>
#include <filesystem>
#include "Cube.h"
/**
 * @brief Metoda wyzwalająca callback myszki
 * 
 * @param window okno aplikacji
 * @param xpos pozycja x myszy
 * @param ypos pozycja y myszy
 */
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
/**
 * @brief Metoda wyzwalająca callback lkawiatury
 * 
 * @param window kno aplikacji
 * @param button przycisk
 * @param action akcja
 * @param mods tryb wciśnięcia
 */
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

/**
 * @brief główna klasa Engine
 * 
 */
class Engine
{
private:
	/*!<Wskaźnik na kamerę*/
	Camera* camera;
	/*!<Wskaźnik na handlera bitmap*/
	BitmapHandler* bitmapHandler;
	/*!<Wskaźnik na intancję silnika*/
	static Engine* instance;
	/*!<Wskaźnik na okno aplikacji*/
	GLFWwindow* window;
	/*!<Wskaźnik na monitor*/
	GLFWmonitor* monitor;
	/*<! Szerokość ekranu*/
	unsigned int screenWidth;
	/*!<Wysokość ekranu*/
	unsigned int screenHeight;
	/*!<Czas pomiędzy klatkami*/
	float deltaTime;
	/*<!Czas ostatniej klatki*/
	float lastFrame;

	/*!<Macierz projekcji*/
	glm::mat4 projection;
	/*!<Kolor tła*/
	glm::vec4 backgroundColor = glm::vec4(0.0f,0.0f,1.0f,0.1f);

	const char* vertexBumpMappingShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aNormal;\n"
		"layout (location = 2) in vec2 aTexCoords;\n"
		"layout (location = 3) in vec3 aTangent;\n"
		"layout (location = 4) in vec3 aBitangent;\n"
		
		"out VS_OUT {\n"
		"    vec3 FragPos;\n"
		"    vec2 TexCoords;\n"
		"    vec3 TangentLightPos;\n"
		"    vec3 TangentViewPos;\n"
		"    vec3 TangentFragPos;\n"
		"	 flat int useNormalMapping;\n"
		"} vs_out;\n"
		"\n"
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 model;\n"
		"\n"
		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;\n"
		"uniform int useNormalMapping;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));   \n"
		"    vs_out.TexCoords = aTexCoords;\n"
		"    \n"
		"    mat3 normalMatrix = transpose(inverse(mat3(model)));\n"
		"    vs_out.useNormalMapping = useNormalMapping;\n"
		"	 if (useNormalMapping == 1)\n"
		"	 {\n"
		"		vec3 T = normalize(normalMatrix * aTangent);\n"
		"		vec3 N = normalize(normalMatrix * aNormal);\n"
		"		T = normalize(T - dot(T, N) * N);\n"
		"		vec3 B = cross(N, T);\n"
		"		\n"
		"		mat3 TBN = transpose(mat3(T, B, N));    \n"
		"		vs_out.TangentLightPos = TBN * lightPos;\n"
		"		vs_out.TangentViewPos  = TBN * viewPos;\n"
		"		vs_out.TangentFragPos  = TBN * vs_out.FragPos;\n"
		"    } else\n"
		"	 {\n"
		"		vs_out.TangentLightPos = lightPos;\n"
		"		vs_out.TangentViewPos = viewPos;\n"
		"		vs_out.TangentFragPos = vs_out.FragPos;\n"
		"	 }\n"
		"    \n"
		"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
		"}\0";

	const char* fragmentBumpMappingShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"in VS_OUT {\n"
		"    vec3 FragPos;\n"
		"    vec2 TexCoords;\n"
		"    vec3 TangentLightPos;\n"
		"    vec3 TangentViewPos;\n"
		"    vec3 TangentFragPos;\n"
		"	 flat int useNormalMapping;\n"
		"} fs_in;\n"
		"\n"
		"uniform sampler2D diffuseMap;\n"
		"uniform sampler2D normalMap;\n"
		"\n"
		"uniform vec3 lightPos;\n"
		"uniform vec3 viewPos;\n"
		"\n"
		"void main()\n"
		"{           \n"
		"     // obtain normal from normal map in range [0,1]\n"
		"    vec3 normal;\n"
		"	 if (fs_in.useNormalMapping == 1)\n"
		"	 {\n"
		"		normal = texture(normalMap, fs_in.TexCoords).rgb;\n"
		"		normal = normalize(normal * 2.0 - 1.0);\n"
		"	 }\n"
		"	 else\n"
		"	 {\n"
		"		normal = normalize(cross(dFdx(fs_in.FragPos), dFdy(fs_in.FragPos)));\n"
		"	 }\n"
		"   \n"
		"    // get diffuse color\n"
		"    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;\n"
		"    // ambient\n"
		"    vec3 ambient = 0.1 * color;\n"
		"    // diffuse\n"
		"    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);\n"
		"    float diff = max(dot(lightDir, normal), 0.0);\n"
		"    vec3 diffuse = diff * color;\n"
		"    // specular\n"
		"    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);\n"
		"    vec3 reflectDir = reflect(-lightDir, normal);\n"
		"    vec3 halfwayDir = normalize(lightDir + viewDir);  \n"
		"    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);\n"
		"\n"
		"    vec3 specular = vec3(0.2) * spec;\n"
		"    FragColor = vec4(ambient + diffuse + specular, 1.0);\n"
		"}\0";
		unsigned int programShader2;
		unsigned int VBO, VAO;
		unsigned int vertexBumpMappingShader;
		unsigned int fragmentBumpMappingShader;
public:
	bool state = true;

	/**
	 * @brief Konstruktor klasy Engine
	 * 
	 * @param width szerokość
	 * @param height wysokość
	 * @param Title tytuł okna
	 * @param monitor wskaźnik na monitor
	 */
	Engine(unsigned int width, unsigned int height, std::string Title, GLFWmonitor* monitor)
	{
		
		this->instance = this;
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//glEnable(GL_DEPTH_TEST);
		this->window = glfwCreateWindow(width, height, Title.c_str(), monitor, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		init();
		
		int success;
		char infoLog[512];
		glEnable(GL_DEPTH_TEST);

		vertexBumpMappingShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexBumpMappingShader, 1, &vertexBumpMappingShaderSource, NULL);
		glCompileShader(vertexBumpMappingShader);
		glGetShaderiv(vertexBumpMappingShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexBumpMappingShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		fragmentBumpMappingShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentBumpMappingShader, 1, &fragmentBumpMappingShaderSource, NULL);
		glCompileShader(fragmentBumpMappingShader);
		glGetShaderiv(fragmentBumpMappingShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentBumpMappingShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}



		programShader2 = glCreateProgram();
		glAttachShader(programShader2, vertexBumpMappingShader);
		glAttachShader(programShader2, fragmentBumpMappingShader);
		glLinkProgram(programShader2);
		glGetProgramiv(programShader2, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(programShader2, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		
		glDeleteShader(vertexBumpMappingShader);
		glDeleteShader(fragmentBumpMappingShader);



		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
     	this->screenHeight = height;
		this->screenWidth = width;
		this->monitor = monitor;
		camera = new Camera(width, height,programShader2, window);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetCursorPosCallback(window, MouseCallback);
		
	}
	/**
	 * @brief ustawia rozmiar ekranu 
	 * 
	 * @param width szerokość okna
	 * @param height wysokość okna
	 */
	void setWindowSize(unsigned int width, unsigned int height);
	/**
	 * @brief przełącza pełny ekran
	 * 
	 * @param fullscreen czy włączyć czy wyłączyć
	 */
	void isFullscreen(bool fullscreen);
	/**
	 * @brief inicjacja silnika
	 * 
	 */
	void init();
	/**
	 * @brief przetwarzanie urządzeń wejścia
	 * 
	 */
	void processInput();
	/**
	 * @brief główna pętla gry
	 * 
	 */
	void mainLoop();
	/**
	 * @brief Ustawia kolor tła
	 * 
	 * @param r intensywność czerwonego
	 * @param g intensywność zielonego
	 * @param b intensywność niebieskiego
	 * @param a kanał alfa
	 */
	void setBackgroundColor(float r,float g,float b,float a);
	/**
	 * @brief generowanie sześcianów
	 * 
	 */
	void generateCube();
	/**
	 * @brief pobieranie instancji klasy
	 * 
	 * @return wskaźnik na klasę engine 
	 */
	static Engine* getInstance()
	{
		return instance;
	}
	/**
	 * @brief pobieranie wskaźnika na kamerę
	 * 
	 * @return wskaźnik na kamerę 
	 */
	Camera* getCamera()
	{
		return camera;
	}
	/**
	 * @brief pobieranie wskaźnika na okno
	 * 
	 * @return wskaźnik na okno 
	 */
	GLFWwindow* getWindow();
	void changeMapping();
};
#endif // !engine_h
