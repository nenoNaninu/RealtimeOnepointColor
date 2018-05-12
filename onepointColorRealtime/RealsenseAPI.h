#pragma once
#include"stdafx.h"

class RealsenseAPI
{
public:
	RealsenseAPI() {}
	~RealsenseAPI();
	bool initialize(int width, int height, int fps);
	void getColorImage(cv::Mat& inputMat)const;
	int getWidth()const;
	int getHeight()const;
	int getFPS()const;

private:

	int width, height, fps;
	//namespace Intel::RealSense::Base で
	//private:
	//	/* Call Release() to delele object */
	//	void operator delete(void* pthis);
	//とか書かれているのでスマポは使えない。
	Intel::RealSense::SenseManager* senseManager = nullptr;
};