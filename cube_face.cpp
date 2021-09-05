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
	Part of the cube class.
*/

//crops 9 facelets from the image and returns them in a vector (converted to HSV and blurred for the color functions)
std::vector<cv::Mat> Cube::faceletCrop(const cv::Mat& img)
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

void Cube::drawFacelets(cv::Mat& img_resize)
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
bool Cube::isFaceFound(const std::map<std::string, int>& face_count)
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
void Cube::addFaceToMap(std::map<std::string, int>& face_count, Face& face)
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
Face Cube::getCubeFace(const cv::Mat& img)
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

//returns the specified cube face (U, D, R, L, B, F) by checking the middle facelet
Face Cube::getValidCubeFace(cv::VideoCapture& webcam, COLOR side)
{
	while (webcam.isOpened())
	{
		//map to keep track of previous faces
		std::map<std::string, int> face_count;

		//face that will be returned
		Face face;

		//will continue until the face is verified
		while (!isFaceFound(face_count))
		{	
			//read the image from the webcam
			cv::Mat img, img_resize;
			webcam.read(img);
			cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
			drawFacelets(img_resize);

			//get face
			face = getCubeFace(img_resize);
			addFaceToMap(face_count, face);

			//display the image
			cv::imshow("Rubik's Cube Solver", img_resize);
			cv::waitKey(10);
		}

		//will check if the correct face was found
		if (face.getFaceletColor(4) == side)
		{
			return face;
		}
	}
}

//initializes cube structure
void Cube::initializeCube(cv::VideoCapture& webcam)
{
	//get each face
	Face front_face = this -> getValidCubeFace(webcam, COLOR::G); 
	front_face.printFace(); 
	Face right_face = this -> getValidCubeFace(webcam, COLOR::R); 
	right_face.printFace(); 
	Face back_face = this -> getValidCubeFace(webcam, COLOR::B); 
	back_face.printFace();
	Face left_face = this -> getValidCubeFace(webcam, COLOR::O); 
	left_face.printFace();
	Face up_face = this -> getValidCubeFace(webcam, COLOR::W); 
	up_face.printFace();
	Face down_face = this -> getValidCubeFace(webcam, COLOR::Y); 
	down_face.printFace();

	//initialize the cube
	cube[0] = front_face;
	cube[1] = right_face;
	cube[2] = up_face;
	cube[3] = down_face;
	cube[4] = left_face;
	cube[5] = back_face;
}