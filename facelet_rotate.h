#ifndef FACELET_ROTATE_H
#define FACELET_ROTATE_H

#include <vector>
#include <string>
#include <map>

//cube rotations
enum ROTATION
{
    U, UP, U2, D, DP, D2, F, FP, F2, R, RP, R2, L, LP, L2, B, BP, B2
};

//rotation functions for facelet model
void printCube(const std::string& cube);
std::string rotateUpClockwise(const std::string& cube);
std::string rotateUpCounterClockwise(const std::string& cube);
std::string& rotateUpTwice(std::string& cube);
std::string rotateFrontClockwise(const std::string& cube);
std::string rotateFrontCounterClockwise(const std::string& cube);
std::string& rotateFrontTwice(std::string& cube);
std::string rotateLeftClockwise(const std::string& cube);
std::string rotateLeftCounterClockwise(const std::string& cube);
std::string& rotateLeftTwice(std::string& cube);
std::string rotateRightClockwise(const std::string& cube);
std::string rotateRightCounterClockwise(const std::string& cube);
std::string& rotateRightTwice(std::string& cube);
std::string rotateBackClockwise(const std::string& cube);
std::string rotateBackCounterClockwise(const std::string& cube);
std::string& rotateBackTwice(std::string& cube);
std::string rotateDownClockwise(const std::string& cube);
std::string rotateDownCounterClockwise(const std::string& cube);
std::string& rotateDownTwice(std::string& cube);
std::string rotateCube(std::string cube, std::vector<ROTATION> moves);
std::vector<ROTATION> depthFirstSearchCube(std::string target, std::string cube, std::vector<ROTATION> moves, int depth,
    std::map<std::string, int>& table, std::vector<ROTATION> solution = {});
std::vector<ROTATION> iterativeDeepeningSearchCube(std::string target, std::string cube, std::vector<ROTATION> moves, int depth,
    std::map<std::string, int>& table);

#endif
