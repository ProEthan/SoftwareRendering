#pragma once

/*
	VertexShader:
		顶点着色器

	输入：
		单个顶点的位置 position
		变换矩阵 model
		视角矩阵 view
		透视矩阵 projection

	输出：
		变换后的顶点位置 glPosition
*/

const int pixRows = 720; // 像素行数（屏幕高度）
const int pixCols = 720; // 像素列数（屏幕宽度）

#include<glm/glm.hpp>
#include<iostream>
#include<vector>

class VertexShader {
public:
	VertexShader() {}
	VertexShader(glm::vec4 position) :_position(position) {}
	VertexShader(glm::vec4 position, glm::vec4 color) :_position(position), _color(color) {}
	VertexShader(glm::vec4 position, glm::vec4 color, glm::vec3 normal) :_position(position), _color(color), _normal(normal) {}
	VertexShader(glm::vec4 position, glm::vec4 color, glm::vec3 normal, glm::vec2 texcoord) :_position(position), _color(color), _normal(normal), _texcoord(texcoord) {}

	void SetModel(glm::mat4 model);
	void SetView(glm::mat4 view);
	void SetProjection(glm::mat4 projection);

	void SetPosition(glm::vec4 position);
	void SetColor(glm::vec4 color);
	void SetTexcoord(glm::vec2 texcoord);
	void SetNormal(glm::vec3 normal);

	glm::vec2 GetTexcoord();

	glm::vec4 GetGlPosition();
	glm::vec3 GetGlNormal();
	glm::vec4 GetGlColor();

	glm::vec4 GetFragPosition();

	bool CalcGlTransform();

private:

	glm::vec4 _position = glm::vec4(0, 0, -99, 0);
	glm::vec4 _color = glm::vec4(0, 0, 0, 0);
	glm::vec3 _normal = glm::vec3(0, 0, 0);
	glm::vec2 _texcoord = glm::vec2(0, 0);

	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;

	glm::vec4 _glPosition;
	glm::vec4 _glColor;
	glm::vec3 _glNormal;
	glm::vec2 _glTexcoord;

	glm::vec4 _fragPosition;
};

void VertexShader::SetModel(glm::mat4 model) {
	this->_model = model;
}

void VertexShader::SetView(glm::mat4 view) {
	this->_view = view;
}

void VertexShader::SetProjection(glm::mat4 projection) {
	this->_projection = projection;
}

void VertexShader::SetPosition(glm::vec4 position) {
	this->_position = position;
}

void VertexShader::SetTexcoord(glm::vec2 texcoord) {
	this->_texcoord = texcoord;
}

void VertexShader::SetColor(glm::vec4 color) {
	this->_color = color;
}

void VertexShader::SetNormal(glm::vec3 normal) {
	this->_normal = normal;
}

glm::vec2 VertexShader::GetTexcoord() {
	return this->_glTexcoord;
}

glm::vec4 VertexShader::GetGlPosition() {
	return this->_glPosition;
}

glm::vec3 VertexShader::GetGlNormal() {
	return this->_glNormal;
}

glm::vec4 VertexShader::GetGlColor() {
	return this->_glColor;
}

glm::vec4 VertexShader::GetFragPosition() {
	return this->_fragPosition;
}

// 计算Vertex变换后的位置和状态（返回值：是否被裁剪）
bool VertexShader::CalcGlTransform() {

	// 空间变换
	this->_glPosition = this->_projection * this->_view * this->_model * this->_position;

	// 法向量变换
	this->_glNormal = glm::mat3(glm::transpose(glm::inverse(this->_model))) * this->_normal;

	// 裁剪
	if (this->_glPosition.x > -this->_glPosition.w || this->_glPosition.x < this->_glPosition.w || this->_glPosition.y > -this->_glPosition.w || this->_glPosition.y < this->_glPosition.w || this->_glPosition.z < this->_glPosition.w || this->_glPosition.z > -this->_glPosition.w) {
		return true;
	}

	// 透视除法
	if (this->_glPosition.w != 0) {
		this->_glPosition /= this->_glPosition.w;
	}
	else {
		std::cout << "log" << std::endl;
	}

	this->_fragPosition = this->_glPosition;

	// 转换到屏幕空间
	glm::mat4 screen = glm::mat4(1.0);
	screen[0][0] = pixCols / 2;
	screen[1][1] = pixRows / 2;
	this->_glPosition = screen * this->_glPosition;
	glm::vec4 sc = { pixCols / 2, pixRows / 2, 0, 0 };
	this->_glPosition += sc;

	// 颜色输出
	this->_glColor = this->_color;

	// 纹理坐标输出
	this->_glTexcoord = this->_texcoord;

	return false;
}