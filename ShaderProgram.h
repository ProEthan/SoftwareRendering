#pragma once
/*
Shader:
	������ɫ��
���룺
	һ��ͼԪ�Ķ������� vector<Vertex> vertexs
�����
	����Ⱦ���߳����Ķ������� vector<Vertex> resVertexs
*/

#include "VertexShader.h"
#include "RasterizateShader.h"
#include "FragementShader.h"

#include<map>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(std::vector<Vertex> vertexs) :_vertexs(vertexs) {}
	~ShaderProgram();

	void StartShaderProgram();

	void DeepTest();
	void NoDeepTest();

	void SetModel(glm::mat4 model);
	void SetView(glm::mat4 view);
	void SetProjection(glm::mat4 projection);

	void SetPosition(glm::vec4 position);

	void SetPicUnitVertexNum(int type);

	void SetTextureData(Bitmap* bmp);

	std::vector<Vertex> GetResVertexs();

	void SetDirLightColor(glm::vec3 dirLightColor);
	void SetDirLightDirection(glm::vec3 dirLightDirection);
	void SetViewPos(glm::vec3 viewPos);

private:

	std::vector<Vertex> _vertexs;

	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;

	glm::vec3 _dirLightColor;
	glm::vec3 _dirLightDirection;
	glm::vec3 _viewPos;

	int _picUnitVertexNum; // ����ͼԪ�������

	Bitmap* _textureData;

	std::vector<std::vector<Vertex>> _allPicUnit; // ��Ų�ֵ������ж������ݣ���ͼԪ��ţ�

	std::vector<Vertex> _resVertexs; // �������Ҫ��Ⱦ�Ķ�������
};

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::SetModel(glm::mat4 model) {
	this->_model = model;
}

void ShaderProgram::SetView(glm::mat4 view) {
	this->_view = view;
}

void ShaderProgram::SetProjection(glm::mat4 projection) {
	this->_projection = projection;
}

void ShaderProgram::SetPicUnitVertexNum(int num) {
	this->_picUnitVertexNum = num;
}

void ShaderProgram::SetTextureData(Bitmap* bmp) {
	this->_textureData = bmp;
}

void ShaderProgram::SetDirLightColor(glm::vec3 dirLightColor) {
	this->_dirLightColor = dirLightColor;
}
void ShaderProgram::SetDirLightDirection(glm::vec3 dirLightDirection) {
	this->_dirLightDirection = dirLightDirection;
}
void ShaderProgram::SetViewPos(glm::vec3 viewPos) {
	this->_viewPos = viewPos;
}

// ��ʼ��ɫ������Ⱦ���ߣ�
void ShaderProgram::StartShaderProgram() {

	int vertexsNum = _vertexs.size(); // �ܵĶ�������

	int picUnitNum = vertexsNum / _picUnitVertexNum; // ͼԪ��������

	for (int i = 0; i < picUnitNum; i++) {

		std::vector<Vertex> resVertexsInUnit; // ���һ��ͼԪ�ڵ����ж������ݣ���ֵ��

		std::vector<Vertex> picUnit; // ���һ��ͼԪ�ڵ����ж������ݣ���ֵǰ��

		for(int j = 0; j < _picUnitVertexNum; j++){

			int temp = _picUnitVertexNum * i + j;

			// ����ÿһ���������ݣ����붥����ɫ����
			VertexShader vs = VertexShader(_vertexs[temp].GetPosition(), _vertexs[temp].GetColor(), _vertexs[temp].GetNormal(), _vertexs[temp].GetTexcoord());
			vs.SetModel(_model);
			vs.SetView(_view);
			vs.SetProjection(_projection);

			bool isClic = vs.CalcGlTransform(); // �ռ�任

			if (isClic == false) {
				glm::vec4 glPosition = vs.GetGlPosition(); // �ռ�任��Ķ���λ��
				glm::vec4 glColor = vs.GetGlColor(); // ��ɫ
				glm::vec3 glNormal = vs.GetGlNormal(); // �ռ�任��ķ�����
				glm::vec2 glTexcoord = vs.GetTexcoord(); // �ռ�任�����������

				Vertex vsVertex = Vertex(glPosition, glColor, glNormal, glTexcoord); // �ռ�任��Ķ���

				picUnit.push_back(vsVertex); // ���뵽һ��ͼԪ��
			}
		}


		// ����һ��ͼԪ�����ݣ���դ���׶Σ���ֵ������
		RasterizateShader rs = RasterizateShader(picUnit);
		rs.SetTextureData(this->_textureData);
		rs.Interpolation(); // ��ֵ
		resVertexsInUnit = rs.GetResVertexs(); // һ��ͼԪ�����ж�������ݣ���ֵ��


		// ���ڲ�ֵ��ͼԪ�ڵ�ÿһ�����㣨����Ƭ����ɫ����
		int allVertexsNumInUnit = resVertexsInUnit.size();
		for (int j = 0;j < allVertexsNumInUnit;j++) {
			FragementShader fs = FragementShader(resVertexsInUnit[j].GetPosition(), resVertexsInUnit[j].GetColor(), resVertexsInUnit[j].GetNormal(), resVertexsInUnit[j].GetTexcoord());
			fs.SetTextureData(this->_textureData);
			fs.SetDirLight(this->_dirLightColor, this->_dirLightDirection);
			fs.SetViewPos(this->_viewPos);
			fs.CalcFragColor(); // ����Ƭ��������ɫ
			glm::vec4 fragColor = fs.GetFragColor(); // �õ�Ƭ��������ɫ
			resVertexsInUnit[j].SetColor(fragColor);
		}

		_allPicUnit.push_back(resVertexsInUnit);
	}

	DeepTest();
}


// ��Ȳ��ԣ���_allPicUnit���в�����
void ShaderProgram::DeepTest() {
	// ��Ȼ����㷨
	std::vector<Vertex> deepBuffer(pixRows * pixCols, Vertex());
	int picUnitNum = _allPicUnit.size();
	for (int i = 0;i < picUnitNum;i++) {
		std::vector<Vertex> vertexsInMesh = _allPicUnit[i];
		int vertexsNumInMesh = vertexsInMesh.size();
		for (int j = 0;j < vertexsNumInMesh;j++) {
			int x = vertexsInMesh[j].GetPosition().x;
			int y = vertexsInMesh[j].GetPosition().y;
			int z = vertexsInMesh[j].GetPosition().z;
			int deepBufferPos = y * pixCols + x;
			if (z > deepBuffer[deepBufferPos].GetPosition().z) {
				deepBuffer[deepBufferPos] = vertexsInMesh[j];
			}
		}
	}
	int vNum = deepBuffer.size();
	for (int i = 0;i < vNum;i++) {
		if (deepBuffer[i].GetPosition().z != -99) {
			_resVertexs.push_back(deepBuffer[i]);
		}
	}
}


// ǰ����Ⱦ�����Σ�����Ҫ��Ȳ��ԣ�ֱ�Ӹ�ֵ�����յ�����
void ShaderProgram::NoDeepTest() {
	int m = _allPicUnit.size();
	for (int i = 0;i < m;i++) {
		int n = _allPicUnit[i].size();
		for (int j = 0;j < n;j++) {
			_resVertexs.push_back(_allPicUnit[i][j]);
		}
	}
}

std::vector<Vertex> ShaderProgram::GetResVertexs() {
	return _resVertexs;
}