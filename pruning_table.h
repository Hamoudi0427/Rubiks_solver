#ifndef PRUNING_TABLE_H
#define PRUNING_TABLE_H

#include <map>
#include <string>
#include "facelet_rotate.h"

std::map<std::string, int> generateG1Table(int depth);
std::map<std::string, int> generateG2Table(int depth);

#endif