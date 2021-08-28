#ifndef PRUNING_TABLE_H
#define PRUNING_TABLE_H

#include <map>
#include <string>
#include <string>
#include "facelet_rotate.h"

std::map<std::string, int> generateG1Table(int depth);
std::map<std::string, int> generateG2Table(int depth);
std::map<std::string, int> generateG3Table(int depth, std::vector<std::string> g2_corner_orbits);
std::map<std::string, int> generateSolvedTable(int depth);

#endif