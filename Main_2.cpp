//#include<glm/glm.hpp>
//#include<iostream>
//#include<vector>
//#include <initializer_list>
//
//#include "ShaderProgram.h"
//#include "VertexShader.h"
//
//void Draw(VertexBuffer& vb, int num);
//void ShaderProgramer(float* vertices, unsigned char* attrs, unsigned int* offset, int num);
//void CreateBuffer(D3D11_BUFFER_DESC* vdb, D3D11_SUBRESOURCE_DATA* InitData);
//void Draw(int verticesNum, int firstVertex);
//
///*--------------------------------VertexBuffer┐¬╩╝-------------------------------------------*/
//
//struct ATTR {
//	unsigned char XYZW = 1;
//	unsigned char COLOR = 2;
//	unsigned char TEXCOORD = 3;
//	unsigned char NORMAL = 4;
//}ATTR;
//
//class VertexBuffer
//{
//public:
//	VertexBuffer();
//	~VertexBuffer();
//
//	void ATTR_CUSTOMVERTEX_DESC(std::initializer_list<unsigned char> il);
//
//	void CreateVertexBuffer(unsigned int verticesNum, unsigned int length);
//
//	void SetBufferData(unsigned int length, float *vertices);
//
//	void OFFSET_CUSTOMVERTEX_DESC(std::initializer_list<unsigned int> il);
//
//	float* GetBufferData();
//
//	unsigned char* GetAttrs();
//
//	unsigned int* GetOffsets();
//
//private:
//	unsigned int _verticesNum;
//	float* _pVertices;
//	unsigned char* _attrs;
//	unsigned int* _offsets;
//};
//
//VertexBuffer::VertexBuffer()
//{
//}
//
//VertexBuffer::~VertexBuffer()
//{
//	delete _pVertices;
//}
//
//unsigned int* VertexBuffer::GetOffsets() {
//	return _offsets;
//}
//
//unsigned char* VertexBuffer::GetAttrs() {
//	return _attrs;
//}
//
//void VertexBuffer::ATTR_CUSTOMVERTEX_DESC(std::initializer_list<unsigned char> il) {
//	int i = 0;
//	int len = il.size();
//	_attrs = new unsigned char[len];
//	for (auto s : il)
//	{
//		*(_attrs + i) = s;
//		i++;
//	}
//}
//
//void VertexBuffer::OFFSET_CUSTOMVERTEX_DESC(std::initializer_list<unsigned int> il) {
//	int i = 0;
//	int len = il.size();
//	_offsets = new unsigned int[len];
//	for (auto s : il)
//	{
//		*(_offsets + i) = s;
//		i++;
//	}
//}
//
//float* VertexBuffer::GetBufferData() {
//	return _pVertices;
//}
//
//void VertexBuffer::CreateVertexBuffer(unsigned int verticesNum, unsigned int length) {
//	_verticesNum = verticesNum;
//	_pVertices = new float[verticesNum * length / sizeof(float)];
//}
//
//void VertexBuffer::SetBufferData(unsigned int length, float* vertices) {
//	int len = length / sizeof(float);
//	int i = 0;
//	while (i != len) {
//		*(_pVertices + i) = *(vertices + i);
//		i++;
//	}
//}
//
///*-------------------------------VertexBufferŻß╩°--------------------------------------------*/
//
///*-------------------------------Main┐¬╩╝--------------------------------------------*/
//
//typedef struct D3D11_INPUT_ELEMENT_DESC
//{
//	string SemanticName;
//	UINT SemanticIndex;
//	UINT Format;
//	UINT InputSlot;
//	UINT AlignedByteOffset;
//	UINT InstanceDataStepRate;
//}D3D11_INPUT_ELEMENT_DESC;
//
//typedef struct D3D11_BUFFER_DESC
//{
//	UINT ByteWidth;
//	UINT BindFlags;
//	UINT CPUAccessFlags;
//	UINT MiscFlags;
//	UINT StructureByteStride;
//}D3D11_BUFFER_DESC;
//
//typedef struct D3D11_SUBRESOURCE_DATA
//{
//	const void* pSysMem;
//	UINT SysMemPitch;
//	UINT SysMemSlicePitch;
//}D3D11_SUBRESOURCE_DATA;
//
//// ╔Ŕ╝ĂÂąÁŃŻß╣╣
//struct CustomVertex {
//	float x, y, z, w;
//	float u, v;
//	float nx, ny, nz;
//};
//
//int main2() {
//
//	// ├Ŕ╩÷Żß╣╣╠ňÍđÁ─╩˘đď
//	const D3D11_INPUT_ELEMENT_DESC layout[3] = {
//		{"POSITION", 0, sizeof(float) * 4, 0, 0, 0},
//		{"TEXCOORD", 0, sizeof(float) * 2, 0, 0, 0},
//		{"NORMAL",   0, sizeof(float) * 3, 0, 0, 0},
//	};
//
//	// ╔ŔÍ├ÂąÁŃ╩řżŢ
//	CustomVertex vertices[] = {
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//	};
//
//	// ╔ŔÍ├ÂąÁŃ╗║│ňă°├Ŕ╩÷
//	D3D11_BUFFER_DESC vbd;
//	ZeroMemory(&vbd, sizeof(vbd));
//	vbd.ByteWidth = sizeof(vertices);
//
//	// đ┬ŻĘÂąÁŃ╗║│ňă°
//	D3D11_SUBRESOURCE_DATA InitData;
//	ZeroMemory(&InitData, sizeof(InitData));
//	InitData.pSysMem = vertices;
//
//	// ┤┤ŻĘ╗║┤Š
//	// ID3D11Device::CreateBuffer(&vbd, &InitData);
//
//	// ┴ČŻËÎ┼╔źĂ¸
//	// ID3D11Device::ShaderProgram();
//
//	// ╗ŠÍĂ
//	// ID3D11DeviceContext::Draw(3, 0);
//}
//
//void Draw(int verticesNum, int firstVertex) {
//
//}
//
//void CreateBuffer(D3D11_BUFFER_DESC* vbd, D3D11_SUBRESOURCE_DATA* InitData) {
//
//}
//
//int main() {
//
//	VertexBuffer vb;
//
//	// 2.1 ├Ŕ╩÷Żß╣╣╠ňÍđÁ─╩˘đď
//	vb.ATTR_CUSTOMVERTEX_DESC({ ATTR.XYZW, ATTR.TEXCOORD, ATTR.NORMAL });
//	// 2.2 ╩˘đďď┌Żß╣╣ÍđÁ─ĂźĎĂÍÁ
//	vb.OFFSET_CUSTOMVERTEX_DESC({ 0, 4, 6 });
//
//	// 3.1 ┤┤ŻĘÂąÁŃ╗║┤Š
//	vb.CreateVertexBuffer(6, sizeof(CustomVertex));
//	// 3.2 │§╩╝╗»ÂąÁŃ╩řżŢ
//	CustomVertex vertices[] = {
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//		{0,0,0,1, 0,0, 0,0,1},
//	};
//	// 3.3 Ş°ÂąÁŃ╗║┤ŠŞ│ÍÁ
//	float* pVertices = new float[sizeof(vertices) / sizeof(float)];
//	memcpy(pVertices, vertices, sizeof(vertices));
//	vb.SetBufferData(sizeof(vertices), pVertices);
//
//	// 4 ┐¬╩╝╗ŠÍĂúĘ▓╬╩řú║ÂąÁŃ╗║┤ŠíóĎ╗Ş÷═°Ş˝Á─ÂąÁŃ╩ř┴┐úę
//	Draw(vb, 3);
//
//	return 0;
//}
//void Draw(VertexBuffer& vb, int num) {
//	ShaderProgramer(vb.GetBufferData(), vb.GetAttrs(), vb.GetOffsets(), num);
//}
//
///*---------------------------------MainŻß╩°------------------------------------------*/
//
//void ShaderProgramer(float* vertices, unsigned char* attrs, unsigned int* offset, int num) {
//
//	for (int i = 0;i < 2;i++) { // 2Ş÷═╝ď¬
//
//		for (int j = 0;j < num;j++) { // ├┐Ş÷═╝ď¬─┌numŞ÷ÂąÁŃ
//
//			// ÂďË┌├┐Ď╗Ş÷ÂąÁŃ╩řżŢúĘ┤ź╚ŰÂąÁŃÎ┼╔źĂ¸úę
//			VertexShader vs = VertexShader();
//
//			for (int k = 0;k < 3;k++) { // ├┐Ş÷ÂąÁŃ╚řÍÍ╩˘đď
//				int start = *(offset + k);
//				if (*(attrs + k) == 1) {
//					glm::vec4 position = glm::vec4(vertices[i * 27 + j * 9 + start], vertices[j * 9 + start + 1], vertices[j * 9 + start + 2], vertices[j * 9 + start + 3]);
//					vs.SetPosition(position);
//				}
//				else if(*(attrs + k) == 2) {
//					glm::vec4 color = glm::vec4(vertices[i * 27 + j * 9 + start], vertices[j * 9 + start + 1], vertices[j * 9 + start + 2], vertices[j * 9 + start + 3]);
//					vs.SetColor(color);
//				}
//				else if (*(attrs + k) == 3) {
//					glm::vec2 texcoord = glm::vec2(vertices[i * 27 + j * 9 + start], vertices[j * 9 + start + 1]);
//					vs.SetTexcoord(texcoord);
//				}
//				else if (*(attrs + k) == 4) {
//					glm::vec3 normal = glm::vec3(vertices[i * 27 + j * 9 + start], vertices[j * 9 + start + 1], vertices[j * 9 + start + 2]);
//					vs.SetNormal(normal);
//				}
//			}
//		}
//	}
//}