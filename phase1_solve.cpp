#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "pruning_table.h"

/*
	In the first phase (Go -> G1) the set of legal moves = <L, R, F, B, U, D>.
	To get to G1 we must orient all the edge facelets correctly.
	An edge is said to be 'oriented' if it can be solved using only R, L, U and D turns.
*/

//this function extracts the 'good' facelets from the cube and returns only those facelets
std::string getEdgeMask(std::string cube)
{
	//vectors containing all edge piece coordinates
	std::vector<std::vector<int>> edges = {{1, 46}, {3, 37}, {5, 10}, {7, 19}, {28, 25}, {30, 43}, {32, 16}, {34, 52}, {21, 41}, {23, 12}, {50, 39}, 
	{14, 48}};

	std::string masked_cube = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

	//mark the good facelets
	for (auto edge : edges)
	{
		//check for first edge coordinate
		switch (cube[edge[0]])
		{
		case 'W':
			switch (cube[edge[1]])
			{
			case 'B':
				masked_cube[edge[0]] = 'M';
				break;
			case 'R':
				masked_cube[edge[0]] = 'M';
				break;
			case 'O':
				masked_cube[edge[0]] = 'M';
				break;
			case 'G':
				masked_cube[edge[0]] = 'M';
				break;
			default:
				break;
			}
		case 'Y':
			switch (cube[edge[1]])
			{
			case 'B':
				masked_cube[edge[0]] = 'M';
				break;
			case 'R':
				masked_cube[edge[0]] = 'M';
				break;
			case 'O':
				masked_cube[edge[0]] = 'M';
				break;
			case 'G':
				masked_cube[edge[0]] = 'M';
				break;
			default:
				break;
			}
		case 'G':
			switch (cube[edge[1]])
			{
			case 'O':
				masked_cube[edge[0]] = 'M';
				break;
			case 'R':
				masked_cube[edge[0]] = 'M';
				break;
			default:
				break;
			}
		case 'B':
			switch (cube[edge[1]])
			{
			case 'O':
				masked_cube[edge[0]] = 'M';
				break;
			case 'R':
				masked_cube[edge[0]] = 'M';
				break;
			default:
				break;
			}
		default:
			break;
		}

		//check second edge coordinate
		switch (cube[edge[1]])
		{
		case 'W':
			switch (cube[edge[0]])
			{
			case 'B':
				masked_cube[edge[1]] = 'M';
				break;
			case 'R':
				masked_cube[edge[1]] = 'M';
				break;
			case 'O':
				masked_cube[edge[1]] = 'M';
				break;
			case 'G':
				masked_cube[edge[1]] = 'M';
				break;
			default:
				break;
			}
		case 'Y':
			switch (cube[edge[0]])
			{
			case 'B':
				masked_cube[edge[1]] = 'M';
				break;
			case 'R':
				masked_cube[edge[1]] = 'M';
				break;
			case 'O':
				masked_cube[edge[1]] = 'M';
				break;
			case 'G':
				masked_cube[edge[1]] = 'M';
				break;
			default:
				break;
			}
		case 'G':
			switch (cube[edge[0]])
			{
			case 'O':
				masked_cube[edge[1]] = 'M';
				break;
			case 'R':
				masked_cube[edge[1]] = 'M';
				break;
			default:
				break;
			}
		case 'B':
			switch (cube[edge[0]])
			{
			case 'O':
				masked_cube[edge[1]] = 'M';
				break;
			case 'R':
				masked_cube[edge[1]] = 'M';
				break;
			default:
				break;
			}
		default:
			break;
		}
	}

	return masked_cube;
}

//this function generates the pruning table and then searches for the G1 moves (sub-optimally as it uses DFS)
std::vector<ROT> getG1Moves(std::string mask)
{
	std::string target_mask = "XMXMXMXMXXXXXXXXXXXXXMXMXXXXMXMXMXMXXXXXXXXXXXXXMXMXXX";
	std::vector<ROT> moves = {ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F, ROT::FP, ROT::F2, ROT::R, ROT::RP, 
		ROT::R2, ROT::L, ROT::LP, ROT::L2, ROT::B, ROT::BP, ROT::B2};

	//generate the pruning table
	std::map<std::string, int> table = generateG1Table(PHASE_G1_TABLE);

	//return the moves to get edges oriented
	return depthFirstSearchCube(target_mask, mask, moves, PHASE_G1_DEPTH, table, PHASE_G1_TABLE);
}

//returns the optimal moves to get to the next phase (uses IDDFS)
std::vector<ROT> getShortestG1Moves(std::string mask)
{
	std::string target_mask = "XMXMXMXMXXXXXXXXXXXXXMXMXXXXMXMXMXMXXXXXXXXXXXXXMXMXXX";
	std::vector<ROT> moves = {ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F, ROT::FP, ROT::F2, ROT::R, ROT::RP,
		ROT::R2, ROT::L, ROT::LP, ROT::L2, ROT::B, ROT::BP, ROT::B2};

	//generate the pruning table
	std::map<std::string, int> table = generateG1Table(PHASE_G1_TABLE);

	//return shortest amount of moves to get the edges oriented
	return iterativeDeepeningSearchCube(target_mask, mask, moves, PHASE_G1_DEPTH, table, PHASE_G1_TABLE);
}