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
	};
	void getDisplayImage(cv::Mat & drawingImg)const;
	void keyboardPressed(unsigned char key, int x, int y);
	void mousePressed(int button, int state, int x, int y);
private:
	std::unique_ptr<RealsenseAPI> realsense;
	bool processing = false;
	bool selected = false;
	cv::Scalar selectedPixelValue;
};
