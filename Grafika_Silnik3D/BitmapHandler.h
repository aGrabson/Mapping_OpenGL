#pragma once
#ifndef BitmapHandler_h
#define BitmapHandler_h
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "stb_image.h"

/**
 * @brief Klasa odpowiadająca za obsługę bitmap
 * 
 */
class BitmapHandler {
public:
/**
 * @brief Konstruktor obiektu BitmapHandler
 * 
 */
	BitmapHandler(){}
	/**
	 * @brief Funkcja, która ładuje teksture i zwraca jej id
	 * 
	 * @param path Ścieżka do pliku
	 * @return unsigned int id textury
	 */
	unsigned int loadTexture(char const* path);
};

#endif BitmapHandler_h