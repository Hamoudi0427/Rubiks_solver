#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "pruning_table.h"

/*
	In this final phase we start from G3 -> solved cube. In this stage only half turns are allowed <U2, D2, F2, B2, L2, R2>.
	The corners and edges are oriented correctly, so all that is left to do is solve the cube.
*/

//return the moves needed to get solve the cube
std::vector<ROT> getSolvedMoves(std::string g3_cube)
{
	//available moves
	std::vector<ROT> moves = {ROT::U2, ROT::D2, ROT::F2, ROT::B2, ROT::L2, ROT::R2};

	//the target cube is the solved cube
	std::string target = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";

	//generate the pruning table
	std::map<std::string, int> table = generateSolvedTable(6);

	return depthFirstSearchCube(target, g3_cube, moves, 14, table, 6);
}

//return the optimal solution needed to solve the cube
std::vector<ROT> getShortestSolvedMoves(std::string g3_cube)
{
	//available moves
	std::vector<ROT> moves = {ROT::U2, ROT::D2, ROT::F2, ROT::B2, ROT::L2, ROT::R2};
	
	//the target cube is the solved cube
	std::string target = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";

	//generate the pruning table
	std::map<std::string, int> table = generateSolvedTable(6);

	return iterativeDeepeningSearchCube(target, g3_cube, moves, 14, table, 6);
}
