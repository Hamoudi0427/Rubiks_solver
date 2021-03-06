#include "facelet_rotate.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

/*
	This file contains functions that generate the pruning tables to speed up the move solvers. These tables
	significantly reduce wait times.
*/

//generates states with their coresponding depth to allow for pruning when finding G1 moves
std::map<std::string, int> generateG1Table(int depth)
{
	//use all available moves
	std::vector<ROT> moves = { ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F, ROT::FP, ROT::F2, ROT::R, ROT::RP,
		ROT::R2, ROT::L, ROT::LP, ROT::L2, ROT::B, ROT::BP, ROT::B2 };

	//map will have the cube state as the key and the depth from the solved state as the value
	std::map<std::string, int> states;

	//we start from the target state and generate moves from there
	std::string target = "XMXMXMXMXXXXXXXXXXXXXMXMXXXXMXMXMXMXXXXXXXXXXXXXMXMXXX";
	std::vector<std::string> previous_frontier = { target };

	//generate states
	for (int i = 1; i <= depth; i++)
	{
		std::vector<std::string> frontier;
		for (auto previous_state : previous_frontier)
		{
			for (auto move : moves)
			{
				//add to map if not previously discovered
				std::string new_cube = rotateCube(previous_state, { move });
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

	return states;
}

//generates states with their coresponding depth to allow for pruning when finding G2 moves
std::map<std::string, int> generateG2Table(int depth)
{
	//use all available moves
	std::vector<ROT> moves = { ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F2, ROT::R, ROT::RP, ROT::R2, ROT::L,
		ROT::LP, ROT::L2, ROT::B2 };

	//map will have the cube state as the key and the depth from the solved state as the value
	std::map<std::string, int> states;

	//we start from the target state and generate moves from there
	std::string target = "MMMMXMMMMXXXXXXXXXXXXYXYXXXMMMMXMMMMXXXXXXXXXXXXYXYXXX";
	std::vector<std::string> previous_frontier = { target };

	//generate states
	for (int i = 1; i <= depth; i++)
	{
		std::vector<std::string> frontier;
		for (auto previous_state : previous_frontier)
		{
			for (auto move : moves)
			{
				//add to map if not previously discovered
				std::string new_cube = rotateCube(previous_state, { move });
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

	return states;
}

//pruning table for G2 -> G3, takes in all 96 corner orbits to apply rotations to
std::unordered_map<std::string, int> generateG3Table(int depth, std::vector<std::string> g2_corner_orbits)
{
	//use all moves except F, B, L, R quarter turns
	std::vector<ROT> moves = {ROT::U, ROT::UP, ROT::U2, ROT::D, ROT::DP, ROT::D2, ROT::F2, ROT::R2, ROT::L2, ROT::B2};

	//map will have the cube state as the key and the depth from the solved state as the value
	std::unordered_map<std::string, int> states;
	for (auto corner : g2_corner_orbits)
	{
		states[corner] = -1;
	}

	//we start from one of 96 permissible states in G3
	std::vector<std::string> previous_frontier = g2_corner_orbits;

	//generate states
	for (int i = 1; i <= depth; i++)
	{
		std::vector<std::string> frontier;
		for (auto previous_state : previous_frontier)
		{	
			for (auto move : moves)
			{
				//add to map if not previously discovered
				std::string new_cube = rotateCube(previous_state, { move });
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

	return states;
}

//generates pruning table from the fully solved state
std::map<std::string, int> generateSolvedTable(int depth)
{
	//only half turns are permissible
	std::vector<ROT> moves = {ROT::U2, ROT::D2, ROT::F2, ROT::B2, ROT::L2, ROT::R2};

	//map will have the cube state as the key and the depth from the solved state as the value
	std::map<std::string, int> states;

	//we start from the solved cube and generate moves from there
	std::string target = "WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB";
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
				std::string new_cube = rotateCube(previous_state, { move });
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

	return states;
}