#pragma once

#include "Vertex.h"

#include<iostream>

struct ATTRS{
	unsigned char M_POSITION = 0;
	unsigned char M_COLOR = 1;
	unsigned char M_NORMAL = 2;
    unsigned char M_TEXCOORD = 3;
}ATTR_ARRAY;

class MVertexBuffer
{
public:
	MVertexBuffer();
	~MVertexBuffer();

    void mEnableVertexAttribArray(unsigned char attr);
    void mVertexAttribPointer(unsigned int start, unsigned int size, unsigned int unitNumber);
    void mGenVertexArray(unsigned int num, unsigned int* VAO);
    void mGenBuffers(unsigned int num, unsigned int* VBO);
    void mBindVertexArray(unsigned int VAO);
    void mBindBuffer(unsigned int VBO);
    void mBufferData(unsigned int size, float vertices[]);
    std::vector<Vertex> GetVertexs();

private:
    unsigned int* _VAO;
    unsigned int* _VBO;

	std::vector<Vertex> _vertexs;

    float* _vertices;

	unsigned char _attr;

    unsigned int _size;
};

MVertexBuffer::MVertexBuffer()
{
}

MVertexBuffer::~MVertexBuffer()
{
    delete _vertices;
}

std::vector<Vertex> MVertexBuffer::GetVertexs() {
    return _vertexs;
}

void MVertexBuffer::mEnableVertexAttribArray(unsigned char attr) {
    _attr = attr;
}

void MVertexBuffer::mVertexAttribPointer(unsigned int start, unsigned int size, unsigned int unitNumber) {
    Vertex vertex;
    int len = _size / (unitNumber * sizeof(float));
    for (int i = 0;i < len;i++) {
        if (_attr == ATTR_ARRAY.M_POSITION) {
            glm::vec4 v4 = glm::vec4(_vertices[unitNumber * i + start], _vertices[unitNumber * i + 1 + start], _vertices[unitNumber * i + 2 + start], _vertices[unitNumber * i + 3 + start]);
            vertex.SetPosition(v4);
            _vertexs.push_back(vertex);
        }
        else if (_attr == ATTR_ARRAY.M_COLOR) {
            glm::vec4 v4 = glm::vec4(_vertices[unitNumber * i + start], _vertices[unitNumber * i + 1 + start], _vertices[unitNumber * i + 2 + start], _vertices[unitNumber * i + 3 + start]);
            _vertexs[i].SetColor(v4);

        }
        else if (_attr == ATTR_ARRAY.M_NORMAL) {
            glm::vec3 v3 = glm::vec3(_vertices[unitNumber * i + start], _vertices[unitNumber * i + 1 + start], _vertices[unitNumber * i + 2 + start]);
            _vertexs[i].SetNormal(v3);
        }
        else if (_attr == ATTR_ARRAY.M_TEXCOORD) {
            glm::vec2 v2 = glm::vec2(_vertices[unitNumber * i + start], _vertices[unitNumber * i + 1 + start]);
            _vertexs[i].SetTexcoord(v2);
        }
    }
}


void MVertexBuffer::mGenVertexArray(unsigned int num, unsigned int* VAO) {
    *VAO = num;
    _VAO = new unsigned int(*VAO);
}

void MVertexBuffer::mGenBuffers(unsigned int num, unsigned int* VBO) {
    *VBO = num;
    _VBO = new unsigned int(*VBO);
}

void MVertexBuffer::mBindVertexArray(unsigned int VAO) {
    if (VAO == 0) {
        delete _VAO;
        _VAO = NULL;
    }
    else {
        return;
    }
}

void MVertexBuffer::mBindBuffer(unsigned int VBO) {
    if (VBO == 0) {
        delete _VBO;
        _VBO = NULL;
    }
    else {
        return;
    }
}

void MVertexBuffer::mBufferData(unsigned int size, float vertices[]) {
    _size = size;
    float ttt;
    _vertices = new float[size * sizeof(float)];
    unsigned int n = size / sizeof(float);
    for (int i = 0; i < n; i++) {
        *(_vertices + i) = vertices[i];
        ttt = *(_vertices + i);
    }
}