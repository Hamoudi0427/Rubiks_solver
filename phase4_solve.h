#ifndef PHASE4_SOLVE_H
#define PHASE4_SOLVE_H

#include <vector>
#include <string>
#include "facelet_rotate.h"

std::vector<ROT> getSolvedMoves(std::string g3_cube);
std::vector<ROT> getShortestSolvedMoves(std::string g3_cube);

#endif
