#include <iostream>
#include <vector>
#include <string>
#include <array>

/*
    This file contains the rotation functions for a Rubik's cube defined as a 
    permutation of 54 facelets stored in a string.
*/

//possible rotations
enum ROTATION
{
    U, UP, U2, D, DP, D2, F, FP, F2, R, RP, R2, L, LP, L2, B, BP, B2
};

//printing function to help with testing
void printCube(const std::string& cube)
{
    //upper layer
    for (int i = 0; i < 3; i++)
    {
        std::cout << " " << " " << " " << " " << " ";
        std::cout << cube[0 + 3 * i] << cube[1 + 3 * i] << cube[2 + 3 * i];
        std::cout << " " << " " << " " << " " << " ";
        std::cout << " " << " " << " " << " " << " ";
        std::cout << std::endl;
    }

    //middle layers
    for (int i = 0; i < 3; i++)
    {
        std::cout << cube[36 + 3 * i] << cube[37 + 3 * i] << cube[38 + 3 * i];
        std::cout << cube[18 + 3 * i] << cube[19 + 3 * i] << cube[20 + 3 * i];
        std::cout << cube[9 + 3 * i] << cube[10 + 3 * i] << cube[11 + 3 * i];
        std::cout << cube[45 + 3 * i] << cube[46 + 3 * i] << cube[47 + 3 * i];
        std::cout << std::endl;
    }

    //down layer
    for (int i = 0; i < 3; i++)
    {
        std::cout << " " << " " << " " << " " << " ";
        std::cout << cube[27 + 3 * i] << cube[28 + 3 * i] << cube[29 + 3 * i];
        std::cout << " " << " " << " " << " " << " ";
        std::cout << " " << " " << " " << " " << " ";
        std::cout << std::endl;
    }
}

//given the cube string rotate the upper face clockwise
std::string rotateUpClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{0, 2}, {1, 5}, {2, 8}, {3, 1}, {5, 7}, {6, 0}, {7, 3}, {8, 6}, {18, 36}, {19, 37}, {20, 38}, {9, 18}, {10, 19}, {11, 20},
    {45, 9}, {46, 10}, {47, 11}, {36, 45}, {37, 46}, {38, 47}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string rotate the upper face counter clockwise
std::string rotateUpCounterClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{2, 0}, {5, 1}, {8, 2}, {1, 3}, {7, 5}, {0, 6}, {3, 7}, {6, 8}, {36, 18}, {37, 19}, {38, 20}, {18, 9}, {19, 10}, {20, 11},
    {9, 45}, {10, 46}, {11, 47}, {45, 36}, {46, 37}, {47, 38}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string apply a double rotation to the upper face
std::string& rotateUpTwice(std::string& cube)
{
    //perform a clockwise rotation twice
    cube = rotateUpClockwise(cube);
    cube = rotateUpClockwise(cube);

    return cube;
}

//given the cube string rotate the front face clockwise
std::string rotateFrontClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{18, 20}, {19, 23}, {20, 26}, {21, 19}, {23, 25}, {24, 18}, {25, 21}, {26, 24}, {6, 9}, {7, 12}, {8, 15}, {9, 29},
    {12, 28}, {15, 27}, {27, 38}, {28, 41}, {29, 44}, {38, 8}, {41, 7}, {44, 6}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string rotate the front face counter clockwise
std::string rotateFrontCounterClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{20, 18}, {23, 19}, {26, 20}, {19, 21}, {25, 23}, {18, 24}, {21, 25}, {24, 26}, {9, 6}, {12, 7}, {15, 8}, {29, 9},
    {28, 12}, {27, 15}, {38, 27}, {41, 28}, {44, 29}, {8, 38}, {7, 41}, {6, 44}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string apply a double rotation to the front face
std::string& rotateFrontTwice(std::string& cube)
{
    //perform a clockwise rotation twice
    cube = rotateFrontClockwise(cube);
    cube = rotateFrontClockwise(cube);

    return cube;
}

//given the cube string rotate the left face clockwise
std::string rotateLeftClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{36, 38}, {37, 41}, {38, 44}, {39, 37}, {41, 43}, {42, 36}, {43, 39}, {44, 42}, {0, 18}, {3, 21}, {6, 24}, {18, 27},
    {21, 30}, {24, 33}, {27, 53}, {30, 50}, {33, 47}, {47, 6}, {50, 3}, {53, 0}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string rotate the left face counter clockwise
std::string rotateLeftCounterClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{38, 36}, {41, 37}, {44, 38}, {37, 39}, {43, 41}, {36, 42}, {39, 43}, {42, 44}, {18, 0}, {21, 3}, {24, 6}, {27, 18},
    {30, 21}, {33, 24}, {53, 27}, {50, 30}, {47, 33}, {6, 47}, {3, 50}, {0, 53}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string apply a double rotation to the left face
std::string& rotateLeftTwice(std::string& cube)
{
    //perform a clockwise rotation twice
    cube = rotateLeftClockwise(cube);
    cube = rotateLeftClockwise(cube);

    return cube;
}

//given the cube string rotate the right face clockwise
std::string rotateRightClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{9, 11}, {10, 14}, {11, 17}, {12, 10}, {14, 16}, {15, 9}, {16, 12}, {17, 15}, {20, 2}, {23, 5}, {26, 8}, {2, 51},
    {5, 48}, {8, 45}, {45, 35}, {48, 32}, {51, 29}, {29, 20}, {32, 23}, {35, 26}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string rotate the right face counter clockwise
std::string rotateRightCounterClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{11, 9}, {14, 10}, {17, 11}, {10, 12}, {16, 14}, {9, 15}, {12, 16}, {15, 17}, {2, 20}, {5, 23}, {8, 26}, {51, 2},
    {48, 5}, {45, 8}, {35, 45}, {32, 48}, {29, 51}, {20, 29}, {23, 32}, {26, 35}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string apply a double rotation to the right face
std::string& rotateRightTwice(std::string& cube)
{
    //perform a clockwise rotation twice
    cube = rotateRightClockwise(cube);
    cube = rotateRightClockwise(cube);

    return cube;
}

//given the cube string rotate the back face clockwise
std::string rotateBackClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{45, 47}, {46, 50}, {47, 53}, {48, 46}, {50, 52}, {51, 45}, {52, 48}, {53, 51}, {11, 0}, {14, 1}, {17, 2}, {0, 42},
    {1, 39}, {2, 36}, {36, 33}, {39, 34}, {42, 35}, {33, 17}, {34, 14}, {35, 11}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string rotate the back face counter clockwise
std::string rotateBackCounterClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{47, 45}, {50, 46}, {53, 47}, {46, 48}, {52, 50}, {45, 51}, {48, 52}, {51, 53}, {0, 11}, {1, 14}, {2, 17}, {42, 0},
    {39, 1}, {36, 2}, {33, 36}, {34, 39}, {35, 42}, {17, 33}, {14, 34}, {11, 35}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string apply a double rotation to the back face
std::string& rotateBackTwice(std::string& cube)
{
    //perform a clockwise rotation twice
    cube = rotateBackClockwise(cube);
    cube = rotateBackClockwise(cube);

    return cube;
}

//given the cube string rotate the down face clockwise
std::string rotateDownClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{27, 29}, {28, 32}, {29, 35}, {30, 28}, {32, 34}, {33, 27}, {34, 30}, {35, 33}, {24, 15}, {25, 16}, {26, 17}, {15, 51},
    {16, 52}, {17, 53}, {51, 42}, {52, 43}, {53, 44}, {42, 24}, {43, 25}, {44, 26}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string rotate the down face counter clockwise
std::string rotateDownCounterClockwise(const std::string& cube)
{
    //define the rotation as a set of permutations
    std::array<std::array<int, 2>, 20> src_dst{{{29, 27}, {32, 28}, {35, 29}, {28, 30}, {34, 32}, {27, 33}, {30, 34}, {33, 35}, {15, 24}, {16, 25}, {17, 26}, {51, 15},
    {52, 16}, {53, 17}, {42, 51}, {43, 52}, {44, 53}, {24, 42}, {25, 43}, {26, 44}}};

    //apply the rotation
    std::string new_cube = cube;
    for (std::array<int, 2> perm : src_dst)
    {
        new_cube[perm[1]] = cube[perm[0]];
    }

    return new_cube;
}

//given the cube string apply a double rotation to the down face
std::string& rotateDownTwice(std::string& cube)
{
    //perform a clockwise rotation twice
    cube = rotateDownClockwise(cube);
    cube = rotateDownClockwise(cube);

    return cube;
}

//applies a series of rotations to the cube
std::string rotateCube(std::string cube, std::vector<ROTATION> moves)
{
    for (auto move : moves)
    {
        switch (move)
        {
        case U:
            cube = rotateUpClockwise(cube);
            break;
        case UP:
            cube = rotateUpCounterClockwise(cube);
            break;
        case U2:
            cube = rotateUpTwice(cube);
            break;
        case D:
            cube = rotateDownClockwise(cube);
            break;
        case DP:
            cube = rotateDownCounterClockwise(cube);
            break;
        case D2:
            cube = rotateDownTwice(cube);
            break;
        case L:
            cube = rotateLeftClockwise(cube);
            break;
        case LP:
            cube = rotateLeftCounterClockwise(cube);
            break;
        case L2:
            cube = rotateLeftTwice(cube);
            break;
        case R:
            cube = rotateRightClockwise(cube);
            break;
        case RP:
            cube = rotateRightCounterClockwise(cube);
            break;
        case R2:
            cube = rotateRightTwice(cube);
            break;
        case B:
            cube = rotateBackClockwise(cube);
            break;
        case BP:
            cube = rotateBackCounterClockwise(cube);
            break;
        case B2:
            cube = rotateBackTwice(cube);
            break;
        case F:
            cube = rotateFrontClockwise(cube);
            break;
        case FP:
            cube = rotateFrontCounterClockwise(cube);
            break;
        case F2:
            cube = rotateFrontTwice(cube);
            break;
        default:
            break;
        }
    }

    return cube;
}

//depth first search (DFS) to find possible solution at a given depth
std::vector<ROTATION> depthFirstSearchCube(std::string target, std::string cube, std::vector<ROTATION> moves, int depth, std::vector<ROTATION> solution = {})
{
    //solution found return array of moves to get to target cube
    if (cube == target)
    {
        return solution;
    }

    //no solution found if maximum depth is used
    if (depth == 0)
    {
        return {};
    }

    for (auto move : moves)
    {
        //update the solution vector with the move and continue searching
        std::vector<ROTATION> new_solution = solution;
        new_solution.push_back(move);

        //reduce remaining depth and apply the move to the cube
        std::vector<ROTATION> result = depthFirstSearchCube(target, rotateCube(cube, {move}), moves, depth - 1, new_solution);

        //return the solution vector if found
        if (result.size() != 0)
        {
            return result;
        }
    }

    //empty vector returned if no solution is found
    return {};
}

//iterative deepening DFS function provides the optimal solution while using less space than BFS
std::vector<ROTATION> iterativeDeepeningSearchCube(std::string target, std::string cube, std::vector<ROTATION> moves, int depth)
{
    //continues searching deeper until a solution is found, garentees optimal solution if one exists
    for (int i = 0; i < depth; i++)
    {
        std::vector<ROTATION> solution = depthFirstSearchCube(target, cube, moves, i);

        //return first solution found
        if (solution.size() != 0)
        {
            return solution;
        }
    }

    //return empty vector if no solution is found
    return {};
}