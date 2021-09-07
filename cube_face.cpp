#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include "cube_structure.h"
#include "facelet_rotate.h"
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

void Cube::drawFacelets(cv::Mat& img_resize, cv::Scalar color)
{
	cv::rectangle(img_resize, cv::Point(270, 200), cv::Point(330, 260), color, 2);
	cv::rectangle(img_resize, cv::Point(350, 200), cv::Point(410, 260), color, 2);
	cv::rectangle(img_resize, cv::Point(430, 200), cv::Point(490, 260), color, 2);
	cv::rectangle(img_resize, cv::Point(270, 280), cv::Point(330, 340), color, 2);
	cv::rectangle(img_resize, cv::Point(350, 280), cv::Point(410, 340), color, 2);
	cv::rectangle(img_resize, cv::Point(430, 280), cv::Point(490, 340), color, 2);
	cv::rectangle(img_resize, cv::Point(270, 360), cv::Point(330, 420), color, 2);
	cv::rectangle(img_resize, cv::Point(350, 360), cv::Point(410, 420), color, 2);
	cv::rectangle(img_resize, cv::Point(430, 360), cv::Point(490, 420), color, 2);
}

void Cube::drawArrows(cv::Mat& img_resize, ROT move)
{
	switch (move)
	{
	case ROT::U:
		cv::arrowedLine(img_resize, cv::Point(300, 230), cv::Point(460, 230), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::UP:
		cv::arrowedLine(img_resize, cv::Point(460, 230), cv::Point(300, 230), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::U2:
		cv::arrowedLine(img_resize, cv::Point(300, 215), cv::Point(460, 215), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(300, 245), cv::Point(460, 245), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::DP:
		cv::arrowedLine(img_resize, cv::Point(300, 390), cv::Point(460, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::D:
		cv::arrowedLine(img_resize, cv::Point(460, 390), cv::Point(300, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::D2:
		cv::arrowedLine(img_resize, cv::Point(460, 375), cv::Point(300, 375), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(460, 405), cv::Point(300, 405), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::RP:
		cv::arrowedLine(img_resize, cv::Point(460, 230), cv::Point(460, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::R:
		cv::arrowedLine(img_resize, cv::Point(460, 390), cv::Point(460, 230), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::R2:
		cv::arrowedLine(img_resize, cv::Point(475, 230), cv::Point(475, 390), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(445, 230), cv::Point(445, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::L:
		cv::arrowedLine(img_resize, cv::Point(300, 230), cv::Point(300, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::LP:
		cv::arrowedLine(img_resize, cv::Point(300, 390), cv::Point(300, 230), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::L2:
		cv::arrowedLine(img_resize, cv::Point(315, 230), cv::Point(315, 390), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(285, 230), cv::Point(285, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::BP:
		cv::arrowedLine(img_resize, cv::Point(300, 230), cv::Point(460, 230), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::B:
		cv::arrowedLine(img_resize, cv::Point(460, 230), cv::Point(300, 230), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::B2:
		cv::arrowedLine(img_resize, cv::Point(300, 215), cv::Point(460, 215), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(300, 245), cv::Point(460, 245), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::F:
		cv::arrowedLine(img_resize, cv::Point(300, 390), cv::Point(460, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::FP:
		cv::arrowedLine(img_resize, cv::Point(460, 390), cv::Point(300, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::F2:
		cv::arrowedLine(img_resize, cv::Point(460, 375), cv::Point(300, 375), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(460, 405), cv::Point(300, 405), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::MD:
		cv::arrowedLine(img_resize, cv::Point(460, 230), cv::Point(460, 390), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(300, 230), cv::Point(300, 390), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(380, 230), cv::Point(380, 390), cv::Scalar(0, 0, 255), 3);
		break;
	case ROT::MU:
		cv::arrowedLine(img_resize, cv::Point(460, 390), cv::Point(460, 230), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(300, 390), cv::Point(300, 230), cv::Scalar(0, 0, 255), 3);
		cv::arrowedLine(img_resize, cv::Point(380, 390), cv::Point(380, 230), cv::Scalar(0, 0, 255), 3);
		break;
	}
}

//will check if a face is found
bool Cube::isFaceFound(const std::map<std::string, int>& face_count)
{
	for (auto face : face_count)
	{
		if (face.second >= 20)
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
Face Cube::getValidCubeFace(cv::VideoCapture& webcam, COLOR side, std::string message)
{
	while (webcam.isOpened())
	{
		std::map<std::string, int> face_count;
		Face face;
		cv::Mat img, img_resize;

		//will continue until the face is verified
		while (!isFaceFound(face_count))
		{	
			//read the image from the webcam
			webcam.read(img);
			cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
			drawFacelets(img_resize, cv::Scalar(255, 255, 255));

			//get face
			face = getCubeFace(img_resize);
			addFaceToMap(face_count, face);

			//display the image
			cv::putText(img_resize, message, cv::Point(10, 590), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(200, 200, 250), 1);
			cv::imshow("Rubik's Cube Solver", img_resize);
			cv::waitKey(10);
		}

		//will check if the correct face was found
		if (face.getFaceletColor(4) == side)
		{
			drawFacelets(img_resize, cv::Scalar(0, 255, 0));
			cv::imshow("Rubik's Cube Solver", img_resize);
			cv::waitKey(500);
			return face;
		}
	}
}

//initializes cube structure
void Cube::initializeCube(cv::VideoCapture& webcam)
{
	//get each face
	Face front_face = this -> getValidCubeFace(webcam, COLOR::G, "Green Face (White Side as Up)");
	front_face.printFace();
	std::cout << std::endl;

	Face right_face = this -> getValidCubeFace(webcam, COLOR::R, "Red Face (White Side as Up)");
	right_face.printFace();
	std::cout << std::endl;

	Face back_face = this -> getValidCubeFace(webcam, COLOR::B, "Blue Face (White Side as Up)");
	back_face.printFace();
	std::cout << std::endl;

	Face left_face = this -> getValidCubeFace(webcam, COLOR::O, "Orange Face (White Side as Up)");
	left_face.printFace();
	std::cout << std::endl;

	Face up_face = this -> getValidCubeFace(webcam, COLOR::W, "White Face (Blue Side as Up)");
	up_face.printFace();
	std::cout << std::endl;

	Face down_face = this -> getValidCubeFace(webcam, COLOR::Y, "Yellow Face (Green Side as Up)");
	down_face.printFace();
	std::cout << std::endl;

	//initialize the cube
	cube[0] = up_face; 
	cube[1] = right_face; 
	cube[2] = front_face; 
	cube[3] = down_face; 
	cube[4] = left_face; 
	cube[5] = back_face; 

	//convert string representation
	facelet_cube = this->convertToString(); 
}

//apply moves on the cube until it is solved
void Cube::applyMoves(cv::VideoCapture& webcam)
{
	//start at front face (green)
	SIDE current_face = SIDE::F;
	
	while (solution.size() != 0)
	{
		//get current move
		ROT move = solution[0];
		solution.erase(solution.begin());

		//apply move to the actual cube
		Face face;
		cv::Mat img, img_resize;

		//ensure cube is on the correct side before applying the move
		if ((rotationToString(move)[0] == 'L' || rotationToString(move)[0] == 'R' || rotationToString(move)[0] == 'U' || rotationToString(move)[0] == 'D') && (current_face != SIDE::F))
		{
			while (face != cube[2])
			{
				//read the image from the webcam
				webcam.read(img);
				cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
				drawFacelets(img_resize, cv::Scalar(255, 255, 255));
				drawArrows(img_resize, ROT::MU);
				cv::imshow("Rubik's Cube Solver", img_resize);
				face = getCubeFace(img_resize);
				cv::waitKey(20);
			}

			current_face = SIDE::F;
		}
		else if ((rotationToString(move)[0] == 'F' || rotationToString(move)[0] == 'B') && (current_face != SIDE::U))
		{
			while (face != cube[0])
			{
				//read the image from the webcam
				webcam.read(img);
				cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
				drawFacelets(img_resize, cv::Scalar(255, 255, 255));
				drawArrows(img_resize, ROT::MD);
				cv::imshow("Rubik's Cube Solver", img_resize);
				face = getCubeFace(img_resize);
				cv::waitKey(20);
			}

			current_face = SIDE::U;
		}

		//apply move to the cube
		facelet_cube = rotateCube(facelet_cube, { move });
		this->stringToCube();

		//ensure move is applied
		if (rotationToString(move)[0] == 'L' || rotationToString(move)[0] == 'R' || rotationToString(move)[0] == 'U' || rotationToString(move)[0] == 'D')
		{
			while (face != cube[2])
			{
				//read the image from the webcam
				webcam.read(img);
				cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
				drawFacelets(img_resize, cv::Scalar(255, 255, 255));
				drawArrows(img_resize, move);
				cv::imshow("Rubik's Cube Solver", img_resize);
				face = getCubeFace(img_resize);
				cv::waitKey(100);
			}
		}
		else if (rotationToString(move)[0] == 'F' || rotationToString(move)[0] == 'B')
		{
			while (face != cube[0])
			{
				//read the image from the webcam
				webcam.read(img);
				cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);
				drawFacelets(img_resize, cv::Scalar(255, 255, 255));
				drawArrows(img_resize, move);
				cv::imshow("Rubik's Cube Solver", img_resize);
				face = getCubeFace(img_resize);
				cv::waitKey(100);
			}
		}
	}
}