

class InputLayout
{
public:
	~InputLayout();

	InputLayout* Get();

	float* position = NULL;
	float* color = NULL;
	float* texcoord = NULL;
	float* normal = NULL;

	UINT numElement; // һ�����������Ե�����
	int offset[4] = {-1,-1,-1,-1}; // һ��������ÿ�����Ե�ƫ��
	UINT size; // һ��������ռfloat��

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