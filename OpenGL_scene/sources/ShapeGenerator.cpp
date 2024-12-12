#include "ShapeGenerator.h"

bool ShapeGenerator::LoadOBJ(Model m, const char* p)
{
	// Временные массивы для хранения индексов и значений из файла
	std::vector<unsigned int> vertexIndices, vtIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_textures;
	std::vector<glm::vec3> temp_normals;

	// Открытие файла
	std::ifstream file(p, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "Не удалось открыть файл: " << p << std::endl;
		return false;
	}

	// Строка для хранения токенов из файла
	std::string line;

	// Построчное чтение файла, обработка токенов
	while (std::getline(file, line)) {
		std::istringstream sstr(line);	// Поток для текущей строки
		std::string prefix;				// Переменная для префиксов (они опрделяют токен)
		sstr >> prefix;

		// Обработка координат вершин
		if (prefix == "v") {
			glm::vec3 vertex;
			sstr >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		// Обработка текстурных координат
		else if (prefix == "vt") {
			glm::vec2 texture;
			sstr >> texture.x >> texture.y;
			temp_textures.push_back(texture);
		}
		// Обработка нормалей
		else if (prefix == "vn") {
			glm::vec3 normal;
			sstr >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		// Обработка граней
		else if (prefix == "f") {
			//Информация о вершине
			std::vector<unsigned int> vIndices, vtIndicesLocal, vnIndices;
			std::string vertexInfo;

			// Чтение данных о каждой вершине
			while (sstr >> vertexInfo) {
				// Разделение данных вершины
				std::replace(vertexInfo.begin(), vertexInfo.end(), '/', ' ');
				std::istringstream vertexStream(vertexInfo);
				unsigned int vIndex = 0, vtIndex = 0, nIndex = 0;
				vertexStream >> vIndex;
				if (!vertexStream.eof()) vertexStream >> vtIndex;
				if (!vertexStream.eof()) vertexStream >> nIndex;

				// Учитываем, что индексы начинаются с 1
				if (vIndex > 0) vIndices.push_back(vIndex - 1);
				if (vtIndex > 0) vtIndicesLocal.push_back(vtIndex - 1);
				if (nIndex > 0) vnIndices.push_back(nIndex - 1);
			}

			// Преобразование в треугольники (если грань содержит больше трёх вершин)
			for (size_t i = 1; i < vIndices.size() - 1; ++i) {
				vertexIndices.push_back(vIndices[0]);
				vertexIndices.push_back(vIndices[i]);
				vertexIndices.push_back(vIndices[i + 1]);

				if (!vtIndicesLocal.empty()) {
					vtIndices.push_back(vtIndicesLocal[0]);
					vtIndices.push_back(vtIndicesLocal[i]);
					vtIndices.push_back(vtIndicesLocal[i + 1]);
				}

				if (!vnIndices.empty()) {
					normalIndices.push_back(vnIndices[0]);
					normalIndices.push_back(vnIndices[i]);
					normalIndices.push_back(vnIndices[i + 1]);
				}
			}
		}
	}

	// Обязательно закрываем файл, а то продует
	file.close();

	// Генерация выходных массивов
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// Вершины
		m.Vertices.push_back(temp_vertices[vertexIndices[i]]);

		// Нормали
		if (!temp_normals.empty() && i < normalIndices.size()) {
			m.Normals.push_back(temp_normals[normalIndices[i]]);
		}
		else {
			// Нормали по умолчанию, если всё грустно
			m.Normals.emplace_back(0.0f, 0.0f, 0.0f);
		}

		// Текстуры
		if (!temp_textures.empty() && i < vtIndices.size()) {
			m.Textures.push_back(temp_textures[vtIndices[i]]);
		}
		else {
			// Текстурные координаты по умолчанию, если всё грустно
			m.Textures.emplace_back(0.0f, 0.0f);
		}
	}

	// Наконец-то конец нашим страданиям
	return true;
}
