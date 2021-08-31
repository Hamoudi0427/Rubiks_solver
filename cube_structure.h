#ifndef CUBE_STRUCTURE_H
#define CUBE_STRUCTURE_H

#include "facelet_rotate.h"
#include <array>

enum class COLOR
{
	W, Y, G, B, R, O, X
};

enum class SIDE
{
	U, D, L, R, F, B
};

//class for one of the six faces that make up the cube in the cube class
class Face
{
public:
	//constructors
	Face(std::array<std::array<COLOR, 3>, 3> face_construct);
	Face(void);
	Face(const Face& face_copy);

	//assignment
	Face& operator=(const Face& copy);

	//color retrieval and entry
	COLOR getFaceletColor(int index) const;
	std::array<std::array<COLOR, 3>, 3> getFace(void) const;
	void setFaceletColor(int index, COLOR color);
	void setFace(std::array<std::array<COLOR, 3>, 3> face_construct);
	void printFace(void);
private:
	//geometric reresentation of a face
	std::array<std::array<COLOR, 3>, 3> face;
};

//geometric representation of the cube
class Cube
{
public:

private:
	std::array<Face, 6> cube;
	std::string facelet_cube;
};

#endif
