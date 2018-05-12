#include "stdafx.h"
#include "ImageProcessingRoot.h"

using namespace cv;

void ImageProcessingRoot::getDisplayImage(cv::Mat & drawingImg)const
{

	if (processing)
	{
		Mat cameraImage;
		realsense->getColorImage(cameraImage);
		Mat hsvImage;
		cvtColor(cameraImage, hsvImage, CV_BGR2HSV);
		std::vector<Mat> hsvPanels;
		split(hsvImage, hsvPanels);

		if (selected)
		{
			Mat mask(realsense->getHeight(), realsense->getHeight(), CV_8UC1);
			//const Scalar diff(5, 20, 20);
			inRange(hsvPanels[0], selectedPixelValue[0] - 7, selectedPixelValue[0] + 7, mask);
			erode(mask, mask, Mat());
			erode(mask, mask, Mat());
			dilate(mask, mask, Mat());
			dilate(mask, mask, Mat());
			hsvPanels[1].setTo(0, ~mask);
			merge(hsvPanels, hsvImage);

		}
		else
		{
			hsvPanels[1] = 0;
			merge(hsvPanels, hsvImage);
		}
		cvtColor(hsvImage, drawingImg, CV_HSV2BGR);
	}
	else
	{
		realsense->getColorImage(drawingImg);
	}

}

void ImageProcessingRoot::keyboardPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'S':
	case 's':
		processing = !processing;
		break;
	case 'R':
	case 'r':
		selected = false;
	}
}

void ImageProcessingRoot::mousePressed(int button, int state, int x, int y)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Mat cameraImage;
		realsense->getColorImage(cameraImage);
		Mat hsvImage;
		cvtColor(cameraImage, hsvImage, CV_BGR2HSV);
		auto h = hsvImage.data[hsvImage.step*y + hsvImage.elemSize()*x];
		auto s = hsvImage.data[hsvImage.step*y + hsvImage.elemSize()*x +1];
		auto v = hsvImage.data[hsvImage.step*y + hsvImage.elemSize()*x +2];
		std::cout << "h" << +h << " s" << +s << " v" << +v << std::endl;
		selectedPixelValue = Scalar(h, s, v);
		selected = true;
	}
}
