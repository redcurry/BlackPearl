#pragma once

#include <opencv2/opencv.hpp>

typedef std::vector<cv::Point> Contour;

class ApertureFinder
{
public:
	Contour find_aperture(const cv::Mat& image) const;

private:
	const double BilateralFilterDRatio = 0.03;
	const double BilateralFilterSigmaColor = 17.0;  // Independent of image size
	const double BilateralFilterSigmaSpaceRatio = 0.02;

	const double FloodFillUpLowDiff = 2;

	cv::Mat bilateral_filter(const cv::Mat& image) const;
	int calc_d(const cv::Mat& image) const;
	double calc_sigma_space(const cv::Mat& image) const;
	cv::Mat flood_fill(const cv::Mat& image) const;
	cv::Mat invert(const cv::Mat& image) const;
	cv::Mat threshold(const cv::Mat& image) const;
	std::vector<Contour> find_contours(const cv::Mat& image) const;
};

