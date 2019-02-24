#include "CoinFinder.h"
#include "Common.h"

cv::RotatedRect CoinFinder::find_coin(const cv::Mat& image) const
{
	const auto median_image = median(image);
	const auto canny_image = canny(median_image);
	const auto contours = find_contours(canny_image);
	const auto circles = find_circles(contours);
	const auto coins = find_coins(image, circles);

	if (coins.size() == 1)
		return { coins[0].center, coins[0].size, coins[0].angle };

	if (coins.size() > 1)
		throw std::runtime_error("More than one coin was found.");

	throw std::runtime_error("No coins was found.");
}

cv::Mat CoinFinder::median(const cv::Mat& image) const
{
	cv::Mat median_image;
	cv::medianBlur(image, median_image, calc_median_k(image));
	return median_image;
}

int CoinFinder::calc_median_k(const cv::Mat& image) const
{
	return round_odd(longest_len(image) * MedianKRatio);
}

cv::Mat CoinFinder::canny(const cv::Mat& image) const
{
	cv::Mat canny_image;
	cv::Canny(image, canny_image, CannyThreshold1, CannyThreshold2);
	return canny_image;
}

std::vector<Contour> CoinFinder::find_contours(const cv::Mat& image) const
{
	std::vector<Contour> contours;
	cv::findContours(
		image,
		contours,
		cv::RETR_EXTERNAL,
		cv::CHAIN_APPROX_SIMPLE);
	return contours;
}

std::vector<cv::RotatedRect> CoinFinder::find_circles(const std::vector<Contour>& contours) const
{
	std::vector<cv::RotatedRect> circles;
	for (auto& contour : contours)
	{
		cv::Point2f center;
		float radius;

		cv::minEnclosingCircle(contour, center, radius);

		const double fit_ratio = calc_circle_fit_ratio(contour, center, radius);
		if (fit_ratio > MinCircleFitRatio)
			circles.push_back(cv::RotatedRect(center, cv::Size2f(radius, radius), 0));
	}

	return circles;
}

// Fit ratio (ideally, every point in contour is equidistant from center)
double CoinFinder::calc_circle_fit_ratio(const Contour& contour, const cv::Point2f& center, double r) const
{
	int count = 0;

	for (auto& point : contour)
	{
		const double d = distance(point, center);
		if (abs(d - r) / r < MaxCircleFitError)
			count++;
	}

	return double(count) / contour.size();
}

std::vector<cv::RotatedRect> CoinFinder::find_coins(const cv::Mat& image, const std::vector<cv::RotatedRect>& circles) const
{
	const double min_radius = longest_len(image) * MinCoinRadiusRatio;
	const double max_radius = longest_len(image) * MaxCoinRadiusRatio;
	return filter_by_radius(circles, min_radius, max_radius);
}

// Currently, RotatedRect contain circles
std::vector<cv::RotatedRect> CoinFinder::filter_by_radius(std::vector<cv::RotatedRect> circles, double min, double max) const
{
	std::vector<cv::RotatedRect> good_circles;
	for (auto& circle : circles)
	{
		const double radius = circle.size.width / 2.0;
		if (min < radius && radius < max)
			good_circles.push_back(circle);
	}
	return good_circles;
}

int CoinFinder::round_odd(double x) const
{
	const auto floor = int(std::floor(x));
	return floor % 2 == 0 ? floor + 1 : floor;
}
