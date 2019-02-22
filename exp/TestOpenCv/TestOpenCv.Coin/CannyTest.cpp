#include <opencv2/opencv.hpp>

namespace CannyTest
{
	void median();
	void on_median_change(int pos, void* param);

	void canny();
	void on_canny1_change(int pos, void* param);
	void on_canny2_change(int pos, void* param);

	void find_contours();

	const char* median_window = "Median";
	const char* canny_window = "Canny";
	const char* contour_window = "Contours";

	cv::Mat image;
	int max_image_len;

	cv::Mat median_image;
	int median_size = 13;

	cv::Mat canny_image;
	int thresh1 = 500;
	int thresh2 = 250;

	std::vector<std::vector<cv::Point>> contours;

	int start_canny_test(int argc, char** argv)
	{
		image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
		cv::resize(image, image, cv::Size(480, 640));

		max_image_len = image.cols > image.rows ? image.cols : image.rows;

		median_size = cvRound(0.02 * max_image_len);
		if (median_size % 2 == 0)
			median_size++;

		cv::namedWindow(median_window, cv::WINDOW_AUTOSIZE);
		cv::createTrackbar("median", median_window, &median_size, 50, on_median_change);

		median();

		cv::imshow(median_window, median_image);
		cv::waitKey(0);
		cv::destroyWindow(median_window);

		cv::namedWindow(canny_window, cv::WINDOW_AUTOSIZE);
		cv::createTrackbar("thresh1", canny_window, &thresh1, 800, on_canny1_change);
		cv::createTrackbar("thresh2", canny_window, &thresh2, 800, on_canny2_change);

		canny();

		cv::imshow(canny_window, canny_image);
		cv::waitKey(0);
		cv::destroyWindow(canny_window);

		cv::namedWindow(contour_window, cv::WINDOW_AUTOSIZE);

		find_contours();

		cv::imshow(contour_window, canny_image);
		cv::waitKey(0);
		cv::destroyWindow(contour_window);

		return 0;
	}

	void median()
	{
		cv::medianBlur(image, median_image, median_size);
	}

	void on_median_change(int pos, void* param)
	{
		median_size = pos;
		if (pos % 2 == 0)
			median_size = pos + 1;
		median();
		cv::imshow(median_window, median_image);
	}

	void canny()
	{
		cv::Canny(median_image, canny_image, thresh1, thresh2);
	}

	void on_canny1_change(int pos, void* param)
	{
		thresh1 = pos;
		canny();
		cv::imshow(canny_window, canny_image);
	}

	void on_canny2_change(int pos, void* param)
	{
		thresh2 = pos;
		canny();
		cv::imshow(canny_window, canny_image);
	}

	void find_contours()
	{
		cv::findContours(canny_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		cv::drawContours(canny_image, contours, -1, cv::Scalar(128, 128, 128), 2);

		std::cout << "contours: " << contours.size() << std::endl;
	}
}
