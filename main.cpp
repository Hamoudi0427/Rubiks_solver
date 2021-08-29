#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "phase3_solve.h"
#include "phase4_solve.h"
#include "pruning_table.h"
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

int main(void)
{

	std::string cube = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";
	cube = rotateCube(cube, { ROT::L, ROT::R, ROT::U, ROT::D2, ROT::D, ROT::L, ROT::UP, ROT::B, ROT::F2, ROT::L, 
		ROT::LP, ROT::UP, ROT::B, ROT::L, ROT::RP, ROT::BP});
	//cube = "BWYYWWBOYBBGRROGRWWGOBGWROWGBOYYGRYRYBOYORGOWOGRWBGBRY";
	std::vector<ROT> complete;

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
}

/*
	Left for solver:
	-OOP if it improves code
	-file database not done at run time using hashes
	-both after we impliment CV
	OpenCV:
	-add depnedencies
	-plan code thourogly
	-plan rubiks class
	-code
	Web:
	-python impliment and use django 
*/