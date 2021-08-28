#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "phase3_solve.h"
#include "pruning_table.h"
#include <string>
#include <iostream>
#include <map>

int main(void)
{
	std::string cube = "YRGGWRBYOBWRORYOYBRBWOGYOBYYOGGYGOBRGOWROWGWBWGRRBBYWW";
	std::string g1 = "BYOBWWBYBOOYRRBGOGYBYGGWBRYRGRBYYGWRWRRROOWOWGGOWBYWGO";

	cube = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";
	cube = rotateCube(cube, {ROT::L, ROT::R, ROT::U, ROT::D2, ROT::D, ROT::F, ROT::B, ROT::L, ROT::D, ROT::R});

	//g1
	std::vector<ROT> sol = getShortestG1Moves(getEdgeMask(cube));
	std::cout << sol.size() << std::endl;
	cube = rotateCube(cube, sol);
	printCube(cube);

	//g2
	sol = getShortestG2Moves(getCornerMask(cube));
	cube = rotateCube(cube, sol);
	std::cout << sol.size() << std::endl;
	printCube(cube);

	//g3
	std::string phase3 = getOrbitMask(cube);
	sol = getShortestG3Moves(phase3);
	std::cout << sol.size() << std::endl;
	cube = rotateCube(cube, sol);
	printCube(cube);

	//std::vector<ROT> sol = iterativeDeepeningSearchCube()

	return 0;
}

//think about maybe doing OOP for the facelet cube
//also once CV stuff is started, reorgranize non- CV and CV things
//maybe add namespaces after doing cv stuff
//g2 -> g3, g3 -> solved
//rework to make the functions apart of a cube class after testing

//review and clean up code
//section of into folder(search up first)