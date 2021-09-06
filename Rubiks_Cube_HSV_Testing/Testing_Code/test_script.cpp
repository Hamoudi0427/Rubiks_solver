#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

/*
	Testing Script:
	-outputs webcam masked image and different light conditions of the cube
	-has HSV trackbars for each channel to test for color values
*/

int main(void)
{
	//set the minimum and maximum values for the HSV color scale
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 180, smax = 255, vmax = 255;

	//read in four test images
	std::string dark_path = "HSV_Test_Images/Dark_Lit_Cube.jpg";
	std::string regular_path = "HSV_Test_Images/Regular_Lit_Cube.jpg";
	std::string bright_path = "HSV_Test_Images/Bright_Lit_Cube.jpg";
	std::string very_bright_path = "HSV_Test_Images/Very_Bright_Lit_Cube.jpg";
	cv::Mat dark = cv::imread(dark_path);
	cv::Mat regular = cv::imread(regular_path);
	cv::Mat bright = cv::imread(bright_path);
	cv::Mat very_bright = cv::imread(very_bright_path);

	//image resizing to fit windows
	cv::resize(dark, dark, cv::Size(600, 400), cv::INTER_LINEAR);
	cv::resize(regular, regular, cv::Size(600, 400), cv::INTER_LINEAR);
	cv::resize(bright, bright, cv::Size(600, 400), cv::INTER_LINEAR);
	cv::resize(very_bright, very_bright, cv::Size(600, 400), cv::INTER_LINEAR);


	//Trackbar Set-up
	cv::namedWindow("HSV Trackbar", (640, 200));
	cv::createTrackbar("Hue Min", "HSV Trackbar", &hmin, 179);
	cv::createTrackbar("Hue Max", "HSV Trackbar", &hmax, 180);
	cv::createTrackbar("Saturation Min", "HSV Trackbar", &smin, 254);
	cv::createTrackbar("Saturation Max", "HSV Trackbar", &smax, 255);
	cv::createTrackbar("Value Min", "HSV Trackbar", &vmin, 254);
	cv::createTrackbar("Value Max", "HSV Trackbar", &vmax, 255);

	//convert each image to HSV color space
	cv::Mat dark_hsv, regular_hsv, bright_hsv, very_bright_hsv;
	cv::cvtColor(dark, dark_hsv, cv::COLOR_BGR2HSV);
	cv::cvtColor(regular, regular_hsv, cv::COLOR_BGR2HSV);
	cv::cvtColor(bright, bright_hsv, cv::COLOR_BGR2HSV);
	cv::cvtColor(very_bright, very_bright_hsv, cv::COLOR_BGR2HSV);

	//Webcam set-up for testing data
	cv::VideoCapture webcam(0);

	while (webcam.isOpened())
	{
		//read and display images from webcam
		cv::Mat frame, frame_hsv, frame_mask;
		int success = webcam.read(frame);
		if (!success)
		{
			std::cout << "Could not open webcam or stream ended." << std::endl;
		}

		//get masked images based on min and max values set by the trackbars and testing pixels in that range
		cv::Mat dark_mask, regular_mask, bright_mask, very_bright_mask;
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(dark_hsv, lower, upper, dark_mask);
		cv::inRange(regular_hsv, lower, upper, regular_mask);
		cv::inRange(bright_hsv, lower, upper, bright_mask);
		cv::inRange(very_bright_hsv, lower, upper, very_bright_mask);

		//apply mask on webcam frame with collected data
		cv::GaussianBlur(frame, frame, cv::Size(5, 5), 5, 0); //helps with color detection
		cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);
		cv::inRange(frame_hsv, lower, upper, frame_mask);
		cv::imshow("Webcam", frame_mask);
		cv::imshow("Wecam Original", frame);

		//red needs two color ranges
		cv::Mat red_light, red_dark, red_mask;
		cv::inRange(frame_hsv, cv::Scalar(0, 50, 20), cv::Scalar(5, 255, 255), red_light);
		cv::inRange(frame_hsv, cv::Scalar(175, 50, 20), cv::Scalar(180, 255, 255), red_dark);
		cv::bitwise_or(red_light, red_dark, red_mask);
		
		//display the HSV images and their masks
		cv::imshow("Dark HSV", dark_hsv);
		cv::imshow("Dark HSV Mask", dark_mask);
		cv::imshow("Regular HSV", regular_hsv);
		cv::imshow("Regular HSV Mask", regular_mask);
		cv::imshow("Bright HSV", bright_hsv);
		cv::imshow("Bright HSV Mask", bright_mask);
		cv::imshow("Very Bright HSV", very_bright_hsv);
		cv::imshow("Very Bright HSV Mask", very_bright_mask);
		cv::imshow("Red Mask", red_mask);

		//20 ms buffer
		cv::waitKey(20);
	}

}

/*
Process:
	-cropped cube is passed to the function
	-the function masks with each color and detects the greatest percentage of masked pixels
	-color enumeration is returned with the mostly likely color if percentage is 75% or greater
	-white is the default if no color is found (hard to detect with HSV color space)
*/