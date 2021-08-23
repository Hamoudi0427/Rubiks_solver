#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>

/*
	In the second phase (G1 -> G2) the set of legal moves = <L, R, F2, B2, U, D> as F and B quarter turns affect edge orientation.
	To get to G2 we must seperate the edges and orient the corners
	A corner is oriented if the facelet matches to its solved face.
*/

//this function extracts the 'good' corner facelets and distinguishes U/D edges and E-slice edges
std::string getCornerMask(std::string g1_cube)
{
	//indicate the E- slice edges with Y indicating E-slice edges
	std::string target_mask = "XMXMXMXMXXXXXXXXXXXXXYXMYXXXMXMXMXMXXXXXXXXXXXXXYXYXXX";

	//corner facelets
	std::vector<std::vector<int>> corners = {{0, 36, 47}, {6, 18, 38}, {8, 9, 20}, {8, 11, 45}, {24, 27, 44}, {15, 26, 29}, 
	{17, 35, 51}, {33, 42, 53}};

	//extract corners by indicating their Up - Down colors (White and Yellow)
	for (auto corner : corners)
	{
		if (g1_cube[corner[0]] == 'W' || g1_cube[corner[0]] == 'Y')
		{
			target_mask[corner[0]] = 'C';
		}
		else if (g1_cube[corner[1]] == 'W' || g1_cube[corner[1]] == 'Y')
		{
			target_mask[corner[1]] = 'C';
		}
		else if (g1_cube[corner[2]] == 'W' || g1_cube[corner[2]] == 'Y')
		{
			target_mask[corner[2]] = 'C';
		}
	}

	return target_mask;
}

std::vector<ROTATION> getG2Moves(std::string g2_mask)
{
	std::string target_mask = "CMCMXMCMCXXXXXXXXXXXXYXMYXXCMCMXMCMCXXXXXXXXXXXXYXYXXX";

	//moves without FP, F, B, BP
	std::vector<ROTATION> moves = {U, UP, U2, D, DP, D2, F2, R, RP, R2, L, LP, L2, B2};

	//return the moves to get edges oriented
	return depthFirstSearchCube(target_mask, g2_mask, moves, 13);
}

std::vector<ROTATION> getShortestG2Moves(std::string g2_mask)
{
	std::string target_mask = "CMCMXMCMCXXXXXXXXXXXXYXMYXXCMCMXMCMCXXXXXXXXXXXXYXYXXX";

	//moves without FP, F, B, BP
	std::vector<ROTATION> moves = {U, UP, U2, D, DP, D2, F2, R, RP, R2, L, LP, L2, B2};

	//return shortest amount of moves to get the edges oriented
	return iterativeDeepeningSearchCube(target_mask, g2_mask, moves, 13);
}

//Note: 'C' = corner, 'M' = U/D edge, 'Y' = E-slice edges