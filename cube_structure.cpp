#include <array>
#include <iostream>
#include <string>
#include "facelet_rotate.h"
#include "cube_structure.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

/*
	 Contains the implementaion of the Cube and Face class.
*/

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

//index overloading to get the facelet
COLOR Face::operator[](int index)
{
	return getFaceletColor(index);
}

//returns the entire face
std::array<std::array<COLOR, 3>, 3> Face::getFace(void) const
{
	return this -> face;
}

//returns face as a string
std::string Face::getFaceString(void) const
{
	std::string face_string;

	//convert face to string
	for (auto row : this->face)
	{
		for (auto facelet : row)
		{
			switch (facelet)
			{
			case COLOR::W:
				face_string += 'W';
				break;
			case COLOR::Y:
				face_string += 'Y';
				break;
			case COLOR::B:
				face_string += 'B';
				break;
			case COLOR::G:
				face_string += 'G';
				break;
			case COLOR::R:
				face_string += 'R';
				break;
			case COLOR::O:
				face_string += 'O';
				break;
			default:
				break;
			}
		}
	}

	return face_string;
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

//default constructor
Cube::Cube(void) : facelet_cube{"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"}
{}

//constructor when given the face (assumed to be given in the proper order <U, R, F, D, L, B>)
Cube::Cube(std::array<Face, 6> faces)
{
	//update the cube (array of faces)
	for (int i = 0; i < 6; i++)
	{
		cube[i] = faces[i];
	}

	//update the string equivalent of the cube
	facelet_cube = this -> convertToString();
}

//convert geometric cube to facelet cube
std::string Cube::convertToString(void)
{
	std::string temp_facelet_cube = "";

	for (auto& face : cube)
	{
		for (int i = 0; i < 9; i++)
		{
			COLOR temp = face.getFaceletColor(i);

			switch (temp)
			{
			case COLOR::W:
				temp_facelet_cube += 'W';
				break;
			case COLOR::R:
				temp_facelet_cube += 'R';
				break;
			case COLOR::B:
				temp_facelet_cube += 'B';
				break;
			case COLOR::G:
				temp_facelet_cube += 'G';
				break;
			case COLOR::Y:
				temp_facelet_cube += 'Y';
				break;
			case COLOR::O:
				temp_facelet_cube += 'O';
				break;
			}
		}
	}

	return temp_facelet_cube;
}

//returns the face corresponding to the side
Face Cube::getFace(SIDE side)
{
	switch (side)
	{
	case SIDE::U:
		return cube[0];
	case SIDE::D:
		return cube[3];
	case SIDE::R:
		return cube[1];
	case SIDE::F:
		return cube[2];
	case SIDE::L:
		return cube[4];
	case SIDE::B:
		return cube[5];
	}
}