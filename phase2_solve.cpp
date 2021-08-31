#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>
#include "pruning_table.h"

/*
	In the second phase (G1 -> G2) the set of legal moves = <L, R, F2, B2, U, D> as F and B quarter turns affect edge orientation.
	To get to G2 we must seperate the edges and orient the corners
	A corner is oriented if the facelet matches to its solved face.
*/

//this function extracts the 'good' corner facelets and distinguishes U/D edges and E-slice edges
std::string getCornerMask(std::string g1_cube)
{
	std::string target_mask = "XMXMXMXMXXXXXXXXXXXXXMXMXXXXMXMXMXMXXXXXXXXXXXXXMXMXXX";

	//indicate the E- slice edges with Y indicating E-slice edges
	std::vector<int> facelet_location = { 1, 3, 5, 7, 21, 23, 48, 50, 28, 30, 32, 34 };
	for (auto facelet : facelet_location)
	{
		if (g1_cube[facelet] == 'G' || g1_cube[facelet] == 'B')
		{
			target_mask[facelet] = 'Y';
		}
	}

	//corner facelets
	std::vector<std::vector<int>> corners = { {0, 36, 47}, {6, 18, 38}, {8, 9, 20}, {2, 11, 45}, {24, 27, 44}, {15, 26, 29},
		{17, 35, 51}, {33, 42, 53} };

	//extract corners by indicating their Up - Down colors (White and Yellow)
	for (auto corner : corners)
	{
		if (g1_cube[corner[0]] == 'W' || g1_cube[corner[0]] == 'Y')
		{
			target_mask[corner[0]] = 'M';
		}
		else if (g1_cube[corner[1]] == 'W' || g1_cube[corner[1]] == 'Y')
		{
			target_mask[corner[1]] = 'M';
		}
		else if (g1_cube[corner[2]] == 'W' || g1_cube[corner[2]] == 'Y')
		{
			target_mask[corner[2]] = 'M';
		}
	}

	return target_mask;
}

std::vector<ROT> getG2Moves(std::string g2_mask)
{
	std::string target_mask = "MMMMXMMMMXXXXXXXXXXXXYXYXXXMMMMXMMMMXXXXXXXXXXXXYXYXXX";

	//moves without FP, F, B, BP
	std::vector<ROT> moves = { ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F2, ROT::R, ROT::RP, ROT::R2, ROT::L,
		ROT::LP, ROT::L2, ROT::B2 };

	//generate the pruning table
	std::map<std::string, int> table = generateG2Table(PHASE_G2_TABLE);

	//return the moves to get edges oriented
	return depthFirstSearchCube(target_mask, g2_mask, moves, PHASE_G2_DEPTH, table, PHASE_G2_TABLE);
}

std::vector<ROT> getShortestG2Moves(std::string g2_mask)
{
	std::string target_mask = "MMMMXMMMMXXXXXXXXXXXXYXYXXXMMMMXMMMMXXXXXXXXXXXXYXYXXX";

	//moves without FP, F, B, BP
	std::vector<ROT> moves = { ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F2, ROT::R, ROT::RP, ROT::R2, ROT::L,
		ROT::LP, ROT::L2, ROT::B2 };

	//generate the pruning table
	std::map<std::string, int> table = generateG2Table(PHASE_G2_TABLE); 

	//return shortest amount of moves to get the edges oriented
	return iterativeDeepeningSearchCube(target_mask, g2_mask, moves, PHASE_G2_DEPTH, table, PHASE_G2_TABLE);
}

//Note: 'C' = corner, 'M' = U/D edge, 'Y' = E-slice edges