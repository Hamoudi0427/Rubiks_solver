#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "cube_structure.h"

/*
	This file provides functions that determine the color of a cropped image (representing the facelets).
	Note that the color white does not have its own function and is instead determined through the abscence of the other colors.
	Input images are assumed to be blurred and converted to the HSV color space.
*/

//determines if facelet is green
bool isGreen(const cv::Mat& cropped_img)
{
	//upper and lower bound HSV green values
	int hmin = 40, smin = 25, vmin = 0;
	int hmax = 85, smax = 255, vmax = 255;

	//mask facelet with upper and lower bound green color values
	cv::Mat masked_img;
	cv::inRange(cropped_img, cv::Scalar(hmin, smin, vmin), cv::Scalar(hmax, smax, vmax), masked_img);

	//if 60% or more of the facelet is green then the color can be determined
	float img_size = cropped_img.rows * cropped_img.cols;
	float num_masked_pixels = cv::countNonZero(masked_img);
	float masked_percentage = (num_masked_pixels / img_size) * 100;

	if (masked_percentage >= 60.0)
	{
		return true;
	}

	return false;
}

//determines if facelet if blue
bool isBlue(const cv::Mat& cropped_img)
{
	//upper and lower bound HSV blue values
	int hmin = 90, smin = 150, vmin = 0;
	int hmax = 140, smax = 255, vmax = 255;

	//mask facelet with upper and lower bound blue color values
	cv::Mat masked_img;
	cv::inRange(cropped_img, cv::Scalar(hmin, smin, vmin), cv::Scalar(hmax, smax, vmax), masked_img);

	//if 60% or more of the facelet is blue then the color can be determined
	float img_size = cropped_img.rows * cropped_img.cols;
	float num_masked_pixels = cv::countNonZero(masked_img);
	float masked_percentage = (num_masked_pixels / img_size) * 100;

	if (masked_percentage >= 60.0)
	{
		return true;
	}

	return false;
}

//determines if facelet is yellow
bool isYellow(const cv::Mat& cropped_img)
{
	//upper and lower bound HSV yellow values
	int hmin = 22, smin = 0, vmin = 0;
	int hmax = 40, smax = 255, vmax = 255;

	//mask facelet with upper and lower bound yellow color values
	cv::Mat masked_img;
	cv::inRange(cropped_img, cv::Scalar(hmin, smin, vmin), cv::Scalar(hmax, smax, vmax), masked_img);

	//if 60% or more of the facelet is yellow then the color can be determined
	float img_size = cropped_img.rows * cropped_img.cols;
	float num_masked_pixels = cv::countNonZero(masked_img);
	float masked_percentage = (num_masked_pixels / img_size) * 100;

	if (masked_percentage >= 60.0)
	{
		return true;
	}

	return false;
}

//determines if facelet is orange
bool isOrange(const cv::Mat& cropped_img)
{
	//upper and lower bound HSV orange values
	int hmin = 6, smin = 100, vmin = 0;
	int hmax = 22, smax = 255, vmax = 255;

	//mask facelet with upper and lower bound orange color values
	cv::Mat masked_img;
	cv::inRange(cropped_img, cv::Scalar(hmin, smin, vmin), cv::Scalar(hmax, smax, vmax), masked_img);

	//if 60% or more of the facelet is orange then the color can be determined
	float img_size = cropped_img.rows * cropped_img.cols;
	float num_masked_pixels = cv::countNonZero(masked_img);
	float masked_percentage = (num_masked_pixels / img_size) * 100;

	if (masked_percentage >= 60.0)
	{
		return true;
	}

	return false;
}

//determines if facelet if red
bool isRed(const cv::Mat& cropped_img)
{
	//upper and lower bound HSV red values (red has two thresholds)
	int hmin_dark = 0, smin_dark = 50, vmin_dark = 20;
	int hmax_dark = 5, smax_dark = 255, vmax_dark = 255;
	int hmin_light = 170, smin_light = 50, vmin_light = 20;
	int hmax_light = 180, smax_light = 255, vmax_light = 255;

	//mask facelet with upper and lower bound red color values
	cv::Mat masked_img_dark, masked_img_light, masked_img;
	cv::inRange(cropped_img, cv::Scalar(hmin_dark, smin_dark, vmin_dark), cv::Scalar(hmax_dark, smax_dark, vmax_dark), masked_img_dark);
	cv::inRange(cropped_img, cv::Scalar(hmin_light, smin_light, vmin_light), cv::Scalar(hmax_light, smax_light, vmax_light), masked_img_light);
	cv::bitwise_or(masked_img_dark, masked_img_light, masked_img);

	//if 60% or more of the facelet is red then the color can be determined
	float img_size = cropped_img.rows * cropped_img.cols;
	float num_masked_pixels = cv::countNonZero(masked_img);
	float masked_percentage = (num_masked_pixels / img_size) * 100;

	if (masked_percentage >= 60.0)
	{
		return true;
	}

	return false;
}

//determines the color of a facelet
COLOR getColor(const cv::Mat& cropped_img)
{
	if (isRed(cropped_img))
	{
		return COLOR::R;
	}
	else if (isBlue(cropped_img))
	{
		return COLOR::B;
	}
	else if (isYellow(cropped_img))
	{
		return COLOR::Y;
	}
	else if (isOrange(cropped_img))
	{
		return COLOR::O;
	}
	else if (isGreen(cropped_img))
	{
		return COLOR::G;
	}
	else
	{
		return COLOR::W;
	}
}