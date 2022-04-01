#pragma once

/*
	入口函数
*/
#include <GLFW/glfw3.h>
#include "MFrameBuffer.h"
#include "Transform.h"
#include "GameApp.h"

void processInput(GLFWwindow* window);
std::vector<unsigned char> ShaderToBuffer(std::vector<Vertex> vertexs);

//const int pixRows = 720; // 像素行数（屏幕高度）
//const int pixCols = 720; // 像素列数（屏幕宽度）

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(pixCols, pixRows, "RenderWindow", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GameApp gameApp;
    gameApp.InitResource();

    Texture texture = Texture(L"container2.png");
    Bitmap* bmp = texture.GetTextureData();

    // 光源颜色
    glm::vec3 dirLightColor = glm::vec3(1.0, 1.0, 1.0);
    // 光照方向
    glm::vec3 dirLightDirection = glm::vec3(1.0, 1.0, 1.0);
    // 摄影机位置
    glm::vec3 viewPos = glm::vec3(0, 0, 0);

    int m = 1;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // 创建着色器
        auto t = gameApp.GetVertices();
        ShaderProgram shaderProg = ShaderProgram(gameApp.GetVertices());
        shaderProg.SetTextureData(bmp);
        shaderProg.SetDirLightColor(dirLightColor);
        shaderProg.SetDirLightDirection(dirLightDirection);
        shaderProg.SetViewPos(viewPos);

        // 为着色器的变量赋值
        // model
        glm::mat4 model = glm::mat4(1.0);
        Transform transObj = Transform();
        glm::mat4 transScale = transObj.Scale(glm::vec3(0.5, 0.5, 0.5)); // 缩放

        glm::mat4 transTranslate = transObj.Translate(glm::vec3(0, 0, -1.0)); // 平移

        glm::vec3 startPos = glm::vec3(0.0, 0.0, 0.0);
        glm::vec3 direction = glm::vec3(1.2, 1.0, 0.5);
        glm::mat4 transRotate = transObj.Rotate(startPos, direction, m * 6); // 旋转

        m = (++m) % 60;
        model = transTranslate * transRotate * transScale;

        // view
        glm::mat4 view = glm::mat4(1.0);

        // proj
        glm::mat4 proj = glm::mat4(1.0);
        proj = transObj.Perspective(-0.5f, -10.0f);

        // 着色器赋值
        shaderProg.SetPicUnitVertexNum(3); // 图元的顶点数量（三角形图元时该值为3）
        shaderProg.SetModel(model);
        shaderProg.SetView(view);
        shaderProg.SetProjection(proj);

        // 开始着色程序
        shaderProg.StartShaderProgram();

        // 获取着色器的输出
        std::vector<Vertex> resVertexs = shaderProg.GetResVertexs();

        // 将着色器的输出 映射到 MFrameBuffer 中，用于显示
        std::vector<unsigned char> resBuffer = ShaderToBuffer(resVertexs);

        //绘制
        unsigned char* p = resBuffer.data();
        glDrawPixels(pixCols, pixRows,GL_RGBA, GL_UNSIGNED_BYTE, p);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    delete bmp;

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

std::vector<unsigned char> ShaderToBuffer(std::vector<Vertex> vertexs) {

    int resVertexsNum = vertexs.size();

    std::vector<unsigned char> resBuffer((pixRows + 2) * (pixCols + 2) * 4);

    // 描点（带颜色值）
    for (int i = 0;i < resVertexsNum;i++) {

        glm::vec4 position = vertexs[i].GetPosition();

        glm::vec4 color = vertexs[i].GetColor();

        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4] = color.r;
        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4 + 1] = color.g;
        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4 + 2] = color.b;
        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4 + 3] = color.a;

    }

    // 均值滤波（1 x 3 的核）
    for (int i = 4; i < (pixRows + 2) * (pixCols + 2) * 4 - 4; i += 4) {
        unsigned char r1 = resBuffer[i];
        unsigned char g1 = resBuffer[i + 1];
        unsigned char b1 = resBuffer[i + 2];

        unsigned char r2 = resBuffer[i + 4];
        unsigned char g2 = resBuffer[i + 5];
        unsigned char b2 = resBuffer[i + 6];

        unsigned char r3 = resBuffer[i - 4];
        unsigned char g3 = resBuffer[i - 3];
        unsigned char b3 = resBuffer[i - 2];

        resBuffer[i] = (r1 + r2 + r3) / 3;
        resBuffer[i + 1] = (g1 + g2 + g3) / 3;
        resBuffer[i + 2] = (b1 + b2 + b3) / 3;
    }

    return resBuffer;
}

