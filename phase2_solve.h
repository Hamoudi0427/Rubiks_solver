#ifndef PHASE2_SOLVE_H
#define PHASE2_SOLVE_H

#include <vector>
#include <string>
#include "facelet_rotate.h"

std::string getCornerMask(std::string g1_cube);
std::vector<ROT> getG2Moves(std::string g2_mask);
std::vector<ROT> getShortestG2Moves(std::string g2_mask);

#endif