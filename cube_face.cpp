#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "cube_structure.h"
#include "cube_colors.h"
#include <vector>

/*
	This file provides the functions needed to extract the cube face from image.
	This is done by using the facelet borders that will be displayed in the 800 x 600 webcam.
*/

//crops 9 facelets from the image and returns them in a vector (converted to HSV and blurred for the color functions)
std::vector<cv::Mat> faceletCrop(const cv::Mat& img)
{
	//pre-process by bluring and converting to the HSV color space
	cv::Mat img_blur, img_hsv;
	cv::cvtColor(img, img_hsv, cv::COLOR_BGR2HSV);
	cv::GaussianBlur(img_hsv, img_blur, cv::Size(11, 11), 3, 0);

	//crop images
	cv::Mat upper_left = img_blur(cv::Range(200, 260), cv::Range(270, 330)); 
	cv::Mat upper_middle = img_blur(cv::Range(200, 260), cv::Range(350, 410)); 
	cv::Mat upper_right = img_blur(cv::Range(200, 260), cv::Range(430, 490)); 

	cv::Mat middle_left = img_blur(cv::Range(280, 340), cv::Range(270, 330)); 
	cv::Mat middle_middle = img_blur(cv::Range(280, 340), cv::Range(350, 410));
	cv::Mat middle_right = img_blur(cv::Range(280, 340), cv::Range(430, 490));

	cv::Mat lower_left = img_blur(cv::Range(360, 420), cv::Range(270, 330)); //360, 420
	cv::Mat lower_middle = img_blur(cv::Range(360, 420), cv::Range(350, 410));
	cv::Mat lower_right = img_blur(cv::Range(360, 420), cv::Range(430, 490));

	return {upper_left, upper_middle, upper_right, middle_left, middle_middle, middle_right, lower_left, lower_middle, lower_right};
}

//returns the face coresponding to the image
Face getCubeFace(const cv::Mat& img)
{
	//get cropped facelets
	std::vector<cv::Mat> cropped_facelets = faceletCrop(img);

	for (auto facelet : cropped_facelets)
	{
		cv::Mat bgr;
		cv::cvtColor(facelet, bgr, cv::COLOR_HSV2RGB);
		cv::imshow("facelet", bgr);
	}

	//get the face with the facelet colors
	Face face;
	for (int i = 0; i < cropped_facelets.size(); i++)
	{
		COLOR color = getColor(cropped_facelets[i]);
		face.setFaceletColor(i, color);
	}

	return face;
}