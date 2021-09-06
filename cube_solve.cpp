#include "cube_structure.h"
#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "phase3_solve.h"
#include "phase4_solve.h"
#include "opencv2/opencv.hpp"

/*
	Cube solver that solves cube once the cube is initialized from the webcam.
	Average runtime is about 45 seconds.
*/

void Cube::solveCube(void)
{
	std::string temp_cube = facelet_cube; 
	
	//G0 -> G1
	cv::Mat g0 = cv::imread("Solution_Loading_Screen/G0.png");
	cv::imshow("Rubik's Cube Solver", g0);
	cv::waitKey(100);

	std::vector<ROT> sol = getShortestG1Moves(getEdgeMask(temp_cube));
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//G1 -> G2
	cv::Mat g1 = cv::imread("Solution_Loading_Screen/G1.png");
	cv::imshow("Rubik's Cube Solver", g1);
	cv::waitKey(100);

	sol = getShortestG2Moves(getCornerMask(temp_cube));
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//G2 -> G3
	cv::Mat g2 = cv::imread("Solution_Loading_Screen/G2.png");
	cv::imshow("Rubik's Cube Solver", g2);
	cv::waitKey(100);

	sol = getShortestG3Moves(getOrbitMask(temp_cube));
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//G3 -> Solved
	cv::Mat g3 = cv::imread("Solution_Loading_Screen/G3.png");
	cv::imshow("Rubik's Cube Solver", g3);
	cv::waitKey(100);

	sol = getShortestSolvedMoves(temp_cube);
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//display solved image
	cv::Mat solved = cv::imread("Solution_Loading_Screen/Solved.png");
	cv::imshow("Rubik's Cube Solver", solved);
	cv::waitKey(500);
	
	std::cout << this -> solution;
}