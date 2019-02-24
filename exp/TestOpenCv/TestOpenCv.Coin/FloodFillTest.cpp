#include "FloodFillTest.h"
#include <opencv2/opencv.hpp>

namespace FloodFillTest
{
	typedef std::vector<cv::Point> Contour;

	cv::Mat image;
	cv::Mat median_image;
	cv::Mat smooth_image;
	cv::Mat flood_image;

	cv::String smooth_window = "SmoothWindow";
	cv::String flood_window = "FloodWindow";
	cv::String image_window = "ImageWindow";

	int d = 21;
	int sigma_color = 17;
	int sigma_space = 13;

	void show_bilateral_filter();
	void bilateral_filter();
	void on_d_change(int pos, void* param);
	void on_sigma_color_change(int pos, void* param);
	void on_sigma_space_change(int pos, void* param);

	int up_low_diff = 2;

	void show_flood_fill();
	void flood_fill();
	void on_up_low_diff_change(int pos, void* param);

	void invert();
	void threshold();

	int start(int argc, char** argv)
	{
		image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
		cv::resize(image, image, cv::Size(480, 640));

		show_bilateral_filter();
		show_flood_fill();

		image = flood_image;

		invert();
		threshold();

		std::vector<Contour> contours;
		cv::findContours(image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		cv::drawContours(image, contours, -1, cv::Scalar(128, 128, 128), 2);

		cv::namedWindow(image_window, cv::WINDOW_AUTOSIZE);
		cv::imshow(image_window, image);
		cv::waitKey(0);
		cv::destroyWindow(image_window);

		return 0;
	}

	void show_bilateral_filter()
	{
		cv::namedWindow(smooth_window, cv::WINDOW_AUTOSIZE);
		cv::createTrackbar("d", smooth_window, &d, 100, on_d_change);
		cv::createTrackbar("sigmaColor", smooth_window, &sigma_color, 100, on_sigma_color_change);
		cv::createTrackbar("sigmaSpace", smooth_window, &sigma_space, 200, on_sigma_space_change);

		bilateral_filter();

		cv::imshow(smooth_window, smooth_image);
		cv::waitKey(0);
		cv::destroyWindow(smooth_window);
	}

	void bilateral_filter()
	{
		cv::bilateralFilter(image, smooth_image, d, sigma_color, sigma_space);
	}

	void on_d_change(int pos, void* param)
	{
		d = pos;
		bilateral_filter();
		cv::imshow(smooth_window, smooth_image);
	}

	void on_sigma_color_change(int pos, void* param)
	{
		sigma_color = pos;
		bilateral_filter();
		cv::imshow(smooth_window, smooth_image);
	}

	void on_sigma_space_change(int pos, void* param)
	{
		sigma_space = pos;
		bilateral_filter();
		cv::imshow(smooth_window, smooth_image);
	}

	void show_flood_fill()
	{
		cv::namedWindow(flood_window, cv::WINDOW_AUTOSIZE);
		cv::createTrackbar("upLowDiff", flood_window, &up_low_diff, 50, on_up_low_diff_change);

		flood_fill();

		cv::imshow(flood_window, flood_image);
		cv::waitKey(0);
		cv::destroyWindow(flood_window);
	}

	void flood_fill()
	{
		auto center = cv::Point(image.cols / 2, image.rows / 2);
		cv::Rect* bounds = new cv::Rect();
		flood_image = smooth_image.clone();
		cv::floodFill(flood_image, center, cv::Scalar::all(0), bounds,
			cv::Scalar::all(up_low_diff), cv::Scalar::all(up_low_diff), 8);
	}

	void on_up_low_diff_change(int pos, void* param)
	{
		up_low_diff = pos;
		flood_fill();
		cv::imshow(flood_window, flood_image);
	}

	void invert()
	{
		cv::bitwise_not(image, image);
	}

	void threshold()
	{
		cv::threshold(image, image, 254, 255, cv::ThresholdTypes::THRESH_BINARY);
	}
}
