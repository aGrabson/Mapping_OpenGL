#pragma once
#ifndef point3d_h
#define point3d_h
#include <glad/glad.h>
#include <glm.hpp>
#include <GLFW/glfw3.h>

/**
 * @brief Klasa reprezentująca punkt 3D
 * 
 */
class Point3D
{
private:
/**
 * @brief Tablica przechowująca informacje o wspołrzędnych punktu 3D
 * 
 */
	float vertices[3];
	unsigned int VAO, VBO;
public:
/**
 * @brief Konstruktor klasy Point3D
 * 
 * @param vertices Tablica zawierająaca informacje o współrzędnych punktu 3D
 */
	Point3D(float vertices[])
	{
		for (int i = 0; i < 3; i++)
		{
			this->vertices[i] = vertices[i];
		}
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	/**
	 * @brief Zwraca współrzędną X
	 * 
	 * @return float 
	 */
	float getX();
	/**
	 * @brief Zwraca współrzędną Y
	 * 
	 * @return float 
	 */
	float getY();
	/**
	 * @brief Zwraca współrzędną Z
	 * 
	 * @return float 
	 */
	float getZ();
	/**
	 * @brief Ustawia współrzędną X
	 * 
	 * @param x Nowa współrzędna X
	 */
	void setX(float x);
	/**
	 * @brief Ustawia współrzędną Y
	 * 
	 * @param x Nowa współrzędna Y
	 */
	void setY(float y);
	/**
	 * @brief Ustawia współrzędną Z
	 * 
	 * @param x Nowa współrzędna Z
	 */
	void setZ(float z);
	/**
	 * @brief Zwraca wektor współrzędnych punktu 
	 * 
	 * @return glm::vec3 
	 */
	glm::vec3 getVec();
	/**
	 * @brief Ustawia wektor współrzędnych punktu
	 * 
	 * @param vec Nowy wektor współrzędnych punktu
	 */
	void setVec(glm::vec3 vec);
	/**
	 * @brief Funkcja rysująca punkt 3D
	 * 
	 */
	void draw();
};
#endif // !point3d_h
