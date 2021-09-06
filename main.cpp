#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "phase3_solve.h"
#include "phase4_solve.h"
#include "pruning_table.h"
#include "cube_structure.h"
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
	Cube cubes;
	cubes.initializeCube(webcam);
	cubes.solveCube();
}

/*
	to-do:
	-arrow maker and state checker using generated moves
	-make interface nicer, have intro when starting, show upcoming moves, make it turn green when face is found, etc
	--publish extensive on github, refactor and clean up, put in folders, email zhengzou
*/