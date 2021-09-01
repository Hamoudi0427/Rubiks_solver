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

int main(void)
{

	std::string cube = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";
	cube = rotateCube(cube, { ROT::L, ROT::R, ROT::U, ROT::D2, ROT::D, ROT::L, ROT::R, ROT::UP, ROT::D, ROT::BP, ROT::U2, ROT::L, ROT::U, ROT::BP, ROT::D2, ROT::L2
		, ROT::U, ROT::B, ROT::L, ROT::U2, ROT::D, ROT::R, ROT::L, ROT::D2, ROT::UP, ROT::L, ROT::D, ROT::B2
		, ROT::L, ROT::D, ROT::F2, ROT::LP, ROT::U2, ROT::D, ROT::B2, ROT::F2, ROT::L, ROT::D2, ROT::B, 
		ROT::LP, ROT::B2, ROT::D, ROT::F});
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