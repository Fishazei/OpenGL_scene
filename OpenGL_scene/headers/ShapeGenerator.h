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
	/// �������� ������� �� .obj ������ 
	/// </summary>
	/// <param name="m">������, � ������� ����������� ����� ������</param>
	/// <param name="p">���� �� �����</param>
	/// <returns></returns>
	static bool LoadOBJ(Model m, const char* p);
private:

	static bool LoadToModel();
};

