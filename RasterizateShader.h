#pragma once
/*
	RasterizateShader:
		光栅化阶段
	
	输入：
		一个图元的数据:图元的顶点的Vertex数据 _vertexs

	输出：
		一个图元内所有顶点的Vertex数据 _resVertexs
*/

#include "Vertex.h"
#include "Texture.h"
#include<algorithm>
#include<map>


class RasterizateShader {

public:

	RasterizateShader(){}
	RasterizateShader(Vertex vertex):_vertex1(vertex){}
	RasterizateShader(Vertex vertex1, Vertex vertex2) :_vertex1(vertex1),_vertex2(vertex2) {}
	RasterizateShader(Vertex vertex1, Vertex vertex2, Vertex vertex3) :_vertex1(vertex1),_vertex2(vertex2),_vertex3(vertex3) {}
	RasterizateShader(std::vector<Vertex> vertexs):_vertexs(vertexs){}

	void Interpolation();

	std::vector<Vertex> GetResVertexs();

	void SetTextureData(Bitmap* bmp);

private:

	// 二维空间的相关计算
	void CalcSlopInPlane(glm::vec4 point1, glm::vec4 point2, float& k, float& b);
	int CalcY(int x, float k, float b);
	float CalcDistance(glm::vec2 point1, glm::vec2 point2);
	float CalcInterProportion(glm::vec4 interPoint, glm::vec4 point1, glm::vec4 point2);
	int CalcZ(int x, int y, glm::vec4 leftPoint, glm::vec4 rightPoint);

	// 三维空间的相关计算
	int CalculateX(glm::vec4 point1, glm::vec4 point2, int y);
	int CalculateY(glm::vec4 point1, glm::vec4 point2, int x);
	int CalculateZ(glm::vec4 point1, glm::vec4 point2, int x, int y);
	float CalculateDistance(glm::vec4 point1, glm::vec4 point2);
	float CalculateProportion(glm::vec4 interPoint, glm::vec4 point1, glm::vec4 point2);

	glm::vec2 TexcoordCalc(glm::vec2 t1, glm::vec2 t2, float prop);

	std::vector<Vertex> LinerInterpolation(Vertex point1, Vertex point2); // 三维空间线性插值
	
	std::vector<Vertex> LinerInterpolation2D(Vertex point1, Vertex point2); // 二维空间线性插值

	std::vector<Vertex> TriangleInterpolation(std::vector<Vertex> vertexs); // 三维空间三角形填充插值

	std::vector<Vertex> SortTriangleVertex(std::vector<Vertex> vertexs);
	Vertex GetInterVertexInLine(Vertex vertex1, Vertex vertex2, int x);
	glm::vec4 LinerColorInterpolationCalc(glm::vec4 leftColor, glm::vec4 rightColor, float proportion);
	glm::vec3 NormalCalc(Vertex v1, Vertex v2, float prop);


	Vertex _vertex1;
	Vertex _vertex2;
	Vertex _vertex3;
	std::vector<Vertex> _vertexs;
	std::vector<Vertex> _resVertexs;

	Bitmap* _textureData;
};

void RasterizateShader::SetTextureData(Bitmap* bmp) {
	this->_textureData = bmp;
}


// 光栅化阶段插值函数
void RasterizateShader::Interpolation() {

	int vertexNumInPicUnit = _vertexs.size();

	std::vector<Vertex> resVertexs;

	// 线性插值
	if (vertexNumInPicUnit == 2) {
		resVertexs = LinerInterpolation(_vertexs[0], _vertexs[1]);
	}
	// 三角形填充插值
	else if(vertexNumInPicUnit == 3) {
		resVertexs = TriangleInterpolation(_vertexs);
	}

	this->_resVertexs = resVertexs;
}



/*
三维空间三角形填充插值：
	输入：
		三个顶点数据
	输出：
		三角形内的所有插值顶点数据
*/
std::vector<Vertex> RasterizateShader::TriangleInterpolation(std::vector<Vertex> vertexs) {

	std::vector<Vertex> resVertexs;

	std::vector<Vertex> orderVertexs = SortTriangleVertex(vertexs);

	glm::vec<4,int> point1 = orderVertexs[0].GetPosition();
	orderVertexs[0].SetPosition(point1);
	glm::vec<4,int> point2 = orderVertexs[1].GetPosition();
	orderVertexs[1].SetPosition(point2);
	glm::vec<4,int> point3 = orderVertexs[2].GetPosition();
	orderVertexs[2].SetPosition(point3);

	for (int x = (int)point1.x; x < (int)point2.x; x++) {

		Vertex upInterVertex = GetInterVertexInLine(orderVertexs[0], orderVertexs[1], x);

		Vertex downInterVertex = GetInterVertexInLine(orderVertexs[0], orderVertexs[2], x);

		std::vector<Vertex> vertexsInLine = LinerInterpolation(upInterVertex, downInterVertex);

		resVertexs.insert(resVertexs.end(), vertexsInLine.begin(), vertexsInLine.end());
	}

	for (int x = (int)point2.x; x < (int)point3.x; x++) {

		Vertex upInterVertex = GetInterVertexInLine(orderVertexs[1], orderVertexs[2], x);

		Vertex downInterVertex = GetInterVertexInLine(orderVertexs[0], orderVertexs[2], x);

		std::vector<Vertex> vertexsInLine = LinerInterpolation(upInterVertex, downInterVertex);

		resVertexs.insert(resVertexs.end(), vertexsInLine.begin(), vertexsInLine.end());
	}

	return resVertexs;
}



/*
三维空间的线性插值：
	输入：
		两个顶点数据
	输出：
		两个顶点间的所有插值顶点数据
*/
std::vector<Vertex> RasterizateShader::LinerInterpolation(Vertex v1, Vertex v2) {
	std::vector<Vertex> vertexs;
	glm::vec4 point1 = v1.GetPosition();
	glm::vec4 point2 = v2.GetPosition();
	if (std::fabs(point1.x - point2.x) > std::fabs(point1.y - point2.y)) {
		if (point1.x < point2.x) {
			for (int x = point1.x;x <= point2.x;x++) {
				int y = CalculateY(point1, point2, x);
				int z = CalculateZ(point1, point2, x, y);
				glm::vec4 interPoint = glm::vec4(x, y, z, z);
				float proportion = CalculateProportion(interPoint, point1, point2);
				//glm::vec4 interColor = LinerColorInterpolationCalc(v1.GetColor(), v2.GetColor(), proportion);
				glm::vec4 interColor = glm::vec4(0, 0, 0, 0);
				glm::vec2 interTexcoord = TexcoordCalc(v1.GetTexcoord(), v2.GetTexcoord(), proportion);
				glm::vec3 interNormal = v2.GetNormal();
				Vertex interVertex = Vertex(interPoint, interColor, interNormal, interTexcoord);
				vertexs.push_back(interVertex);
			}
		}
		else {
			for (int x = point1.x; x >= point2.x; x--) {
				int y = CalculateY(point1, point2, x);
				int z = CalculateZ(point1, point2, x, y);
				glm::vec4 interPoint = glm::vec4(x, y, z, z);
				float proportion = CalculateProportion(interPoint, point1, point2);
				//glm::vec4 interColor = LinerColorInterpolationCalc(v1.GetColor(), v2.GetColor(), proportion);
				glm::vec4 interColor = glm::vec4(0, 0, 0, 0);
				glm::vec2 interTexcoord = TexcoordCalc(v1.GetTexcoord(), v2.GetTexcoord(), proportion);
				glm::vec3 interNormal = v2.GetNormal();
				Vertex interVertex = Vertex(interPoint, interColor, interNormal, interTexcoord);
				vertexs.push_back(interVertex);
			}
		}
	}
	else {
		if (point1.y < point2.y) {
			for (int y = point1.y; y <= point2.y; y++) {
				int x = CalculateX(point1, point2, y);
				int z = CalculateZ(point1, point2, x, y);
				glm::vec4 interPoint = glm::vec4(x, y, z, z);
				float proportion = CalculateProportion(interPoint, point1, point2);
				//glm::vec4 interColor = LinerColorInterpolationCalc(v1.GetColor(), v2.GetColor(), proportion);
				glm::vec4 interColor = glm::vec4(0, 0, 0, 0);
				glm::vec2 interTexcoord = TexcoordCalc(v1.GetTexcoord(), v2.GetTexcoord(), proportion);
				glm::vec3 interNormal = v2.GetNormal();
				Vertex interVertex = Vertex(interPoint, interColor, interNormal, interTexcoord);
				vertexs.push_back(interVertex);
			}
		}
		else {
			for (int y = point1.y; y >= point2.y; y--) {
				int x = CalculateX(point1, point2, y);
				int z = CalculateZ(point1, point2, x, y);
				glm::vec4 interPoint = glm::vec4(x, y, z, z);
				float proportion = CalculateProportion(interPoint, point1, point2);
				//glm::vec4 interColor = LinerColorInterpolationCalc(v1.GetColor(), v2.GetColor(), proportion);
				glm::vec4 interColor = glm::vec4(0, 0, 0, 0);
				glm::vec2 interTexcoord = TexcoordCalc(v1.GetTexcoord(), v2.GetTexcoord(), proportion);
				glm::vec3 interNormal = v2.GetNormal();
				Vertex interVertex = Vertex(interPoint, interColor, interNormal, interTexcoord);
				vertexs.push_back(interVertex);
			}
		}
	}
	return vertexs;
}

glm::vec2 RasterizateShader::TexcoordCalc(glm::vec2 t1, glm::vec2 t2, float prop) {
	Color color;
	float x = t1.x + (t2.x - t1.x) * (1 - prop);
	float y = t1.y + (t2.y - t1.y) * (1 - prop);
	glm::vec2 texcoord = glm::vec2(x, y);
	return texcoord;
}

// 由 y 算 x
int RasterizateShader::CalculateX(glm::vec4 point1, glm::vec4 point2, int y) {
	if (point2.y == point1.y) {
		return point1.x;
	}
	return (y - point1.y) * (point2.x - point1.x) / (point2.y - point1.y) + point1.x;
}

// 由 x 算 y
int RasterizateShader::CalculateY(glm::vec4 point1, glm::vec4 point2, int x) {
	if (point2.x == point1.x) {
		return point1.y;
	}
	return (x - point1.x) * (point2.y - point1.y) / (point2.x - point1.x) + point1.y;
}

int RasterizateShader::CalculateZ(glm::vec4 point1, glm::vec4 point2, int x, int y) {
	if (point2.y == point1.y && point2.x == point2.x) {
		return point1.z;
	}
	else if (point1.y == point2.y) {
		return (x - point1.x) * (point2.z - point1.z) / (point2.x - point2.x) + point1.z;
	}
	else {
		return (y - point1.y) * (point2.z - point1.z) / (point2.y - point1.y) + point1.z;
	}
}

float RasterizateShader::CalculateDistance(glm::vec4 point1, glm::vec4 point2) {
	return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2) + std::pow(point1.z - point2.z, 2));
}

float RasterizateShader::CalculateProportion(glm::vec4 interPoint, glm::vec4 point1, glm::vec4 point2){
	float d1 = CalculateDistance(interPoint, point1);
	float d2 = CalculateDistance(interPoint, point2);
	if (d1 == 0 && d2 == 0) {
		return 1;
	}
	return d2 / (d1 + d2);
}

/*
二维空间的线性插值
*/
std::vector<Vertex> RasterizateShader::LinerInterpolation2D(Vertex v1, Vertex v2) {
	std::vector<Vertex> vertexs;
	glm::vec4 point1 = v1.GetPosition();
	glm::vec4 point2 = v2.GetPosition();
	float k, b;
	CalcSlopInPlane(point1, point2, k, b);
	if (point1.x > point2.x) {
		glm::vec4 temp = point1;
		point1 = point2;
		point2 = temp;
	}
	for (int x = point1.x;x <= point2.x;x++) {
		int y = CalcY(x, k, b);
		int z = CalcZ(x, y, point1, point2);
		glm::vec4 interPoint = glm::vec4(x, y, z, z);
		float proportion = CalcInterProportion(interPoint, point1, point2);
		glm::vec4 interColor = LinerColorInterpolationCalc(v1.GetColor(), v2.GetColor(), proportion);
		glm::vec3 interNormal = v2.GetNormal();
		Vertex interVertex = Vertex(interPoint, interColor, interNormal);
		vertexs.push_back(interVertex);
	}
	return vertexs;
}

// 计算平面内直线斜率（线性）
void RasterizateShader::CalcSlopInPlane(glm::vec4 point1, glm::vec4 point2, float& k, float& b) {
	glm::vec2 p1 = glm::vec2(point1.x, point1.y);
	glm::vec2 p2 = glm::vec2(point2.x, point2.y);
	k = (p2.y - p1.y) / (p2.x - p1.x);
	b = p1.y - k * p1.x;
}

// 计算插值点的Y值（线性）
int RasterizateShader::CalcY(int x, float k, float b) {
	return (int)k * x + b;
}

// 计算插值点的Z值（线性）
int RasterizateShader::CalcZ(int x, int y, glm::vec4 leftPoint, glm::vec4 rightPoint) {
	glm::vec3 p1 = glm::vec3(leftPoint.x, leftPoint.y, leftPoint.z);
	glm::vec3 p2 = glm::vec3(rightPoint.x, rightPoint.y, rightPoint.z);
	glm::vec3 directionVector = p2 - p1;
	return p1.z + directionVector.z * (x - p1.x) / directionVector.x;
}

// 计算平面内两点距离（线性）
float RasterizateShader::CalcDistance(glm::vec2 point1, glm::vec2 point2) {
	return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}

// 计算平面内插值比例（线性）
float RasterizateShader::CalcInterProportion(glm::vec4 interPoint, glm::vec4 point1, glm::vec4 point2) {
	glm::vec2 leftPoint = glm::vec2(point1.x, point1.y);
	glm::vec2 rightPoint = glm::vec2(point2.x, point2.y);
	glm::vec2 targetPoint = glm::vec2(interPoint.x, interPoint.y);
	float d1 = CalcDistance(targetPoint, leftPoint);
	float d2 = CalcDistance(targetPoint, rightPoint);
	return d1 / (d2 + d2);
}

// 按三角形三个顶点的x坐标排序
std::vector<Vertex> RasterizateShader::SortTriangleVertex(std::vector<Vertex> vertexs) {
	std::vector<Vertex> res;

	std::map<std::vector<float>, Vertex> mmap;
	std::vector<float> v1 = { vertexs[0].GetPosition().x, 1 };
	std::vector<float> v2 = { vertexs[1].GetPosition().x, 2 };
	std::vector<float> v3 = { vertexs[2].GetPosition().x, 3 };
	mmap.insert(std::pair<std::vector<float>, Vertex>(v1, vertexs[0]));
	mmap.insert(std::pair<std::vector<float>, Vertex>(v2, vertexs[1]));
	mmap.insert(std::pair<std::vector<float>, Vertex>(v3, vertexs[2]));

	std::map<std::vector<float>, Vertex>::iterator it;
	for (it = mmap.begin();it != mmap.end();it++) {
		glm::vec4 pos = glm::vec4(it->second.GetPosition().x, it->second.GetPosition().y, it->second.GetPosition().z * 100, it->second.GetPosition().w);
		it->second.SetPosition(pos);
		res.push_back(it->second);
	}

	return res;
}

/*
计算得到三角形边上的vertex
	输入：
		一条边的两个端点的vertex、所求vertex的x
	输出：
		边上某点的vertex
*/
Vertex RasterizateShader::GetInterVertexInLine(Vertex vertex1, Vertex vertex2, int x) {
	glm::vec4 point1 = vertex1.GetPosition();
	glm::vec4 point2 = vertex2.GetPosition();
	int y = CalculateY(point1, point2, x);
	int z = CalculateZ(point1, point2, x, y);
	glm::vec4 interPoint = glm::vec4(x, y, z, z);
	float proportion = CalculateProportion(interPoint, point1, point2);
	//glm::vec4 interColor = LinerColorInterpolationCalc(vertex1.GetColor(), vertex2.GetColor(), proportion);
	glm::vec4 interColor = glm::vec4(0, 0, 0, 0);
	glm::vec3 interNormal = vertex2.GetNormal();
	float t1 = vertex1.GetTexcoord().x + (1 - proportion) * (vertex2.GetTexcoord().x - vertex1.GetTexcoord().x);
	float t2 = vertex1.GetTexcoord().y + (1 - proportion) * (vertex2.GetTexcoord().y - vertex1.GetTexcoord().y);
	glm::vec2 interTexcoord = glm::vec2(t1, t2);
	Vertex interVertex = Vertex(interPoint, interColor, interNormal, interTexcoord);
	return interVertex;
}

// 法向量插值
glm::vec3 RasterizateShader::NormalCalc(Vertex v1, Vertex v2, float prop) {
	glm::vec3 n1 = v1.GetNormal();
	glm::vec3 n2 = v2.GetNormal();
	glm::vec3 normal = prop * n1 + (1 - prop) * n2;
	return normal;
}

// 颜色插值
glm::vec4 RasterizateShader::LinerColorInterpolationCalc(glm::vec4 leftColor, glm::vec4 rightColor, float proportion) {
	glm::vec4 interColor;
	interColor = proportion * leftColor + (1 - proportion) * rightColor;
	return interColor;
}

// 插值后的图元数据（许多Vertex（片段））
std::vector<Vertex> RasterizateShader::GetResVertexs() {
	return this->_resVertexs;
}
