#include "ShapeGenerator.h"

bool ShapeGenerator::LoadOBJ(Model m, const char* p)
{
	// ��������� ������� ��� �������� �������� � �������� �� �����
	std::vector<unsigned int> vertexIndices, vtIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_textures;
	std::vector<glm::vec3> temp_normals;

	// �������� �����
	std::ifstream file(p, std::ios::in);
	if (!file.is_open()) {
		std::cerr << "�� ������� ������� ����: " << p << std::endl;
		return false;
	}

	// ������ ��� �������� ������� �� �����
	std::string line;

	// ���������� ������ �����, ��������� �������
	while (std::getline(file, line)) {
		std::istringstream sstr(line);	// ����� ��� ������� ������
		std::string prefix;				// ���������� ��� ��������� (��� ��������� �����)
		sstr >> prefix;

		// ��������� ��������� ������
		if (prefix == "v") {
			glm::vec3 vertex;
			sstr >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		// ��������� ���������� ���������
		else if (prefix == "vt") {
			glm::vec2 texture;
			sstr >> texture.x >> texture.y;
			temp_textures.push_back(texture);
		}
		// ��������� ��������
		else if (prefix == "vn") {
			glm::vec3 normal;
			sstr >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		// ��������� ������
		else if (prefix == "f") {
			//���������� � �������
			std::vector<unsigned int> vIndices, vtIndicesLocal, vnIndices;
			std::string vertexInfo;

			// ������ ������ � ������ �������
			while (sstr >> vertexInfo) {
				// ���������� ������ �������
				std::replace(vertexInfo.begin(), vertexInfo.end(), '/', ' ');
				std::istringstream vertexStream(vertexInfo);
				unsigned int vIndex = 0, vtIndex = 0, nIndex = 0;
				vertexStream >> vIndex;
				if (!vertexStream.eof()) vertexStream >> vtIndex;
				if (!vertexStream.eof()) vertexStream >> nIndex;

				// ���������, ��� ������� ���������� � 1
				if (vIndex > 0) vIndices.push_back(vIndex - 1);
				if (vtIndex > 0) vtIndicesLocal.push_back(vtIndex - 1);
				if (nIndex > 0) vnIndices.push_back(nIndex - 1);
			}

			// �������������� � ������������ (���� ����� �������� ������ ��� ������)
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

	// ����������� ��������� ����, � �� �������
	file.close();

	// ��������� �������� ��������
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// �������
		m.Vertices.push_back(temp_vertices[vertexIndices[i]]);

		// �������
		if (!temp_normals.empty() && i < normalIndices.size()) {
			m.Normals.push_back(temp_normals[normalIndices[i]]);
		}
		else {
			// ������� �� ���������, ���� �� �������
			m.Normals.emplace_back(0.0f, 0.0f, 0.0f);
		}

		// ��������
		if (!temp_textures.empty() && i < vtIndices.size()) {
			m.Textures.push_back(temp_textures[vtIndices[i]]);
		}
		else {
			// ���������� ���������� �� ���������, ���� �� �������
			m.Textures.emplace_back(0.0f, 0.0f);
		}
	}

	// �������-�� ����� ����� ����������
	return true;
}
