#include "cube_structure.h"
#include <string>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(void)
{
	//initialize webcam
	cv::VideoCapture webcam(0);

	//initialize Rubik's cube
	Cube rubiks_cube;

	//get each of the Rubik's cube faces from the webcam
	rubiks_cube.initializeCube(webcam);

	//generate cube solution
	rubiks_cube.solveCube();

	//apply moves to cube
	rubiks_cube.applyMoves(webcam);
}


/*
	to-do:
	-arrow maker and state checker using generated moves
	-make interface nicer, have intro when starting, show upcoming moves, make it turn green when face is found, etc
	--publish extensive on github, refactor and clean up, put in folders, email zhengzou
*/