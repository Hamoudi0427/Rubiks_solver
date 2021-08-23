#ifndef PHASE1_SOLVE_H
#define PHASE1_SOLVE_H

#include <vector>
#include <string>
#include "facelet_rotate.h"

std::string getEdgeMask(std::string cube);
std::vector<ROTATION> getG1Moves(std::string mask);
std::vector<ROTATION> getShortestG1Moves(std::string mask);

#endif