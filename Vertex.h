#pragma once
/*
	Vertex：
	一个顶点所需要的数据：
	vec4 position	---顶点位置
	vec4 color	---顶点颜色
	vec2 texcoord	---纹理坐标
	vec3 normal	---顶点法向量
*/

#include<glm/glm.hpp>
#include<iostream>
#include<vector>

class Vertex {
public:
	Vertex(){}
	Vertex(glm::vec4 position,glm::vec4 color,glm::vec3 normal):_position(position),_color(color),_normal(normal){}
	Vertex(glm::vec4 position, glm::vec2 texcoord, glm::vec3 normal) :_position(position), _texcoord(texcoord), _normal(normal) {}
	Vertex(glm::vec4 position, glm::vec4 color, glm::vec3 normal, glm::vec2 texcoord) :_position(position), _color(color), _normal(normal), _texcoord(texcoord) {}

	void SetPosition(glm::vec4 position);
	void SetColor(glm::vec4 color);
	void SetNormal(glm::vec3 normal);
	void SetTexcoord(glm::vec2 texcoord);

	glm::vec4 GetPosition();
	glm::vec4 GetColor();
	glm::vec3 GetNormal();
	glm::vec2 GetTexcoord();
private:
	glm::vec4 _position = glm::vec4(0, 0, -99, 0);
	glm::vec4 _color = glm::vec4(0, 0, 0, 0);
	glm::vec3 _normal = glm::vec3(0, 0, 0);
	glm::vec2 _texcoord = glm::vec2(0, 0);
};

void Vertex::SetPosition(glm::vec4 position) {
	this->_position = position;
}

void Vertex::SetColor(glm::vec4 color) {
	this->_color = color;
}

void Vertex::SetNormal(glm::vec3 normal) {
	this->_normal = normal;
}

void Vertex::SetTexcoord(glm::vec2 texcoord) {
	this->_texcoord = texcoord;
}

glm::vec4 Vertex::GetPosition() {
	return this->_position;
}

glm::vec4 Vertex::GetColor() {
	return this->_color;
}

glm::vec3 Vertex::GetNormal() {
	return this->_normal;
}

glm::vec2 Vertex::GetTexcoord() {
	return this->_texcoord;
}
