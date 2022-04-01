#pragma once
/*
FragementShader:
	片段着色器
输入：
	一个片段的的颜色值 vertexColor 
	一个片段的法向量 vertexNormal
	一个片段的位置 vertexPosition
输出：
	一个片段最终的颜色 FragColor
*/

#include<glm/glm.hpp>
#include<iostream>
#include<vector>

const float width = 720.0; // 像素行数（屏幕高度）
const float height = 720.0; // 像素列数（屏幕宽度）

class FragementShader
{
public:
	FragementShader();
	FragementShader(glm::vec4 vertexPosition, glm::vec4 vertexColor, glm::vec3 vertexNormal, glm::vec2 texcoord) :_vertexPosition(vertexPosition), _vertextColor(vertexColor), _vertexNormal(vertexNormal), _vertexTexcoord(texcoord) {}
	FragementShader(glm::vec4 vertexPosition,glm::vec4 vertexColor,glm::vec3 vertexNormal):_vertexPosition(vertexPosition), _vertextColor(vertexColor),_vertexNormal(vertexNormal){}
	FragementShader(glm::vec4 vertexPosition, glm::vec4 vertexColor) :_vertexPosition(vertexPosition), _vertextColor(vertexColor) {}
	FragementShader(glm::vec4 vertexColor) :_vertextColor(vertexColor) {}
	~FragementShader();

	glm::vec4 GetFragColor();
	void CalcFragColor();

	void SetTextureData(Bitmap* bmp);
	void SetDirLight(glm::vec3 color, glm::vec3 direction);

	void SetViewPos(glm::vec3 viewPos);

private:

	glm::vec4 TextureColorCalc();
	glm::vec3 BasicLightCalc(glm::vec3 fPosition, glm::vec3 fColor, glm::vec3 fNormal);

	glm::vec4 _vertextColor;
	glm::vec4 _vertexPosition;
	glm::vec3 _vertexNormal;
	glm::vec2 _vertexTexcoord;
	glm::vec4 _FragColor;
	Bitmap* _textureData;

	glm::vec3 _dirLightDirection;
	glm::vec3 _dirLightColor;
	glm::vec3 _viewPos;
};

FragementShader::FragementShader()
{
}

FragementShader::~FragementShader()
{
}

void FragementShader::SetTextureData(Bitmap* bmp) {
	this->_textureData = bmp;
}

glm::vec4 FragementShader::GetFragColor() {
	return this->_FragColor;
}

void FragementShader::SetDirLight(glm::vec3 color, glm::vec3 direction) {
	this->_dirLightDirection = direction;
	this->_dirLightColor = color;
}

void FragementShader::SetViewPos(glm::vec3 viewPos) {
	this->_viewPos = viewPos;
}

// 计算片段最终颜色值
void FragementShader::CalcFragColor() {
	glm::vec3 objectColor = _vertextColor + TextureColorCalc();
	float x = (_vertexPosition.x / width - 0.5) * 2.0;
	float y = (_vertexPosition.y / height - 0.5) * 2.0;
	float z = (_vertexPosition.z / 100.0);
	glm::vec3 pos = glm::vec3(x, y, z);
	this->_FragColor = glm::vec4(BasicLightCalc(pos, objectColor, _vertexNormal), 1.0);
}

glm::vec4 FragementShader::TextureColorCalc() {
	Color color;
	UINT height = this->_textureData->GetHeight();
	UINT width = this->_textureData->GetWidth();

	int x = width * this->_vertexTexcoord.x;
	int y = height * this->_vertexTexcoord.y;
	this->_textureData->GetPixel(x, y, &color);

	glm::vec4 tColor = glm::vec4(color.GetRed(), color.GetGreen(), color.GetBlue(), 1);
	return tColor;
}

glm::vec3 FragementShader::BasicLightCalc(glm::vec3 fPosition, glm::vec3 fColor, glm::vec3 fNormal) {

	// 环境光
	float ambientStrength = 0.4;
	glm::vec3 ambient = ambientStrength * _dirLightColor;

	// 漫反射
	glm::vec3 norm = glm::normalize(fNormal);
	glm::vec3 lightDir = glm::normalize(this->_dirLightDirection);
	float diff = std::fmax(glm::dot(norm, lightDir), 0.0);
	glm::vec3 diffuse = diff * _dirLightColor;

	// 镜面光
	float specularStrength = 0.5;
	glm::vec3 viewDir = glm::normalize(this->_viewPos - fPosition);
	glm::vec3 reflectDir = glm::reflect(-lightDir, norm);
	float spec = std::pow(fmax(glm::dot(viewDir, reflectDir), 0.0), 32);
	glm::vec3 specular = specularStrength * spec * _dirLightColor;

	glm::vec3 result = (ambient + diffuse + specular) * fColor;

	if (result == glm::vec3(0, 0, 0)) {
		int log = 1;
	}

	return result;
}