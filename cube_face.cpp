#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include "cube_structure.h"
#include "cube_colors.h"
#include <string>
#include <vector>
#include <map>

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

	cv::Mat lower_left = img_blur(cv::Range(360, 420), cv::Range(270, 330)); 
	cv::Mat lower_middle = img_blur(cv::Range(360, 420), cv::Range(350, 410));
	cv::Mat lower_right = img_blur(cv::Range(360, 420), cv::Range(430, 490));

	return {upper_left, upper_middle, upper_right, middle_left, middle_middle, middle_right, lower_left, lower_middle, lower_right};
}

void drawFacelets(cv::Mat& img_resize)
{
	cv::rectangle(img_resize, cv::Point(270, 200), cv::Point(330, 260), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(350, 200), cv::Point(410, 260), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(430, 200), cv::Point(490, 260), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(270, 280), cv::Point(330, 340), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(350, 280), cv::Point(410, 340), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(430, 280), cv::Point(490, 340), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(270, 360), cv::Point(330, 420), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(350, 360), cv::Point(410, 420), cv::Scalar(255, 255, 255), 2);
	cv::rectangle(img_resize, cv::Point(430, 360), cv::Point(490, 420), cv::Scalar(255, 255, 255), 2);
}

//will check if a face is found
bool isFaceFound(const std::map<std::string, int>& face_count)
{
	for (auto face : face_count)
	{
		if (face.second >= 30)
		{
			return true;
		}
	}

	return false;
}

//add face to the map to keep track of previously found faces
void addFaceToMap(std::map<std::string, int>& face_count, Face& face)
{
	if (face_count.find(face.getFaceString()) == face_count.end())
	{
		face_count[face.getFaceString()] = 1;
	}
	else
	{
		face_count[face.getFaceString()] += 1;
	}
}

//returns the face coresponding to the image
Face getCubeFace(const cv::Mat& img)
{
	//get cropped facelet
	std::vector<cv::Mat> cropped_facelets = faceletCrop(img);

	//get the face with the facelet colors
	Face face;
	for (int i = 0; i < cropped_facelets.size(); i++)
	{
		COLOR color = getColor(cropped_facelets[i]);
		face.setFaceletColor(i, color);
	}

	return face;
}

void prac2(cv::VideoCapture& webcam)
{
	while (webcam.isOpened())
	{
		std::map<std::string, int> face_count;
		while (!isFaceFound(face_count))
		{	//raad image
			cv::Mat img, img_resize;
			webcam.read(img);
			cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
			drawFacelets(img_resize);


			//get face
			Face face = getCubeFace(img_resize);
			addFaceToMap(face_count, face);
			face.printFace();
			std::cout << "hi" << std::endl;
			cv::imshow("Rubik's Cube Solver", img_resize);
			cv::waitKey(10);
		}
		std::cout << std::endl; break;
	}
}