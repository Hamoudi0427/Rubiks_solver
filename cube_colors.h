#ifndef CUBE_COLORS_H
#define CUBE_COLORS_H

#include "opencv2/opencv.hpp"
#include "cube_structure.h"

bool isGreen(const cv::Mat& cropped_img);
bool isBlue(const cv::Mat& cropped_img);
bool isRed(const cv::Mat& cropped_img);
bool isOrange(const cv::Mat& cropped_img);
bool isYellow(const cv::Mat& cropped_img);
COLOR getColor(const cv::Mat& cropped_img);

#endif
