#include "stdafx.h"
#include "RealsenseAPI.h"

using namespace Intel::RealSense;
using namespace cv;
using std::vector;

bool RealsenseAPI::initialize(int width, int height, int fps)
{
	this->width = width;
	this->height = height;
	this->fps = fps;
	this->senseManager = SenseManager::CreateInstance();
	if (senseManager == nullptr) {
		return false;
	}
	this->senseManager->EnableStream(Capture::STREAM_TYPE_COLOR, width, height, fps);
	this->senseManager->Init();
	Capture::Device* device = this->senseManager->QueryCaptureManager()->QueryDevice();
	if (device)
	{
		device->ResetProperties(Capture::STREAM_TYPE_ANY);
		device->SetMirrorMode(Capture::Device::MirrorMode::MIRROR_MODE_HORIZONTAL);
		return true;
	}
	return false;
}

RealsenseAPI::~RealsenseAPI()
{
	if (this->senseManager != nullptr)
	{
		this->senseManager->Release();
	}
}

int RealsenseAPI::getFPS()const
{
	return this->fps;
}

int RealsenseAPI::getHeight()const
{
	return this->height;
}

int RealsenseAPI::getWidth()const
{
	return this->width;
}

void RealsenseAPI::getColorImage(cv::Mat& inputMat)const
{
	if (inputMat.rows != this->height || inputMat.cols != this->width || inputMat.type() != CV_8UC3)
	{
		inputMat = cv::Mat(this->height, this->width, CV_8UC3);
	}


	Status status = senseManager->AcquireFrame(false);
	if (status < Status::STATUS_NO_ERROR)
	{
		std::cout << "err" << std::endl;;
		return;
	}

	const Capture::Sample *sample = senseManager->QuerySample();

	if (sample->color)
	{
		Image::ImageData data = {}; 
		const Image::Rotation rotation = sample->color->QueryRotation();
		status = sample->color->AcquireAccess(Image::ACCESS_READ, Image::PIXEL_FORMAT_RGB24, rotation, Image::OPTION_ANY, &data);
		if (status >= Status::STATUS_NO_ERROR)
		{
			memcpy(inputMat.data, data.planes[0], data.pitches[0] * this->height);
			sample->color->ReleaseAccess(&data);
			senseManager->ReleaseFrame();
		}
	}
}
