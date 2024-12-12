#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>

/// <summary>
/// Класс модели
/// </summary>
class Model
{
public:
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> Textures;
	std::vector<glm::vec3> Normals;
};
#pragma region Structures

struct Material
{

};

struct Light
{

};

#pragma endregion
