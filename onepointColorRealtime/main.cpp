// main.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "RealsenseAPI.h"
#include "glImshow.h"

using namespace cv;

void display();
void keyboard(unsigned char key, int x, int y);
void mainLoop();
void keyPressed(int button, int state, int x, int y);

std::unique_ptr<RealsenseAPI> realsense;

int main(int argc, char *argv[])
{
	const int width = 640;
	const int height = 480;
	const int fps = 60;
	realsense.reset(new RealsenseAPI());
	realsense->initialize(width, height, fps);
	glImshowInit(argc, argv, width, height, "glImshow", GLUT_RGB);
	glImshowSetFunc(display, keyboard, mainLoop,keyPressed);
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
		break;
	}
}

void mainLoop()
{
	cv::Mat mat;
	realsense->getColorImage(mat);
	glImshow(mat, CV_BGR2RGB, GL_RGB);
}

void keyPressed(int button, int state, int x, int y)
{
	
}