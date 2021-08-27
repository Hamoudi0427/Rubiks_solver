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
	cube = rotateCube(cube, { F, B, L, F , D, R2, D, U});

	std::vector<ROTATION> sol = getShortestG1Moves(getEdgeMask(cube));
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


//get prune table working with g1 and g2 and optimize
//g2 -> g3, g3 -> solved
//rework to make the functions apart of a cube class after testing
//get to about 10-30 seconds to generate solution
//opencv
//stream line once it all works 