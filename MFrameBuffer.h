#pragma once
/**
	FrameBuffer:
	���һ֡����Ҫ��Ⱦ������
**/

class MFrameBuffer {
public:
	MFrameBuffer() {}
	MFrameBuffer(unsigned char * startPtr):_startPtr(startPtr){}
	~MFrameBuffer()
	{
		delete _startPtr;
	}
private:
	unsigned char* _startPtr;
};