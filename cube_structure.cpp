#include <array>
#include <iostream>
#include "facelet_rotate.h"
#include "cube_structure.h"

/* Face class definitions */

//construct when initialized with the colors
Face::Face(std::array<std::array<COLOR, 3>, 3> face_construct)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			(this -> face)[row][col] = face_construct[row][col];
		}
	}
}

//construct face with default cube color X
Face::Face(void) : face{{{COLOR::X, COLOR::X, COLOR::X}, {COLOR::X, COLOR::X, COLOR::X}, {COLOR::X, COLOR::X, COLOR::X}}}
{}

//copy constructor
Face::Face(const Face& face_copy)
{
	//get the face array
	std::array<std::array<COLOR, 3>, 3> copy = face_copy.getFace();

	//copy over to the new face
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			(this -> face)[row][col] = copy[row][col];
		}
	}
}

//copy assignment
Face& Face::operator=(const Face& face_copy)
{
	//get the face array
	std::array<std::array<COLOR, 3>, 3> copy = face_copy.getFace();

	//assign to the current face
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			(this->face)[row][col] = copy[row][col];
		}
	}

	//returns a self- reference
	return *this;
}

//returns the color of the individual facelet (index is zero-indexed)
COLOR Face::getFaceletColor(int index) const
{
	return (this -> face)[index / 3][index % 3];
}

//returns the entire face
std::array<std::array<COLOR, 3>, 3> Face::getFace(void) const
{
	return this -> face;
}

//set individual facelet to a color
void Face::setFaceletColor(int index, COLOR color)
{
	(this -> face)[index / 3][index % 3] = color;
}

//resets the face based on the given colors
void Face::setFace(std::array<std::array<COLOR, 3>, 3> face_construct)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			(this -> face)[row][col] = face_construct[row][col];
		}
	}
}

//prints the face with the facelet colors
void Face::printFace(void)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			switch ((this->face)[row][col])
			{
			case COLOR::W:
				std::cout << 'W' << ' ';
				break;
			case COLOR::Y:
				std::cout << 'Y' << ' ';
				break;
			case COLOR::B:
				std::cout << 'B' << ' ';
				break;
			case COLOR::G:
				std::cout << 'G' << ' ';
				break;
			case COLOR::R:
				std::cout << 'R' << ' ';
				break;
			case COLOR::O:
				std::cout << 'O' << ' ';
				break;
			default:
				std::cout << 'X' << ' ';
				break;
			}
		}

		std::cout << std::endl;
	}
}

/* Cube class definitions */