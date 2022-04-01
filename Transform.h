#pragma once
/*
Transform:
	�任�ࣺ���š�ƽ�ơ���ת���ü�

	glm�еľ�������ʱ�����������ǰ�������ں�������������ȡ�����Ϊ��������
*/

#include<glm/glm.hpp>
#include<iostream>
#include<vector>
#include<math.h>
const float PI = 3.1415926;

class Transform
{
public:
	Transform();
	Transform(glm::mat4 transform) :_transform(transform) {}
	~Transform();

	glm::mat4 Scale(glm::vec3 scalePara); // ���ź��������ղ���Ϊ ���ű���
	
	glm::mat4 Translate(glm::vec3 translatePara); // ƽ�ƺ��������յĲ���Ϊ ƽ����ֵ

	glm::mat4 Rotate(glm::vec3 startPos, glm::vec3 direction, float angle); // ��ת���������յĲ���Ϊ ��ת�Ƕȡ���ת����

	glm::mat4 Perspective(float nearZ, float farZ);

	glm::mat4 Rotate_Z(float angle);

	glm::mat4 Rotate_Y(float angle);

	glm::mat4 Rotate_X(float angle);

private:
	glm::mat4 _transform;
};

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::Scale(glm::vec3 scalePara) {
	glm::mat4 trans = glm::mat4(1.0);
	for (int i = 0;i < 3;i++) {
		trans[i][i] *= scalePara[i];
	}
	return trans;
}

glm::mat4 Transform::Translate(glm::vec3 translatePara) {
	glm::mat4 trans = glm::mat4(1.0);
	for (int i = 0;i < 3;i++) {
		trans[3][i] += translatePara[i];
	}
	return trans;
}


glm::mat4 Transform::Rotate(glm::vec3 startPos, glm::vec3 direction, float angle) {

	// �ƹ�ԭ�����������ת
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rotateM = glm::mat4(1.0);
	direction = glm::normalize(direction);
	float a = direction.x;
	float b = direction.y;
	float c = direction.z;
	rotateM[0][0] = a * a + (1 - a * a) * std::cos(radians);
	rotateM[0][1] = a * b * (1 - std::cos(radians)) - c * std::sin(radians);
	rotateM[0][2] = a * c * (1 - std::cos(radians)) + b * std::sin(radians);
	rotateM[1][0] = a * b * (1 - std::cos(radians)) + c * std::sin(radians);
	rotateM[1][1] = b * b + (1 - b * b) * std::cos(radians);
	rotateM[1][2] = b * c * (1 - std::cos(radians)) - a * std::sin(radians);
	rotateM[2][0] = a * c * (1 - std::cos(radians)) - b * std::sin(radians);
	rotateM[2][1] = b * c * (1 - std::cos(radians)) + a * std::sin(radians);
	rotateM[2][2] = c * c + (1 - c * c) * std::cos(radians);

	// ƽ��
	glm::vec3 trans = glm::vec3(-startPos.x, -startPos.y, -startPos.z);
	glm::mat4 forwardTrans = Translate(trans);
	glm::mat4 backTrans = Translate(startPos);

	// ����
	glm::mat4 rq = backTrans * rotateM * forwardTrans;

	// ������������ת����
	return rq;
}

glm::mat4 Transform::Rotate_Z(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[0][0] = std::cos(radians);
	rq[1][0] = 0 - std::sin(radians);
	rq[0][1] = std::sin(radians);
	rq[1][1] = std::cos(radians);
	return rq;
}

glm::mat4 Transform::Rotate_Y(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[0][0] = std::cos(radians);
	rq[0][2] = 0 - std::sin(radians);
	rq[2][0] = std::sin(radians);
	rq[2][2] = std::cos(radians);
	return rq;
}

glm::mat4 Transform::Rotate_X(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[1][1] = std::cos(radians);
	rq[2][1] = 0 - std::sin(radians);
	rq[1][2] = std::sin(radians);
	rq[2][2] = std::cos(radians);
	return rq;
}

/*
���������
	��ƽ��z�����ꡢԶƽ��z������
*/
glm::mat4 Transform::Perspective(float n, float f) {
	glm::mat4 scal = glm::mat4(1.0);
	scal[2][2] = 2.0 / (n - f);
	glm::mat4 trans = glm::mat4(1.0);
	trans[3][2] = (n + f) / (-2.0);
	glm::mat4 persp = glm::mat4(0.0);
	persp[0][0] = n;
	persp[1][1] = n;
	persp[2][2] = n + f;
	persp[3][2] = -n * f;
	persp[2][3] = 1;
	glm::mat4 rq = scal * trans * persp;
	return rq;
}
