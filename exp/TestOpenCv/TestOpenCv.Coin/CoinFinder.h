#pragma once

#include <opencv2/opencv.hpp>
#include "Common.h"

class CoinFinder
{
public:
	cv::RotatedRect find_coin(const cv::Mat& image) const;

private:

	const double MedianKRatio = 0.02;

	const int CannyThreshold1 = 300;
	const int CannyThreshold2 = 150;

	const double MinCircleFitRatio = 0.5;
	const double MaxCircleFitError = 0.05;

	const double MinCoinRadiusRatio = 0.02;
	const double MaxCoinRadiusRatio = 0.05;

	cv::Mat median(const cv::Mat& image) const;
	cv::Mat canny(const cv::Mat& image) const;
	std::vector<Contour> find_contours(const cv::Mat& image) const;
	std::vector<cv::RotatedRect> find_circles(const std::vector<Contour>& contours) const;
	std::vector<cv::RotatedRect> find_coins(const cv::Mat& image, const std::vector<cv::RotatedRect>& circles) const;
	std::vector<cv::RotatedRect> filter_by_radius(std::vector<cv::RotatedRect> circles, double min, double max) const;
	double calc_circle_fit_ratio(const Contour& contour, const cv::Point2f& center, double r) const;
	int calc_median_k(const cv::Mat& image) const;
	int round_odd(double x) const;
};

