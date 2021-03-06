// main.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "glImshow.h"
#include "ImageProcessingRoot.h"

void display();
void keyboard(unsigned char key, int x, int y);
void mainLoop();
void mousePressed(int button, int state, int x, int y);

std::unique_ptr<ImageProcessingRoot> imageProcessingRoot;

int main(int argc, char *argv[])
{
    std::cout << "Click on the color you want to select" << std::endl;
    std::cout << "Press R to reset color" << std::endl;
    std::cout << "Press S to start or stop image processing" << std::endl;
    std::cout << "Press q to quit" << std::endl;

    const int width = 640;
    const int height = 480;
    const int fps = 60;

    imageProcessingRoot.reset(new ImageProcessingRoot(width, height, fps));

    glImshowInit(argc, argv, width, height, "glImshow", GLUT_RGB);
    glImshowSetFunc(display, keyboard, mainLoop, mousePressed);
    glImshowStart();
    return 0;
}

void display()
{
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033':
        glutLeaveMainLoop();
    default:
        imageProcessingRoot->keyboardPressed(key, x, y);
        break;
    }
}

void mainLoop()
{
    cv::Mat mat;
    //realsense->getColorImage(mat);
    imageProcessingRoot->getDisplayImage(mat);
    glImshow(mat, CV_BGR2RGB, GL_RGB);
}

void mousePressed(int button, int state, int x, int y)
{
    imageProcessingRoot->mousePressed(button, state, x, y);
}