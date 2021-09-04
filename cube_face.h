#ifndef CUBE_FACE_H
#define CUBE_FACE_H

#include "opencv2/opencv.hpp"
#include "cube_structure.h"

std::vector<cv::Mat> faceletCrop(const cv::Mat& img);
Face getCubeFace(const cv::Mat& img);

#endif