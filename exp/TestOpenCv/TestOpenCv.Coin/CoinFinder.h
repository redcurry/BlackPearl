#pragma once

#include <opencv2/opencv.hpp>

class CoinFinder
{
public:
	cv::RotatedRect find_coin(const cv::Mat& image) const;

private:

	cv::Mat median(const cv::Mat& image) const;
	cv::Mat adaptive_threshold(const cv::Mat& image) const;
	std::vector<cv::RotatedRect> find_coin_circles(const cv::Mat& image) const;
	double calc_percent_circle_fit(const std::vector<cv::Point>& contour, const cv::Point2f& center, float radius) const;
	double longest_len(const cv::Mat& image) const;
	int calc_median_size(const cv::Mat& image) const;
	int calc_adapt_thresh_size(const cv::Mat& image) const;
	bool within_coin_area_range(double a, const cv::Mat& image) const;
	int round_odd(double x) const;
	double circle_area(double r) const;
	double distance(const cv::Point& p1, const cv::Point& p2) const;
};

