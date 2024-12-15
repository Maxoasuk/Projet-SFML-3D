#include "Object.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>

void Object::setData(void* _data, size_t _dataSize) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // specify variable type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _dataSize, _data, GL_STATIC_DRAW); // GL_DYNAMIC_DRAW, GL_STREAM_DRAW

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

Object::Object(void* _data, size_t _dataSize) {
    this->setData(_data, _dataSize);
}

Object::Object(std::string _path) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;

    std::vector<glm::vec3> verticesOrders;
    std::vector<glm::vec2> texturesOrders;
    std::vector<glm::vec3> normalsOrders;

    std::vector<std::string> points;
    try {
        std::ifstream objectFile;

        objectFile.open(_path);

        for (std::string line; std::getline(objectFile, line);) {
            std::stringstream split(line);

            std::string token;
            split >> token;

            if (token == "v") {
                float x;
                float y;
                float z;
                split >> x >> y >> z;
                vertices.push_back(glm::vec3(x, y, z));
            } 
            else if (token == "vt") {
                float x;
                float y;
                split >> x >> y;
                textures.push_back(glm::vec2(x, y));
            }
            else if (token == "vn") {
                float x;
                float y;
                float z;
                split >> x >> y >> z;
                normals.push_back(glm::vec3(x, y, z));
            }
            else if (token == ("f")) {
                std::string c;
                while (split >> c) {
                    points.push_back(c);                    
                }
            }
        }
        objectFile.close();

        for (int i = 0; i < points.size(); ++i) {
            std::stringstream split2(points[i]);

            std::string idV; std::getline(split2, idV, '/');

            verticesOrders.push_back(vertices[std::stoi(idV) - 1]);
              
            std::string idVt;
            if (std::getline(split2, idVt, '/')) {
                texturesOrders.push_back(textures[std::stoi(idVt) - 1]);
            }
            std::string idVn;
            if (std::getline(split2, idVn, '/')) {
                normalsOrders.push_back(normals[std::stoi(idVn) - 1]);
            }
        }

        if (normalsOrders.size() == 0) {
            normalsOrders = this->GenerateNormal(verticesOrders);
        }

        for (int i = 0; i < points.size(); ++i) {
            all.push_back(verticesOrders[i].x);
            all.push_back(verticesOrders[i].y);
            all.push_back(verticesOrders[i].z);

            if (texturesOrders.size() != 0) {
                all.push_back(texturesOrders[i].x);
                all.push_back(texturesOrders[i].y);
            }

            all.push_back(normalsOrders[i].x);
            all.push_back(normalsOrders[i].y);
            all.push_back(normalsOrders[i].z);
        }
        
       // for (int i = 0; i < vertices.size(); ++i) {
       //     std::cout << vertices[i] << ", ";
       // }
       // std::cout << std::endl;
        
        setData(all.data(), all.size() * sizeof(float));
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR : File can't be read" << e.what() << std::endl;
    }
}

Object::~Object() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Object::SetVertexAttribute(int _locationID, int _dimension, int _type, GLsizei _sizeByteVertex, void* _startOffSet) {
    glBindVertexArray(VAO);

    // specify variable type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(_locationID, _dimension, _type, GL_FALSE, _sizeByteVertex, _startOffSet);
    glEnableVertexAttribArray(_locationID);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Object::draw(GLenum _drawnmode, int _startVertex, int _nbvertex) {
    glBindVertexArray(VAO);
    glDrawArrays(_drawnmode, _startVertex, _nbvertex);
    glBindVertexArray(0);
}

std::vector<glm::vec3> Object::GenerateNormal(std::vector<glm::vec3>& vertices) {
    std::vector<glm::vec3> normals;
    for (int i = 0; i < vertices.size(); i+=3) {
        glm::vec3 p1 = vertices[i];
        glm::vec3 p2 = vertices[i + 1];
        glm::vec3 p3 = vertices[i + 2];

        glm::vec3 u = p2 - p1;
        glm::vec3 v = p3 - p1;

        glm::vec3 normal = glm::cross(u, v);

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }
    return normals;
}