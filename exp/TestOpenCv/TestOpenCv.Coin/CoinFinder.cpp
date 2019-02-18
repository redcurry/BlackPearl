#include "CoinFinder.h"

cv::RotatedRect CoinFinder::findCoin(const cv::Mat& image) const
{
	const auto image2 = median(image);
	const auto image3 = adaptiveThreshold(image2);
	const auto coins = findCoinCircles(image3);

	if (coins.size() == 1)
		return { coins[0].center, coins[0].size, coins[0].angle };

	if (coins.size() > 1)
		throw std::exception("More than one coin was found.");

	throw std::exception("No coins were found.");
}

cv::Mat CoinFinder::median(const cv::Mat& image) const
{
	cv::Mat new_image;
	cv::medianBlur(image, new_image, calc_median_size(image));
	return new_image;
}

int CoinFinder::calc_median_size(const cv::Mat& image) const
{
	return round_odd(longest_len(image) / 50.0);
}

cv::Mat CoinFinder::adaptiveThreshold(const cv::Mat& image) const
{
	cv::Mat new_image;
	cv::adaptiveThreshold(
		image,
		new_image,
		255,
		cv::ADAPTIVE_THRESH_MEAN_C,
		cv::THRESH_BINARY_INV,
		calc_adapt_thresh_size(image),
		11);
	return new_image;
}

std::vector<cv::RotatedRect> CoinFinder::findCoinCircles(const cv::Mat& image) const
{
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(
		image,
		contours,
		cv::RETR_EXTERNAL,
		cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> candidate_contours;
	for (auto& contour : contours)
	{
		const double area = cv::contourArea(contour);
		if (within_coin_area_range(area, image))
			candidate_contours.push_back(contour);
	}

	std::vector<cv::RotatedRect> coin_circles;
	for (auto& contour : candidate_contours)
	{
		cv::Point2f center;
		float radius;

		cv::minEnclosingCircle(contour, center, radius);

		double fit = calc_percent_circle_fit(contour, center, radius);

		if (fit > 0.5)
			coin_circles.push_back(cv::RotatedRect(center, cv::Size2f(radius, radius), 0));
	}

	return coin_circles;
}

int CoinFinder::calc_adapt_thresh_size(const cv::Mat& image) const
{
	return round_odd(longest_len(image) / 42.0);
}

bool CoinFinder::within_coin_area_range(double a, const cv::Mat& image) const
{
	const double min_area = circle_area(longest_len(image) / 42.0);
	const double max_area = circle_area(longest_len(image) / 16.0);
	return min_area < a && a < max_area;
}

int CoinFinder::round_odd(double x) const
{
	const auto floor = int(std::floor(x));
	return floor % 2 == 0 ? floor + 1 : floor;
}

double CoinFinder::circle_area(double r) const
{
	return CV_PI * r * r;
}

// percent of fit (ideally, every point in contour is equidistant from center)
double CoinFinder::calc_percent_circle_fit(
	const std::vector<cv::Point>& contour, const cv::Point2f& center, float radius) const
{
	int count = 0;

	for (auto& p : contour)
	{
		double d = distance(p, center);
		if (abs(d - radius) / radius < 0.05)
			count++;
	}

	return double(count) / contour.size();
}

double CoinFinder::longest_len(const cv::Mat& image) const
{
	return image.cols > image.rows ? image.cols : image.rows;
}

double CoinFinder::distance(const cv::Point& p1, const cv::Point& p2) const
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
