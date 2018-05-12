#pragma once
#include "stdafx.h"
#include "RealsenseAPI.h"

class ImageProcessingRoot
{
public:
	ImageProcessingRoot(int width, int height, int fps)
	{
		realsense.reset(new RealsenseAPI());
		realsense->initialize(width, height, fps);
		//writer.open("./save.avi", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), 60.0, cv::Size(width,height));
	};
	void getDisplayImage(cv::Mat & drawingImg);
	void keyboardPressed(unsigned char key, int x, int y);
	void mousePressed(int button, int state, int x, int y);
private:
	std::unique_ptr<RealsenseAPI> realsense;
	bool processing = false;
	bool selected = false;
	cv::Vec3b selectedPixelValue;
	//cv::VideoWriter writer;
};
