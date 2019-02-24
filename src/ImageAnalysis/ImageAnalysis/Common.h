#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

typedef std::vector<cv::Point> Contour;

inline double max(double a, double b)
{
	return a > b ? a : b;
}

inline double distance(const cv::Point& p1, const cv::Point& p2)
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

inline double longest_len(const cv::Mat& image)
{
	return max(image.cols, image.rows);
}
