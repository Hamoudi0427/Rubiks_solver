#ifndef PHASE3_SOLVE_H
#define PHASE3_SOLVE_H

#include <vector>
#include <string>
#include "facelet_rotate.h"

std::vector<std::string> generateCornerOrbits(int depth);
std::string getOrbitMask(std::string g2_cube);
std::vector<ROT> getG3Moves(std::string g3_mask);
std::vector<ROT> getShortestG3Moves(std::string g3_mask);

#endif
