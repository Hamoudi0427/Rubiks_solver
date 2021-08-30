#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "pruning_table.h"

/*
	In the third phase (G2 -> G3) the set of legal moves is <U, D, F2, B2, L2, R2>.
	To get to G3 we must get into 1/96 corner orbits (to get even parity for G3) and
	solve the edges.
*/

//generates the 96 possible corner orbits to reach G3
std::vector<std::string> generateCornerOrbits(int depth)
{
	//only half turns are permissble in G3
	std::vector<ROT> moves = { ROT::U2, ROT::D2, ROT::F2, ROT::B2, ROT::L2, ROT::R2 };

	//map will have the cube state as the key and the depth from the solved state as the value
	std::map<std::string, int> states;

	//we start from the solved cube and generate moves from there (corners are marked by their face)
	std::string target = "UXUXXXUXURRRRXRRRRFFFFXFFFFDXDXXXDXDLRLRXRLRLBFBFXFBFB";
	std::vector<std::string> previous_frontier = {target};

	//generate states
	for (int i = 1; i <= depth; i++)
	{
		std::vector<std::string> frontier;
		for (auto previous_state : previous_frontier)
		{
			for (auto move : moves)
			{
				//add to map if not previously discovered
				std::string new_cube = rotateCube(previous_state, {move});
				if (states.find(new_cube) == states.end())
				{
					states[new_cube] = i;

					//add to frontier
					frontier.push_back(new_cube);
				}
			}
		}

		previous_frontier = frontier;
	}

	//store all 96 possible states
	std::vector<std::string> corner_orbits;
	for (auto state : states)
	{
		corner_orbits.push_back(state.first);
	}

	return corner_orbits;
}

//returns a cube masked with the corner orbit facelets
std::string getOrbitMask(std::string g2_cube)
{
	//corner facelets
	std::vector<std::vector<int>> corners = {{0, 36, 47}, {6, 18, 38}, {8, 9, 20}, {2, 11, 45}, {24, 27, 44}, {15, 26, 29},
		{17, 35, 51}, {33, 42, 53}};

	std::string mask = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	//first label all of the corner facelets by checking their color
	for (auto corner : corners)
	{
		for (auto facelet : corner)
		{
			switch (g2_cube[facelet])
			{
			case 'B':
				mask[facelet] = 'B';
				break;
			case 'G':
				mask[facelet] = 'F';
				break;
			case 'R':
				mask[facelet] = 'R';
				break;
			case 'W':
				mask[facelet] = 'U';
				break;
			case 'Y':
				mask[facelet] = 'D';
				break;
			case 'O':
				mask[facelet] = 'L';
				break;
			default:
				break;
			}
		}
	}

	//then label edges (F equal to B and L equal to R)
	std::vector<std::vector<int>> edges = {{7, 19}, {21, 41}, {23, 12}, {25, 28}, {37, 3}, {43, 30}, {10, 5}, {16, 32},
		{1, 46}, {14, 48}, {39, 50}, {52, 34}};

	for (auto edge : edges)
	{
		for (auto facelet : edge)
		{
			switch (g2_cube[facelet])
			{
			case 'B':
				mask[facelet] = 'F';
				break;
			case 'G':
				mask[facelet] = 'F';
				break;
			case 'R':
				mask[facelet] = 'R';
				break;
			case 'O':
				mask[facelet] = 'R';
				break;
			default:
				break;
			}
		}
	}

	return mask;
}

//return the moves needed to get to G3
std::vector<ROT> getG3Moves(std::string g3_mask)
{
	//available moves
	std::vector<ROT> moves = { ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F2, ROT::R2, ROT::L2, ROT::B2 };

	//generate the corner orbits
	std::vector<std::string> corner_orbits = generateCornerOrbits(PHASE_G3_ORBIT);

	//generate the pruning table
	std::unordered_map<std::string, int> table = generateG3Table(PHASE_G3_TABLE, corner_orbits);

	return depthFirstSearchCubes(corner_orbits, g3_mask, moves, PHASE_G3_DEPTH, table, PHASE_G3_TABLE);
}

//return the optimal solution needed to get to G3
std::vector<ROT> getShortestG3Moves(std::string g3_mask)
{
	//available moves
	std::vector<ROT> moves = { ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F2, ROT::R2, ROT::L2, ROT::B2 };

	//generate the corner orbits
	std::vector<std::string> corner_orbits = generateCornerOrbits(PHASE_G3_ORBIT); 

	//generate the pruning table
	std::unordered_map<std::string, int> table = generateG3Table(PHASE_G3_TABLE, corner_orbits);

	return iterativeDeepeningSearchCubes(corner_orbits, g3_mask, moves, PHASE_G3_DEPTH, table, PHASE_G3_TABLE);
}