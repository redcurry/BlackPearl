#include "ApertureFinder.h"
#include "Common.h"

Contour ApertureFinder::find_aperture(const cv::Mat& image) const
{
	auto smooth_image = bilateral_filter(image);
	auto flood_image = flood_fill(image);
	auto inverse_image = invert(image);
	auto binary_image = threshold(image);
	auto contours = find_contours(binary_image);

	if (contours.size() == 1)
		return contours[0];

	if (contours.size() > 1)
		throw std::exception("More than one aperture was found.");

	throw std::exception("No aperture was found.");
}

cv::Mat ApertureFinder::bilateral_filter(const cv::Mat& image) const
{
	cv::Mat smooth_image;
	cv::bilateralFilter(
		image,
		smooth_image,
		calc_d(image),
		BilateralFilterSigmaColor,
		calc_sigma_space(image));
	return smooth_image;
}

int ApertureFinder::calc_d(const cv::Mat& image) const
{
	return cvRound(longest_len(image) * BilateralFilterDRatio);
}

double ApertureFinder::calc_sigma_space(const cv::Mat& image) const
{
	return longest_len(image) * BilateralFilterSigmaSpaceRatio;
}

cv::Mat ApertureFinder::flood_fill(const cv::Mat& image) const
{
	auto center = cv::Point(image.cols / 2, image.rows / 2);
	auto flood_image = image.clone();
	cv::floodFill(flood_image, center, cv::Scalar::all(0), new cv::Rect(),
		cv::Scalar::all(FloodFillUpLowDiff), cv::Scalar::all(FloodFillUpLowDiff), 8);
	return flood_image;
}

cv::Mat ApertureFinder::invert(const cv::Mat& image) const
{
	cv::Mat inverse_image;
	cv::bitwise_not(image, inverse_image);
	return inverse_image;
}

cv::Mat ApertureFinder::threshold(const cv::Mat& image) const
{
	cv::Mat binary_image;
	cv::threshold(image, binary_image, 254, 255, cv::ThresholdTypes::THRESH_BINARY);
	return binary_image;
}

std::vector<Contour> ApertureFinder::find_contours(const cv::Mat& image) const
{
	std::vector<Contour> contours;
	cv::findContours(image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	return contours;
}
