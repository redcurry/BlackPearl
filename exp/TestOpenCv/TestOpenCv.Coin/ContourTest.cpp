#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

const char* adapt_thresh_window = "AdaptiveThreshold";
const char* contours_window = "Contours";

cv::Mat image2;
int max_image_len2;
cv::Mat adapThreshImage;
int blockSize = 15;
int c = 11;
int medianSize = 13;
std::vector<std::vector<cv::Point>> contours;

void adaptiveThreshold()
{
	cv::Mat medianImage;
	cv::medianBlur(image2, medianImage, medianSize);
	cv::adaptiveThreshold(
		medianImage,
		adapThreshImage,
		255,
		cv::ADAPTIVE_THRESH_MEAN_C,
		cv::THRESH_BINARY_INV,
		blockSize,
		c);

	cv::imshow(adapt_thresh_window, adapThreshImage);
}

void onBlockSizeChange(int pos, void* param)
{
	blockSize = pos;
	if (pos % 2 == 0)  // blockSize must be an odd number
		blockSize = pos + 1;
	adaptiveThreshold();
}

void onCChange(int pos, void* param)
{
	c = pos;
	adaptiveThreshold();
}

void onMedianChange(int pos, void* param)
{
	medianSize = pos;
	if (pos % 2 == 0)
		medianSize = pos + 1;
	adaptiveThreshold();
}

void findContours()
{
	cv::findContours(
		adapThreshImage,
		contours,
		cv::RETR_EXTERNAL,
		cv::CHAIN_APPROX_SIMPLE
		);

	adapThreshImage = cv::Scalar::all(0);
	cv::drawContours(adapThreshImage, contours, -1, cv::Scalar::all(255));
}

int startContourTest(int argc, char** argv)
{
	image2 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	cv::resize(image2, image2, cv::Size(480, 640));

	max_image_len2 = image2.cols > image2.rows ? image2.cols : image2.rows;

	medianSize = cvRound(max_image_len2 / 50.0);
	if (medianSize % 2 == 0)
		medianSize++;

	blockSize = cvRound(max_image_len2 / 42.0);
	if (blockSize % 2 == 0)
		blockSize++;

	cv::namedWindow(adapt_thresh_window, cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("blockSize", adapt_thresh_window, &blockSize, 100, onBlockSizeChange);
	cv::createTrackbar("c", adapt_thresh_window, &c, 50, onCChange);
	cv::createTrackbar("median", adapt_thresh_window, &medianSize, 50, onMedianChange);

	adaptiveThreshold();

	cv::imshow(adapt_thresh_window, adapThreshImage);
	cv::waitKey(0);
	cv::destroyWindow(adapt_thresh_window);

	findContours();

	cv::imshow(contours_window, adapThreshImage);
	cv::waitKey(0);
	cv::destroyWindow(contours_window);

	return 0;
}
