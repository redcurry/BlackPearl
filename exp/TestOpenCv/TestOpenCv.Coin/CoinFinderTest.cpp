#include "CoinFinder.h"

const int MAX_IMG_LEN = 640;

cv::Mat resize(const cv::Mat& image);
cv::Size resize(const cv::Size& size);

int startCoinFinderTest(int argc, char** argv)
{
	cv::Mat image = cv::imread(argv[1]);
	cv::Mat small_image = resize(image);

	// TODO: CoinFinder should convert to gray, not here
	cv::Mat gray;
	cv::cvtColor(small_image, gray, cv::COLOR_BGR2GRAY);

	CoinFinder coinFinder;
	auto coin = coinFinder.find_coin(gray);

	cv::circle(small_image, coin.center, coin.size.height, cv::Scalar(0, 0, 255), 2);

	cv::namedWindow("Window");
	cv::imshow("Window", small_image);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}

cv::Mat resize(const cv::Mat& image)
{
	cv::Mat new_image;
	cv::resize(image, new_image, resize(cv::Size(image.cols, image.rows)));
	return new_image;
}

cv::Size resize(const cv::Size& size)
{
	auto width = size.width;
	auto height = size.height;

	if (width > height)
	{
		const auto ratio = MAX_IMG_LEN / double(width);
		width = MAX_IMG_LEN;
		height = int(ratio * height);
	}
	else
	{
		const auto ratio = MAX_IMG_LEN / double(height);
		width = int(ratio * width);
		height = MAX_IMG_LEN;
	}

	return { width, height };
}
