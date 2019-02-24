#include "FloodFillTest.h"
#include <opencv2/opencv.hpp>

namespace FloodFillTest
{
	cv::Mat image;
	cv::Mat median_image;
	cv::Mat smooth_image;
	cv::Mat flood_image;

	cv::String smooth_window = "SmoothWindow";
	cv::String flood_window = "FloodWindow";

	int d = 13;
	int sigma_color = 32;
	int sigma_space = 13;

	void show_bilateral_filter();
	void bilateral_filter();
	void on_d_change(int pos, void* param);
	void on_sigma_color_change(int pos, void* param);
	void on_sigma_space_change(int pos, void* param);

	int low_diff = 2;
	int up_diff = 2;

	void show_flood_fill();
	void flood_fill();
	void on_low_diff_change(int pos, void* param);
	void on_up_diff_change(int pos, void* param);

	int start(int argc, char** argv)
	{
		image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
		cv::resize(image, image, cv::Size(480, 640));

		show_bilateral_filter();
		show_flood_fill();

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
		cv::createTrackbar("lowDiff", flood_window, &low_diff, 50, on_low_diff_change);
		cv::createTrackbar("upDiff", flood_window, &up_diff, 50, on_up_diff_change);

		flood_fill();

		cv::imshow(flood_window, smooth_image);
		cv::waitKey(0);
		cv::destroyWindow(flood_window);
	}

	void flood_fill()
	{
		auto center = cv::Point(image.cols / 2, image.rows / 2);
		cv::Rect* bounds = new cv::Rect();
		flood_image = smooth_image.clone();
		cv::floodFill(flood_image, center, cv::Scalar::all(0), bounds,
			cv::Scalar::all(low_diff), cv::Scalar::all(up_diff), 8);
	}

	void on_low_diff_change(int pos, void* param)
	{
		low_diff = pos;
		flood_fill();
		cv::imshow(flood_window, flood_image);
	}

	void on_up_diff_change(int pos, void* param)
	{
		up_diff = pos;
		flood_fill();
		cv::imshow(flood_window, flood_image);
	}
}
