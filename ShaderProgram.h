#pragma once
/*
Shader:
	连接着色器
输入：
	一个图元的顶点数据 vector<Vertex> vertexs
输出：
	从渲染管线出来的顶点数据 vector<Vertex> resVertexs
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

	int _picUnitVertexNum; // 单个图元顶点个数

	Bitmap* _textureData;

	std::vector<std::vector<Vertex>> _allPicUnit; // 存放插值后的所有顶点数据（分图元存放）

	std::vector<Vertex> _resVertexs; // 存放最终要渲染的顶点数据
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

// 开始着色器（渲染管线）
void ShaderProgram::StartShaderProgram() {

	int vertexsNum = _vertexs.size(); // 总的顶点数量

	int picUnitNum = vertexsNum / _picUnitVertexNum; // 图元顶点数量

	for (int i = 0; i < picUnitNum; i++) {

		std::vector<Vertex> resVertexsInUnit; // 存放一个图元内的所有顶点数据（插值后）

		std::vector<Vertex> picUnit; // 存放一个图元内的所有顶点数据（插值前）

		for(int j = 0; j < _picUnitVertexNum; j++){

			int temp = _picUnitVertexNum * i + j;

			// 对于每一个顶点数据（传入顶点着色器）
			VertexShader vs = VertexShader(_vertexs[temp].GetPosition(), _vertexs[temp].GetColor(), _vertexs[temp].GetNormal(), _vertexs[temp].GetTexcoord());
			vs.SetModel(_model);
			vs.SetView(_view);
			vs.SetProjection(_projection);

			bool isClic = vs.CalcGlTransform(); // 空间变换

			if (isClic == false) {
				glm::vec4 glPosition = vs.GetGlPosition(); // 空间变换后的顶点位置
				glm::vec4 glColor = vs.GetGlColor(); // 颜色
				glm::vec3 glNormal = vs.GetGlNormal(); // 空间变换后的法向量
				glm::vec2 glTexcoord = vs.GetTexcoord(); // 空间变换后的纹理坐标

				Vertex vsVertex = Vertex(glPosition, glColor, glNormal, glTexcoord); // 空间变换后的顶点

				picUnit.push_back(vsVertex); // 加入到一个图元中
			}
		}


		// 对于一个图元的数据（光栅化阶段，插值操作）
		RasterizateShader rs = RasterizateShader(picUnit);
		rs.SetTextureData(this->_textureData);
		rs.Interpolation(); // 插值
		resVertexsInUnit = rs.GetResVertexs(); // 一个图元内所有顶点的数据（插值后）


		// 对于插值后图元内的每一个顶点（传入片段着色器）
		int allVertexsNumInUnit = resVertexsInUnit.size();
		for (int j = 0;j < allVertexsNumInUnit;j++) {
			FragementShader fs = FragementShader(resVertexsInUnit[j].GetPosition(), resVertexsInUnit[j].GetColor(), resVertexsInUnit[j].GetNormal(), resVertexsInUnit[j].GetTexcoord());
			fs.SetTextureData(this->_textureData);
			fs.SetDirLight(this->_dirLightColor, this->_dirLightDirection);
			fs.SetViewPos(this->_viewPos);
			fs.CalcFragColor(); // 计算片段最终颜色
			glm::vec4 fragColor = fs.GetFragColor(); // 得到片段最终颜色
			resVertexsInUnit[j].SetColor(fragColor);
		}

		_allPicUnit.push_back(resVertexsInUnit);
	}

	DeepTest();
}


// 深度测试（对_allPicUnit进行操作）
void ShaderProgram::DeepTest() {
	// 深度缓冲算法
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


// 前期渲染三角形，不需要深度测试，直接赋值给最终的数据
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