#ifndef PHASE2_SOLVE_H
#define PHASE2_SOLVE_H

#include <vector>
#include <string>
#include "facelet_rotate.h"

std::string getCornerMask(std::string g1_cube);
std::vector<ROTATION> getG2Moves(std::string g2_mask);
std::vector<ROTATION> getShortestG2Moves(std::string g2_mask);

#endif