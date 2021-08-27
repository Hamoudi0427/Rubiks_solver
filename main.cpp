#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "pruning_table.h"
#include <string>
#include <iostream>
#include <map>

int main(void)
{
	std::string cube = "YRGGWRBYOBWRORYOYBRBWOGYOBYYOGGYGOBRGOWROWGWBWGRRBBYWW";
	std::string g1 = "BYOBWWBYBOOYRRBGOGYBYGGWBRYRGRBYYGWRWRRROOWOWGGOWBYWGO";

	cube = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";
	cube = rotateCube(cube, {ROT::L, ROT::R, ROT::U, ROT::D2});

	//std::map<std::string, int> table2= generateG2Table(7);
	//std::cout << table2.size() << std::endl;

	std::vector<ROT> sol = getShortestG1Moves(getEdgeMask(cube));
	std::cout << sol.size() << std::endl;
	cube = rotateCube(cube, sol);
	printCube(cube);
	std::cout << std::endl;

	sol = getShortestG2Moves(getCornerMask(cube));
	cube = rotateCube(cube, sol);
	std::cout << sol.size() << std::endl;
	printCube(cube);

	return 0;
}

//think about maybe doing OOP for the facelet cube
//also once CV stuff is started, reorgranize non- CV and CV things
//maybe add namespaces after doing cv stuff
//g2 -> g3, g3 -> solved
//rework to make the functions apart of a cube class after testing


//enum classes
//remove print statements from prune table
//add flag for the lower bound update of the map
//review and clean up code
//section of into folder(search up first)