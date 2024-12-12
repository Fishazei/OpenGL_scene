#pragma once
#include <Model.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

static class ShapeGenerator
{
public:
	/// <summary>
	/// Загрузка моделей из .obj файлов 
	/// </summary>
	/// <param name="m">Модель, в которую загружается набор вершин</param>
	/// <param name="p">Путь до файла</param>
	/// <returns></returns>
	static bool LoadOBJ(Model m, const char* p);
private:

	static bool LoadToModel();
};

