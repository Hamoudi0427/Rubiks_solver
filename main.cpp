#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "phase3_solve.h"
#include "phase4_solve.h"
#include "pruning_table.h"
#include "cube_structure.h"
#include "cube_face.h"
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(void)
{
	cv::VideoCapture webcam(0);
	while (webcam.isOpened())
	{
		cv::Mat img, img_resize;
		webcam.read(img);
		cv::resize(img, img_resize, cv::Size(800, 600), cv::INTER_LINEAR);

		cv::rectangle(img_resize, cv::Point(270, 200), cv::Point(330, 260), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(350, 200), cv::Point(410, 260), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(430, 200), cv::Point(490, 260), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(270, 280), cv::Point(330, 340), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(350, 280), cv::Point(410, 340), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(430, 280), cv::Point(490, 340), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(270, 360), cv::Point(330, 420), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(350, 360), cv::Point(410, 420), cv::Scalar(255, 255, 255), 2);
		cv::rectangle(img_resize, cv::Point(430, 360), cv::Point(490, 420), cv::Scalar(255, 255, 255), 2);

		Face face = getCubeFace(img_resize);
		face.printFace();
		std::cout << std::endl;

		cv::imshow("img", img_resize);
		cv::waitKey(10);
	}

	
	
	/*
	std::string cube = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";
	cube = rotateCube(cube, { ROT::L, ROT::R, ROT::U, ROT::D2, ROT::D, ROT::L, ROT::R, ROT::UP, ROT::D, ROT::BP, ROT::U2, ROT::L, ROT::U, ROT::BP, ROT::D2, ROT::L2
		, ROT::U, ROT::B, ROT::L, ROT::U2, ROT::D, ROT::R, ROT::L, ROT::D2, ROT::UP, ROT::L, ROT::D, ROT::B2
		, ROT::L, ROT::D});
	//cube = "YWWYWWYYWORRORRORRGGBGGBGBBWWYWYYWYYOORROOOORBGGBBGBBG";
	std::vector<ROT> complete;

	//test
	Face up{ {{{COLOR::B, COLOR::B, COLOR::B}, {COLOR::B, COLOR::B, COLOR::B}, {COLOR::B, COLOR::B, COLOR::B}}} };
	up.setFaceletColor(8, COLOR::R);
	if (up[8] == COLOR::R)
	{
		std::cout << "blue here";
	}

	//g1
	std::vector<ROT> sol = getShortestG1Moves(getEdgeMask(cube));
	for (auto s : sol)
	{
		complete.push_back(s);
	}
	std::cout << sol.size() << std::endl;
	cube = rotateCube(cube, sol);
	printCube(cube);

	//g2
	sol = getShortestG2Moves(getCornerMask(cube));
	cube = rotateCube(cube, sol);
	for (auto s : sol)
	{
		complete.push_back(s);
	}
	std::cout << sol.size() << std::endl;
	printCube(cube);

	//g3
	std::string phase3 = getOrbitMask(cube);
	sol = getShortestG3Moves(phase3);
	for (auto s : sol)
	{
		complete.push_back(s);
	}
	std::cout << sol.size() << std::endl;
	cube = rotateCube(cube, sol);
	printCube(cube);
	

	//g4
	sol = getShortestSolvedMoves(cube);
	for (auto s : sol)
	{
		complete.push_back(s);
	}
	cube = rotateCube(cube, sol);
	std::cout << sol.size() << std::endl;
	printCube(cube);
	std::cout << complete;
	
	return 0;

	*/
}

/*
	to-do:
	-tweak colors and thresholds
	-make cube face function have a threshold where it must have got the same read 500 times
	-get init face function (gets sides in order and inits cube class)
	-impliment solver within class
	-arrow maker and state checker using generated moves
	-make interface nicer, have intro when starting, show upcoming moves, make it turn green when face is found, etc
	--publish extensive on github, refactor and clean up, put in folders, email zhengzou
*/