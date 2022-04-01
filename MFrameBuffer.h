#pragma once
/**
	FrameBuffer:
	存放一帧中需要渲染的数据
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