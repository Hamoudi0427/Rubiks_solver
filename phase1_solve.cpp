#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>

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

std::vector<ROTATION> getG1Moves(std::string mask)
{
	std::string target_mask = "XMXMXMXMXXXXXXXXXXXXXMXMXXXXMXMXMXMXXXXXXXXXXXXXMXMXXX";
	std::vector<ROTATION> moves = {U, UP, U2, D, DP, D2, F, FP, F2, R, RP, R2, L, LP, L2, B, BP, B2};

	//return the moves to get edges oriented
	return depthFirstSearchCube(target_mask, mask, moves, 7);
}

std::vector<ROTATION> getShortestG1Moves(std::string mask)
{
	std::string target_mask = "XMXMXMXMXXXXXXXXXXXXXMXMXXXXMXMXMXMXXXXXXXXXXXXXMXMXXX";
	std::vector<ROTATION> moves = { U, UP, U2, D, DP, D2, F, FP, F2, R, RP, R2, L, LP, L2, B, BP, B2 };

	//return shortest amount of moves to get the edges oriented
	return iterativeDeepeningSearchCube(target_mask, mask, moves, 7);
}
