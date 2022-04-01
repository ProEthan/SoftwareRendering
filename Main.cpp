//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//
//#include "ShaderProgram.h"
//#include "MFrameBuffer.h"
//#include "Transform.h"
//#include "MVertexBuffer.h"
//
//#include<iostream>
//
//void processInput(GLFWwindow* window);
//std::vector<unsigned char> ShaderToBuffer(std::vector<Vertex> vertexs);
//
////const int pixRows = 720; // ������������Ļ�߶ȣ�
////const int pixCols = 720; // ������������Ļ��ȣ�
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(pixCols, pixRows, "RenderWindow", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    float line[] = {
//        0, 0, 0, 1, 255, 0, 0, 1, 0, 0, 1,
//        0.5, 0.5, 0, 1, 0, 255, 0, 1, 0, 0, 1,
//    };
//
//    MVertexBuffer MVB = MVertexBuffer();
//
//    //float triangle[] = {
//    //       -0.5f, -0.5f, -0.5f,  1.0f, 255, 0, 0, 1, 0, 0, 1,
//    //        0.5f, -0.5f, -0.5f,  1.0f, 255, 0, 0, 1, 0, 0, 1,
//    //        0.5f,  0.5f, -0.5f,  1.0f, 255, 0, 0, 1, 0, 0, 1,
//    //        0.5f,  0.5f, -0.5f,  1.0f, 255, 0, 0, 1, 0, 0, 1,
//    //        -0.5f,  0.5f, -0.5f, 1.0f, 255, 0, 0, 1, 0, 0, 1,
//    //        -0.5f, -0.5f, -0.5f, 1.0f, 255, 0, 0, 1, 0, 0, 1,
//    //        -0.5f, -0.5f,  0.5f, 1.0f, 0, 255, 0, 1, 0, 0, 1,
//    //        0.5f, -0.5f,  0.5f,  1.0f, 0, 255, 0, 1, 0, 0, 1,
//    //        0.5f,  0.5f,  0.5f,  1.0f, 0, 255, 0, 1, 0, 0, 1,
//    //        0.5f,  0.5f,  0.5f,  1.0f, 0, 255, 0, 1, 0, 0, 1,
//    //        -0.5f,  0.5f,  0.5f, 1.0f, 0, 255, 0, 1, 0, 0, 1,
//    //        -0.5f, -0.5f,  0.5f, 1.0f, 0, 255, 0, 1, 0, 0, 1,
//    //        -0.5f,  0.5f,  0.5f,  1.0f, 0, 0, 255, 1, 0, 0, 1,
//    //        -0.5f,  0.5f, -0.5f,  1.0f, 0, 0, 255, 1, 0, 0, 1,
//    //        -0.5f, -0.5f, -0.5f,  1.0f, 0, 0, 255, 1, 0, 0, 1,
//    //        -0.5f, -0.5f, -0.5f,  1.0f, 0, 0, 255, 1, 0, 0, 1,
//    //        -0.5f, -0.5f,  0.5f,  1.0f, 0, 0, 255, 1, 0, 0, 1,
//    //        -0.5f,  0.5f,  0.5f,  1.0f, 0, 0, 255, 1, 0, 0, 1,
//    //        0.5f,  0.5f,  0.5f,  1.0f, 255, 255, 0, 1, 0, 0, 1,
//    //        0.5f,  0.5f, -0.5f,  1.0f, 255, 255, 0, 1, 0, 0, 1,
//    //        0.5f, -0.5f, -0.5f,  1.0f, 255, 255, 0, 1, 0, 0, 1,
//    //        0.5f, -0.5f, -0.5f,  1.0f, 255, 255, 0, 1, 0, 0, 1,
//    //        0.5f, -0.5f,  0.5f,  1.0f, 255, 255, 0, 1, 0, 0, 1,
//    //        0.5f,  0.5f,  0.5f,  1.0f, 255, 255, 0, 1, 0, 0, 1,
//    //        -0.5f, -0.5f, -0.5f, 1.0f, 128, 0, 128, 1, 0, 0, 1,
//    //        0.5f, -0.5f, -0.5f,  1.0f, 128, 0, 128, 1, 0, 0, 1,
//    //        0.5f, -0.5f,  0.5f,  1.0f, 128, 0, 128, 1, 0, 0, 1,
//    //        0.5f, -0.5f,  0.5f,  1.0f, 128, 0, 128, 1, 0, 0, 1,
//    //        -0.5f, -0.5f,  0.5f, 1.0f, 128, 0, 128, 1, 0, 0, 1,
//    //        -0.5f, -0.5f, -0.5f, 1.0f, 128, 0, 128, 1, 0, 0, 1,
//    //        -0.5f,  0.5f, -0.5f, 1.0f, 140, 40, 40, 1, 0, 0, 1,
//    //        0.5f,  0.5f, -0.5f,  1.0f, 140, 40, 40, 1, 0, 0, 1,
//    //        0.5f,  0.5f,  0.5f,  1.0f, 140, 40, 40, 1, 0, 0, 1,
//    //        0.5f,  0.5f,  0.5f,  1.0f, 140, 40, 40, 1, 0, 0, 1,
//    //        -0.5f,  0.5f,  0.5f, 1.0f, 140, 40, 40, 1, 0, 0, 1,
//    //        -0.5f,  0.5f, -0.5f, 1.0f, 140, 40, 40, 1, 0, 0, 1,
//    //};
//
//    float triangle[] = {
//        // ��������         ��������     ������
//       -0.5f, -0.5f, -0.5f,  1.0f, 0, 0, 0, 0, -1,
//        0.5f, -0.5f, -0.5f,  1.0f, 0, 1, 0, 0, -1,
//        0.5f,  0.5f, -0.5f,  1.0f, 1, 1, 0, 0, -1,
//        0.5f,  0.5f, -0.5f,  1.0f, 1, 1, 0, 0, -1,
//        -0.5f,  0.5f, -0.5f, 1.0f, 1, 0, 0, 0, -1,
//        -0.5f, -0.5f, -0.5f, 1.0f, 0, 0, 0, 0, -1,
//
//        -0.5f, -0.5f,  0.5f, 1.0f, 0, 0, 0, 0, 1,
//        0.5f, -0.5f,  0.5f,  1.0f, 0, 1, 0, 0, 1,
//        0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 0, 1,
//        0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 0, 1,
//        -0.5f,  0.5f,  0.5f, 1.0f, 1, 0, 0, 0, 1,
//        -0.5f, -0.5f,  0.5f, 1.0f, 0, 0, 0, 0, 1,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0, 0, -1, 0, 0,
//        -0.5f,  0.5f, -0.5f,  1.0f, 0, 1, -1, 0, 0,
//        -0.5f, -0.5f, -0.5f,  1.0f, 1, 1, -1, 0, 0,
//        -0.5f, -0.5f, -0.5f,  1.0f, 1, 1, -1, 0, 0,
//        -0.5f, -0.5f,  0.5f,  1.0f, 1, 0, -1, 0, 0,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0, 0, -1, 0, 0,
//
//        0.5f,  0.5f,  0.5f,  1.0f, 0, 0, 1, 0, 0,
//        0.5f,  0.5f, -0.5f,  1.0f, 0, 1, 1, 0, 0,
//        0.5f, -0.5f, -0.5f,  1.0f, 1, 1, 1, 0, 0,
//        0.5f, -0.5f, -0.5f,  1.0f, 1, 1, 1, 0, 0,
//        0.5f, -0.5f,  0.5f,  1.0f, 1, 0, 1, 0, 0,
//        0.5f,  0.5f,  0.5f,  1.0f, 0, 0, 1, 0, 0,
//
//        -0.5f, -0.5f, -0.5f, 1.0f, 0, 0, 0, -1, 0,
//        0.5f, -0.5f, -0.5f,  1.0f, 0, 1, 0, -1, 0,
//        0.5f, -0.5f,  0.5f,  1.0f, 1, 1, 0, -1, 0,
//        0.5f, -0.5f,  0.5f,  1.0f, 1, 1, 0, -1, 0,
//        -0.5f, -0.5f,  0.5f, 1.0f, 1, 0, 0, -1, 0,
//        -0.5f, -0.5f, -0.5f, 1.0f, 0, 0, 0, -1, 0,
//
//        -0.5f,  0.5f, -0.5f, 1.0f, 0, 0, 0, 1, 0,
//        0.5f,  0.5f, -0.5f,  1.0f, 0, 1, 0, 1, 0,
//        0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 1, 0,
//        0.5f,  0.5f,  0.5f,  1.0f, 1, 1, 0, 1, 0,
//        -0.5f,  0.5f,  0.5f, 1.0f, 1, 0, 0, 1, 0,
//        -0.5f,  0.5f, -0.5f, 1.0f, 0, 0, 0, 1, 0,
//    };
//
//    unsigned int VBO, VAO;
//
//    MVB.mGenVertexArray(1, &VAO);
//    MVB.mGenBuffers(1, &VBO);
//
//    MVB.mBindVertexArray(VAO);
//
//    MVB.mBindBuffer(VBO);
//
//    MVB.mBufferData(sizeof(triangle), triangle);
//
//    //MVB.mEnableVertexAttribArray(ATTR_ARRAY.M_POSITION);
//    //MVB.mVertexAttribPointer(0, 4, 11);
//    //MVB.mEnableVertexAttribArray(ATTR_ARRAY.M_COLOR);
//    //MVB.mVertexAttribPointer(4, 4, 11);
//    //MVB.mEnableVertexAttribArray(ATTR_ARRAY.M_NORMAL);
//    //MVB.mVertexAttribPointer(8, 3, 11);
//
//
//    MVB.mEnableVertexAttribArray(ATTR_ARRAY.M_POSITION);
//    MVB.mVertexAttribPointer(0, 4, 9);
//
//    MVB.mEnableVertexAttribArray(ATTR_ARRAY.M_TEXCOORD);
//    MVB.mVertexAttribPointer(4, 2, 9);
//
//    MVB.mEnableVertexAttribArray(ATTR_ARRAY.M_NORMAL);
//    MVB.mVertexAttribPointer(6, 3, 9);
//
//    MVB.mBindBuffer(0);
//
//    MVB.mBindVertexArray(0);
//
//    Texture texture = Texture(L"container2.png");
//    Bitmap* bmp = texture.GetTextureData();
//
//    // ��Դ��ɫ
//    glm::vec3 dirLightColor = glm::vec3(1.0, 1.0, 1.0);
//    // ���շ���
//    glm::vec3 dirLightDirection = glm::vec3(1.0, 1.0, 1.0);
//    // ��Ӱ��λ��
//    glm::vec3 viewPos = glm::vec3(0, 0, 0);
//
//    int m = 1;
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        processInput(window);
//
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // ������ɫ��
//        ShaderProgram shaderProg = ShaderProgram(MVB.GetVertexs());
//        shaderProg.SetTextureData(bmp);
//        shaderProg.SetDirLightColor(dirLightColor);
//        shaderProg.SetDirLightDirection(dirLightDirection);
//        shaderProg.SetViewPos(viewPos);
//
//        // Ϊ��ɫ���ı�����ֵ
//        // model
//        glm::mat4 model = glm::mat4(1.0);
//        Transform transObj = Transform();
//        glm::mat4 transScale = transObj.Scale(glm::vec3(0.5, 0.5, 0.5)); // ����
//
//        glm::mat4 transTranslate = transObj.Translate(glm::vec3(0, 0, -1.0)); // ƽ��
//
//        glm::vec3 startPos = glm::vec3(0.0, 0.0, 0.0);
//        glm::vec3 direction = glm::vec3(1.2, 1.0, 0.5);
//        glm::mat4 transRotate = transObj.Rotate(startPos, direction, m * 6); // ��ת
//
//        m = (++m) % 60;
//        model = transTranslate * transRotate * transScale;
//
//        // view
//        glm::mat4 view = glm::mat4(1.0);
//
//        // proj
//        glm::mat4 proj = glm::mat4(1.0);
//        proj = transObj.Perspective(-0.5f, -10.0f);
//
//        // ��ɫ����ֵ
//        shaderProg.SetPicUnitVertexNum(3); // ͼԪ�Ķ���������������ͼԪʱ��ֵΪ3��
//        shaderProg.SetModel(model);
//        shaderProg.SetView(view);
//        shaderProg.SetProjection(proj);
//
//        // ��ʼ��ɫ����
//        shaderProg.StartShaderProgram();
//
//        // ��ȡ��ɫ�������
//        std::vector<Vertex> resVertexs = shaderProg.GetResVertexs();
//
//        // ����ɫ������� ӳ�䵽 MFrameBuffer �У�������ʾ
//        std::vector<unsigned char> resBuffer = ShaderToBuffer(resVertexs);
//
//        //����
//        unsigned char* p = resBuffer.data();
//        glDrawPixels(pixCols, pixRows,GL_RGBA, GL_UNSIGNED_BYTE, p);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//
//    return 0;
//}
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//std::vector<unsigned char> ShaderToBuffer(std::vector<Vertex> vertexs) {
//
//    int resVertexsNum = vertexs.size();
//
//    std::vector<unsigned char> resBuffer((pixRows + 2) * (pixCols + 2) * 4);
//
//    // ��㣨����ɫֵ��
//    for (int i = 0;i < resVertexsNum;i++) {
//
//        glm::vec4 position = vertexs[i].GetPosition();
//
//        glm::vec4 color = vertexs[i].GetColor();
//
//        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4] = color.r;
//        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4 + 1] = color.g;
//        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4 + 2] = color.b;
//        resBuffer[pixCols * (int)position.y * 4 + (int)position.x * 4 + 3] = color.a;
//
//    }
//
//    // ��ֵ�˲���1 x 3 �ĺˣ�
//    for (int i = 4; i < (pixRows + 2) * (pixCols + 2) * 4 - 4; i += 4) {
//        unsigned char r1 = resBuffer[i];
//        unsigned char g1 = resBuffer[i + 1];
//        unsigned char b1 = resBuffer[i + 2];
//
//        unsigned char r2 = resBuffer[i + 4];
//        unsigned char g2 = resBuffer[i + 5];
//        unsigned char b2 = resBuffer[i + 6];
//
//        unsigned char r3 = resBuffer[i - 4];
//        unsigned char g3 = resBuffer[i - 3];
//        unsigned char b3 = resBuffer[i - 2];
//
//        resBuffer[i] = (r1 + r2 + r3) / 3;
//        resBuffer[i + 1] = (g1 + g2 + g3) / 3;
//        resBuffer[i + 2] = (b1 + b2 + b3) / 3;
//    }
//
//    return resBuffer;
//}
//
