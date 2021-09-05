#ifndef CUBE_FACE_H
#define CUBE_FACE_H

#include "opencv2/opencv.hpp"
#include "cube_structure.h"

std::vector<cv::Mat> faceletCrop(const cv::Mat& img);
void drawFacelets(cv::Mat& img_resize);
bool isFaceFound(const std::map<std::string, int>& face_count);
void addFaceToMap(std::map<std::string, int>& face_count, Face& face);
Face getCubeFace(const cv::Mat& img);
void prac2(cv::VideoCapture& webcam);

#endif