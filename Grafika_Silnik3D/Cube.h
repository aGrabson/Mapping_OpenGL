#pragma once
#ifndef cube_h
#define cube_h
#include <glad/glad.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <ext/matrix_transform.hpp>
/**
 * @brief Klasa sześcianu
 * 
 */
class Cube
{
protected:
/**
 * @brief matryca sześcianów z pozycją, pozycją tekstury oraz wektory normalne
 * 
 */
	float vertices[504] = {

 0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f, 0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	};
	
	unsigned int VBO, VAO, EBO;
	/**
	 * @brief pozycja
	 * 
	 */
	glm::vec3 position;
	/**
	 * @brief współczynnik skalowania
	 * 
	 */
	glm::vec3 scalingFactor;
	/**
	 * @brief kąt obrotu w osi X
	 * 
	 */
	float rotationAngleX=0;
	/**
	 * @brief kąt obrotu w osi Y
	 * 
	 */
	float rotationAngleY=0;
	/**
	 * @brief kąt obrotu w osi Z
	 * 
	 */
	float rotationAngleZ=0;
public:

/**
 * @brief Konstruktor z parametrami klasy szescian
 * 
 * @param point pozycja 
 * @param color kolor sześcianu
 */
	Cube(glm::vec3 point, glm::vec3 color)
	{
		scalingFactor = glm::vec3(1.0, 1.0, 1.0);
		position = point;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
		
		unsigned int indices[] = {
0, 1, 2, 3, 4, 5,
6, 7, 8, 9, 10, 11,
12, 13, 14, 15, 16, 17,
18, 19, 20, 21, 22, 23,
24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35
		};
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	/**
	 * @brief Rysowanie sześcianu
	 * 
	 * @param programShader id shadera
	 * @param texture id tekstury
	 * @param textureNum numer tekstury
	 */
	void draw(unsigned int programShader, unsigned int texture, int textureNum);
	/**
	 * @brief Ustawia matryce sześcianu
	 * 
	 * @param vertices matryca sześcianu
	 */
	void setVertices(float vertices[]);
	/**
	 * @brief pobiera matrycę sześcianu
	 * 
	 * @return matryca sześcianu
	 */
	float* getVertices();
	/**
	 * @brief przesunięcie sześcianu o wektor
	 * 
	 * @param translation wektor przesunięcia
	 */
	void translate(glm::vec3 translation);
	/**
	 * @brief obrót w osi x
	 * 
	 * @param angle kąt obrotu
	 */
	void rotateX(float angle);
		/**
	 * @brief obrót w osi y
	 * 
	 * @param angle kąt obrotu
	 */
	void rotateY(float angle);
		/**
	 * @brief obrót w osi z
	 * 
	 * @param angle kąt obrotu
	 */
	void rotateZ(float angle);
	/**
	 * @brief przeskaluj sześcian
	 * 
	 * @param współczynnik
	 */
	void scale(float k);
	/**
	 * @brief Pobiera pozycję sześcianu
	 * 
	 * @return pozycja sześcianu
	 */
	glm::vec3 getPosition();
	/**
	 * @brief pobiera swpółczynnik skalowania
	 * 
	 * @return współczynnik skalowania
	 */
	glm::vec3 getScalingFactor();
	/**
	 * @brief Ustawia pozycję sześcianu
	 * 
	 * @param wektor pozycji
	 */
	void setPosition(glm::vec3 position);
	/**
	 * @brief Zwraca obrót w osi x 
	 * 
	 * @return obrót w osi x
	 */
	float getRotX();
	/**
	 * @brief Zwraca obrót w osi y 
	 * 
	 * @return obrót w osi y
	 */
	float getRotY();
	/**
	 * @brief Zwraca obrót w osi z 
	 * 
	 * @return obrót w osi z
	 */
	float getRotZ();
	
};

#endif // !cube_h