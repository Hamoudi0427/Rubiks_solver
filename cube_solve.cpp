#include "cube_structure.h"
#include "facelet_rotate.h"
#include "phase1_solve.h"
#include "phase2_solve.h"
#include "phase3_solve.h"
#include "phase4_solve.h"

/*
	Cube solver that solves cube once the cube is initialized from the webcam.
	Average runtime is about 45 seconds.
*/

void Cube::solveCube(void)
{
	std::string temp_cube = facelet_cube; 
	
	//G0 -> G1
	std::vector<ROT> sol = getShortestG1Moves(getEdgeMask(temp_cube));
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//G1 -> G2
	sol = getShortestG2Moves(getCornerMask(temp_cube));
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//G2 -> G3
	sol = getShortestG3Moves(getOrbitMask(temp_cube));
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);

	//G3 -> Solved
	sol = getShortestSolvedMoves(temp_cube);
	std::cout << sol.size() << std::endl;
	for (auto move : sol)
	{
		solution.push_back(move);
	}
	temp_cube = rotateCube(temp_cube, sol); 
	printCube(temp_cube);
	
	std::cout << this -> solution;
}