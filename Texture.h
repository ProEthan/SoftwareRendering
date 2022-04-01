#pragma once
/*

Texture；
	纹理类
作用：
	将图片解析成本地数据
变量：
	std::vector<glm::vec4> texture  存放纹理的所有颜色数据

*/
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace std;
using namespace Gdiplus;

class Texture
{
public:
    Texture(wstring imgFileName);
    ~Texture();

    Bitmap* GetTextureData();

private:

    int TestFunction(wstring imgFileName, string outFileName);

    wstring _imgFileName;
    string _outFileName;
    Bitmap* bmp;
};

Texture::Texture(wstring imgFileName)
{
    this->_imgFileName = imgFileName;
}

Texture::~Texture()
{
}

Bitmap* Texture::GetTextureData() {
    GdiplusStartupInput gdiplusstartupinput;
    ULONG_PTR gdiplustoken;
    GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

    Bitmap* bmp = new Bitmap(this->_imgFileName.c_str());

    return bmp;
}

int Texture::TestFunction(wstring imgFileName, string outFileName) {
    GdiplusStartupInput gdiplusstartupinput;
    ULONG_PTR gdiplustoken;
    GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

    wstring infilename = imgFileName;
    string outfilename(outFileName);

    Bitmap* bmp = new Bitmap(infilename.c_str());
    UINT height = bmp->GetHeight();
    UINT width = bmp->GetWidth();
    cout << "width " << width << ", height " << height << endl;

    Color color;
    ofstream fout(outfilename.c_str());

    for (UINT y = 0; y < height; y++){
        for (UINT x = 0; x < width; x++) {
            bmp->GetPixel(x, y, &color);
            fout << x << "," << y << ";"
                << (int)color.GetRed() << ","
                << (int)color.GetGreen() << ","
                << (int)color.GetBlue() << endl;
        }
    }

    fout.close();

    delete bmp;
    GdiplusShutdown(gdiplustoken);
    return 0;
}