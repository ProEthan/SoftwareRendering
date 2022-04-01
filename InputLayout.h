

class InputLayout
{
public:
	~InputLayout();

	InputLayout* Get();

	float* position = NULL;
	float* color = NULL;
	float* texcoord = NULL;
	float* normal = NULL;

	UINT numElement; // 一个顶点中属性的数量
	int offset[4] = {-1,-1,-1,-1}; // 一个顶点中每个属性的偏移
	UINT size; // 一个顶点所占float数

private:
};


InputLayout::~InputLayout()
{
	delete position;
	delete color;
	delete texcoord;
	delete normal;
}

InputLayout* InputLayout::Get() {
	return this;
}