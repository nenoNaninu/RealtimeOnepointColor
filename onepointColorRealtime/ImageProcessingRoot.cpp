#include "stdafx.h"
#include "ImageProcessingRoot.h"

using namespace cv;

void ImageProcessingRoot::getDisplayImage(cv::Mat & drawingImg)
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
            Vec3b lowerRange, upperRange;
            /*******************************hsvで色を抜こうとしていた時のコード*********************/
            //Vec3b diff(7, 15, 40);

            //lowerRange[0] = selectedPixelValue[0] < diff[0] ? 0 : selectedPixelValue[0] - diff[0];
            //lowerRange[1] = selectedPixelValue[1] < diff[1] ? 0 : selectedPixelValue[1] - diff[1];
            //lowerRange[2] = selectedPixelValue[2] < diff[2] ? 0 : selectedPixelValue[2] - diff[2];

            //upperRange[0] = 180 < selectedPixelValue[0] + diff[0] ? 180 : selectedPixelValue[0] + diff[0];
            //upperRange[1] = 180 < selectedPixelValue[1] + diff[1] ? 255 : selectedPixelValue[1] + diff[1];
            //upperRange[2] = 180 < selectedPixelValue[2] + diff[2] ? 255 : selectedPixelValue[2] + diff[2];


            ////inRange(hsvImage, lowerRange, upperRange, mask);
            //inRange(hsvPanels[0], lowerRange[0], upperRange[0], mask);
            /***************************************************************************************/
            /***********************************RGBで色を抜いてみる。*******************************/

            Vec3b diff(30, 30, 30);

            lowerRange[0] = selectedPixelValue[0] < diff[0] ? 0 : selectedPixelValue[0] - diff[0];
            lowerRange[1] = selectedPixelValue[1] < diff[1] ? 0 : selectedPixelValue[1] - diff[1];
            lowerRange[2] = selectedPixelValue[2] < diff[2] ? 0 : selectedPixelValue[2] - diff[2];

            upperRange[0] = 255 < (int)selectedPixelValue[0] + diff[0] ? 255 : selectedPixelValue[0] + diff[0];
            upperRange[1] = 255 < (int)selectedPixelValue[1] + diff[1] ? 255 : selectedPixelValue[1] + diff[1];
            upperRange[2] = 255 < (int)selectedPixelValue[2] + diff[2] ? 255 : selectedPixelValue[2] + diff[2];

            Mat smoothImg;
            edgePreservingFilter(cameraImage, smoothImg);

            inRange(smoothImg, lowerRange, upperRange, mask);

            /***************************************************************************************/

            erode(mask, mask, Mat());
            dilate(mask, mask, Mat());
            erode(mask, mask, Mat());
            dilate(mask, mask, Mat());
            cv::imshow("mask", mask);
            cv::waitKey(1);
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
    //writer << drawingImg;

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

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Mat cameraImage;
        realsense->getColorImage(cameraImage);
        //Mat hsvImage;
        //cvtColor(cameraImage, hsvImage, CV_BGR2HSV);
        //auto h = hsvImage.data[hsvImage.step*y + hsvImage.elemSize()*x];
        //auto s = hsvImage.data[hsvImage.step*y + hsvImage.elemSize()*x + 1];
        //auto v = hsvImage.data[hsvImage.step*y + hsvImage.elemSize()*x + 2];
        //std::cout << "h" << +h << " s" << +s << " v" << +v << std::endl;
        
        edgePreservingFilter(cameraImage, cameraImage);
        auto b = cameraImage.data[cameraImage.step*y + cameraImage.elemSize()*x];
        auto g = cameraImage.data[cameraImage.step*y + cameraImage.elemSize()*x + 1];
        auto r = cameraImage.data[cameraImage.step*y + cameraImage.elemSize()*x + 2];
        std::cout << "r" << +r << " g" << +g << " b" << +b << std::endl;

        //selectedPixelValue = Vec3b(h, s, v);
        selectedPixelValue = Vec3b(b, g, r);
        selected = true;
    }
}
