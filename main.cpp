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
	Cube cube;
	cube.initializeCube(webcam);



	/*
	prac2(webcam); return 0;
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
	*.
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
	-make cube face function have a threshold where it must have got the same read 500 times (tweak to accept face and have checker)
	-get init face function (gets sides in order and inits cube class)
	-impliment solver within class
	-arrow maker and state checker using generated moves
	-make interface nicer, have intro when starting, show upcoming moves, make it turn green when face is found, etc
	--publish extensive on github, refactor and clean up, put in folders, email zhengzou
*/