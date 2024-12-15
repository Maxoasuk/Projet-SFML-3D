#ifndef OBJECT_H__
#define OBJECT_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Object {
	unsigned int VBO;
	unsigned int VAO;

	std::vector<float> all;

	void setData(void* _data, size_t _dataSize);
	std::vector<glm::vec3> GenerateNormal(std::vector<glm::vec3>& vertices);

public:
	Object(void * _data, size_t _dataSize);
	Object(std::string _path);
	~Object();
	
	void SetVertexAttribute(int _locationID, int _dimension, int _type, GLsizei _sizeByteVertex, void* _startOffSet);
	void draw(GLenum _drawnmode, int _startVertex, int _nbvertex);
};

#endif

