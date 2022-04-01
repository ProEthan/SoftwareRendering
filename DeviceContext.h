#pragma once

#include<glm/glm.hpp>
#include<iostream>
#include<vector>

#include "Vertex.h"

class DeviceContest
{
public:
	~DeviceContest();

	void SetInputLayout(InputLayout* pil);
	void SetShaderProgram();
	void SetVertexBuffer(UINT StartSloat, UINT NumBuffers, VertexBuffer* ppvb, UINT* pStrides, UINT* pOffset);
	void Draw(UINT vertexCount, UINT startLoc);
	std::vector<Vertex> GetVertices();

private:
	InputLayout* inputLayout;

	float* _positions;
	float* _colors;
	float* _texcoords;
	float* _normals;

	std::vector<Vertex> _vertexs;
};

DeviceContest::~DeviceContest()
{
	delete _positions;
	delete _colors;
	delete _texcoords;
	delete _normals;
}

std::vector<Vertex> DeviceContest::GetVertices() {
	return _vertexs;
}

void DeviceContest::SetInputLayout(InputLayout* pil) {
	inputLayout = pil;
}

void DeviceContest::SetVertexBuffer(UINT StartSloat, UINT NumBuffers, VertexBuffer* ppvb, UINT* pStrides, UINT* pOffset) {
	Vertex vertex;
	int verticesNum = (ppvb)->verticesNum;
	if (inputLayout->position != NULL) {
		_positions = new float[4 * verticesNum];
		for (int j = 0;j < verticesNum;j++) {
			glm::vec4 position;
			for (int k = 0;k < 4;k++) {
				*(_positions + j * 4 + k) = *((ppvb)->bufferData + j * inputLayout->size + inputLayout->offset[0] + k);
				position[k] = *(_positions + j * 4 + k);
			}
			vertex.SetPosition(position);
			_vertexs.push_back(vertex);
		}
	}
	if (inputLayout->color != NULL) {
		_colors = new float[4 * verticesNum];
		for (int j = 0;j < verticesNum;j++) {
			glm::vec4 color;
			for (int k = 0;k < 4;k++) {
				*(_colors + j * 4 + k) = *((ppvb)->bufferData + j * inputLayout->size + inputLayout->offset[1] + k);
				color[k] = *(_colors + j * 4 + k);
			}
			_vertexs[j].SetColor(color);
		}
	}
	if (inputLayout->texcoord != NULL) {
		_texcoords = new float[2 * verticesNum];
		for (int j = 0;j < verticesNum;j++) {
			glm::vec2 texcoord;
			for (int k = 0;k < 2;k++) {
				*(_texcoords + j * 2 + k) = *((ppvb)->bufferData + j * inputLayout->size + inputLayout->offset[2] + k);
				texcoord[k] = *(_texcoords + j * 2 + k);
			}
			_vertexs[j].SetTexcoord(texcoord);
		}
	}
	if (inputLayout->normal != NULL) {
		_normals = new float[3 * verticesNum];
		for (int j = 0;j < verticesNum;j++) {
			glm::vec3 normal;
			for (int k = 0;k < 3;k++) {
				*(_normals + j * 3 + k) = *((ppvb)->bufferData + j * inputLayout->size + inputLayout->offset[3] + k);
				normal[k] = *(_normals + j * 3 + k);
			}
			_vertexs[j].SetNormal(normal);
		}
	}
}

void DeviceContest::Draw(UINT vertexCount, UINT startLoc) {

}

void DeviceContest::SetShaderProgram() {

}