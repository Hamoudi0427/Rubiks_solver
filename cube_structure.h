#ifndef CUBE_STRUCTURE_H
#define CUBE_STRUCTURE_H

#include "facelet_rotate.h"
#include <array>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

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

	//assignment and equality
	Face& operator=(const Face& copy);

	//color retrieval and entry
	COLOR getFaceletColor(int index) const;
	COLOR operator[](int index);
	std::array<std::array<COLOR, 3>, 3> getFace(void) const;
	std::string getFaceString(void) const;
	void setFaceletColor(int index, COLOR color);
	void setFace(std::array<std::array<COLOR, 3>, 3> face_construct);
	void printFace(void);

private:
	//geometric reresentation of a face
	std::array<std::array<COLOR, 3>, 3> face;
};

//face equality operators
bool operator==(const Face& face1, const Face& face2);
bool operator!=(const Face& face1, const Face& face2);


//geometric representation of the cube
class Cube
{
public:
	//constructors
	Cube(void);
	Cube(std::array<Face, 6> faces);

	//accessor methods
	std::string convertToString(void);
	Face getFace(SIDE side);
	int getSolutionSize(void) {return solution.size();}

	//solving and getting the cube
	void initializeCube(cv::VideoCapture& webcam);
	void solveCube(void);
	void applyMoves(cv::VideoCapture& webcam);

private:
	//cube implementation
	std::array<Face, 6> cube;
	std::string facelet_cube;
	std::vector<ROT> solution;

	//solving and getting the cube
	std::vector<cv::Mat> faceletCrop(const cv::Mat& img);
	void drawFacelets(cv::Mat& img_resize, cv::Scalar color);
	void drawArrows(cv::Mat& img_resize, ROT move);
	bool isFaceFound(const std::map<std::string, int>& face_count);
	void addFaceToMap(std::map<std::string, int>& face_count, Face& face);
	Face getCubeFace(const cv::Mat& img);
	Face getValidCubeFace(cv::VideoCapture& webcam, COLOR side, std::string message);
	void stringToCube(void);
};

#endif
