#pragma once
class VertexBuffer
{
public:
	~VertexBuffer();
	float *bufferData;
	int verticesNum;

private:
};


VertexBuffer::~VertexBuffer()
{
}