#pragma once

#include "VertexBuffer.h"
#include "InputLayout.h"
#include "DESC.h"

struct SampleVertex {
	float x, y, z, w;
	float u, v;
	float nx, ny, nz;
};

class Device
{
public:
	Device();
	~Device();

	void CreateBuffer(BUFFER_DESC* pdb, SUBRESOURCE_DATA* srd, VertexBuffer** ppvb);
	void CreateShaderProgram();
	void CreateInputLayout(INPUT_ELEMENT_DESC* ped, UINT num, InputLayout** ppil);

private:

};

Device::Device()
{
}

Device::~Device()
{
}

void Device::CreateShaderProgram() {

}


void Device::CreateBuffer(BUFFER_DESC* pdb, SUBRESOURCE_DATA* srd, VertexBuffer** ppvb) {
	UINT biteWidth = pdb->ByteWidth;
	(*ppvb)->bufferData = new float[biteWidth / sizeof(float)];
	(*ppvb)->verticesNum = biteWidth / sizeof(SampleVertex);
	memcpy((*ppvb)->bufferData, srd->pSysMem, biteWidth);
}

void Device::CreateInputLayout(INPUT_ELEMENT_DESC* ped, UINT num, InputLayout** ppil) {
	UINT size = 0;
	for (int i = 0;i < num;i++) {
		if ((*(ped + i)).SemanticName == "POSITION") {
			(*ppil)->position = new float[4];
			(*ppil)->offset[0] = size;
			size += 4;
		}
		else if ((*(ped + i)).SemanticName == "COLOR") {
			(*ppil)->color = new float[4];
			(*ppil)->offset[1] = size;
			size += 4;
		}
		else if ((*(ped + i)).SemanticName == "TEXCOORD") {
			(*ppil)->texcoord = new float[2];
			(*ppil)->offset[2] = size;
			size += 2;
		}
		else if ((*(ped + i)).SemanticName == "NORMAL") {
			(*ppil)->normal = new float[3];
			(*ppil)->offset[3] = size;
			size += 3;
		}
	}
	(*ppil)->numElement = num;
	(*ppil)->size = size;
}


