#ifndef ADDITIONMETHODS_H
#define ADDITIONMETHODS_H

#include <opencv2/opencv.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

cv::Mat getGaussianFilter(cv::Size size, double sigma, bool invert);
cv::Mat computeDFT(cv::Mat image);
cv::Mat computeIDFT(cv::Mat image);
cv::Mat getIdealFilter(cv::Size size, double width);
cv::Mat getInverseIdealFilter(cv::Size size, double width);
cv::Mat getButterworthFilter(cv::Size size, double width, int order);
cv::Mat getInverseButterworthFilter(cv::Size size, double width, int order);
cv::Mat getLaplacianFilter(cv::Size size);
void shiftImageToCenter(cv::Mat image);
#endif // ADDITIONMETHODS_H
