#pragma once
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"

class GameApp
{
public:
	~GameApp();

	void InitResource();
	void InitPipeline();
	void InitGraphics();
	void DrawSence();
	std::vector<Vertex> GetVertices();

	Device* dev;
	DeviceContest* devcon;
	SwapChain* swapchain;
	ShaderProgram shaderprogram;
	VertexBuffer* vertexBuffer;
	InputLayout* inputLayout;

private:
};

GameApp::~GameApp()
{
    delete dev;
    delete devcon;
    delete swapchain;
    delete vertexBuffer;
    delete inputLayout;
}

void GameApp::InitResource() {
    dev = new Device();
    devcon = new DeviceContest();
    swapchain = new SwapChain();
    vertexBuffer = new VertexBuffer();
    inputLayout = new InputLayout();

    InitGraphics();
    InitPipeline();
    DrawSence();
}

void GameApp::DrawSence() {
    UINT stride = sizeof(SampleVertex);
    UINT offset = 0;
    devcon->SetVertexBuffer(0, 1, vertexBuffer, &stride, &offset);

    devcon->Draw(3, 0);
}


void GameApp::InitPipeline() {
    INPUT_ELEMENT_DESC ied[] = {
        {"POSITION", sizeof(float) * 4},
        {"TEXCOORD", sizeof(float) * 2},
        {"NORMAL", sizeof(float) * 3},
    };
    dev->CreateInputLayout(ied, ARRAYSIZE(ied), &inputLayout);
    devcon->SetInputLayout(inputLayout);
}

void GameApp::InitGraphics() {
    SampleVertex vertices[] = {
        // 顶点坐标         纹理坐标     法向量
        {-0.5f, -0.5f, -0.5f,  1.0f, 0, 0, 0, 0, -1,},
        {0.5f, -0.5f, -0.5f,  1.0f, 0, 1, 0, 0, -1, },
        {0.5f,  0.5f, -0.5f,  1.0f, 1, 1, 0, 0, -1, },
        {0.5f,  0.5f, -0.5f,  1.0f, 1, 1, 0, 0, -1, },
        {-0.5f,  0.5f, -0.5f, 1.0f, 1, 0, 0, 0, -1, },
        {-0.5f, -0.5f, -0.5f, 1.0f, 0, 0, 0, 0, -1, },

        {-0.5f, -0.5f,  0.5f, 1.0f, 0, 0, 0, 0, 1, },
        {0.5f, -0.5f,  0.5f,  1.0f, 0, 1, 0, 0, 1, },
        {0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 0, 1, },
        {0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 0, 1, },
        {-0.5f,  0.5f,  0.5f, 1.0f, 1, 0, 0, 0, 1, },
        {-0.5f, -0.5f,  0.5f, 1.0f, 0, 0, 0, 0, 1, },

        {-0.5f,  0.5f,  0.5f,  1.0f, 0, 0, -1, 0, 0, },
        {-0.5f,  0.5f, -0.5f,  1.0f, 0, 1, -1, 0, 0, },
        {-0.5f, -0.5f, -0.5f,  1.0f, 1, 1, -1, 0, 0, },
        {-0.5f, -0.5f, -0.5f,  1.0f, 1, 1, -1, 0, 0, },
        {-0.5f, -0.5f,  0.5f,  1.0f, 1, 0, -1, 0, 0, },
        {-0.5f,  0.5f,  0.5f,  1.0f, 0, 0, -1, 0, 0, },

        {0.5f,  0.5f,  0.5f,  1.0f, 0, 0, 1, 0, 0, },
        {0.5f,  0.5f, -0.5f,  1.0f, 0, 1, 1, 0, 0, },
        {0.5f, -0.5f, -0.5f,  1.0f, 1, 1, 1, 0, 0, },
        {0.5f, -0.5f, -0.5f,  1.0f, 1, 1, 1, 0, 0, },
        {0.5f, -0.5f,  0.5f,  1.0f, 1, 0, 1, 0, 0, },
        {0.5f,  0.5f,  0.5f,  1.0f, 0, 0, 1, 0, 0, },

        {-0.5f, -0.5f, -0.5f, 1.0f, 0, 0, 0, -1, 0, },
        {0.5f, -0.5f, -0.5f,  1.0f, 0, 1, 0, -1, 0, },
        {0.5f, -0.5f,  0.5f,  1.0f, 1, 1, 0, -1, 0, },
        {0.5f, -0.5f,  0.5f,  1.0f, 1, 1, 0, -1, 0, },
        {-0.5f, -0.5f,  0.5f, 1.0f, 1, 0, 0, -1, 0, },
        {-0.5f, -0.5f, -0.5f, 1.0f, 0, 0, 0, -1, 0, },

        {-0.5f,  0.5f, -0.5f, 1.0f, 0, 0, 0, 1, 0, },
        {0.5f,  0.5f, -0.5f,  1.0f, 0, 1, 0, 1, 0, },
        {0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 1, 0, },
        {0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 1, 0, },
        {-0.5f,  0.5f,  0.5f, 1.0f, 1, 0, 0, 1, 0, },
        {-0.5f,  0.5f, -0.5f, 1.0f, 0, 0, 0, 1, 0, },
    };

    BUFFER_DESC bd = { 0 };
    bd.ByteWidth = sizeof(vertices);

    SUBRESOURCE_DATA srd = { (float*)vertices,0,0 };

    dev->CreateBuffer(&bd, &srd, &vertexBuffer);
}

std::vector<Vertex> GameApp::GetVertices() {
    return devcon->GetVertices();
}