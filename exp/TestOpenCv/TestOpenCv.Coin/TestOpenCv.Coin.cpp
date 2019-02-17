#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

cv::Mat image;
cv::Mat canny;
cv::Mat canny_circles;

int canny1 = 400;
int canny2 = 200;

std::vector<cv::Vec3f> circles;

int max_image_len;

// accumulator plane resolution (1.0 is size of image, 2.0 is half)
double dp = 4.0;

int minRadius;
int maxRadius;

int accum_thresh = 10;

void onCanny1Change(int pos, void* param)
{
	canny1 = pos;
	cv::Canny(image, canny, canny1, canny2);
	cv::imshow("Canny", canny);
}

void onCanny2Change(int pos, void* param)
{
	canny2 = pos;
	cv::Canny(image, canny, canny1, canny2);
	cv::imshow("Canny", canny);
}

void detect_and_draw_circles();

void onAccumChange(int pos, void* param)
{
	accum_thresh = pos;
	detect_and_draw_circles();
	cv::imshow("Circles", canny_circles);
}

void detect_and_draw_circles()
{
	cv::HoughCircles(
		image,
		circles,
		cv::HOUGH_GRADIENT,
		dp,
		minRadius * 2.0,   // minimum distance between circles
		canny1,
		accum_thresh,
		minRadius,
		maxRadius);

	canny_circles = canny.clone();

	for (int i = 0; i < circles.size(); i++)
	{
		cv::circle(
			canny_circles,
			cv::Point(cvRound(circles[i][0]), cvRound(circles[i][1])),
			cvRound(circles[i][2]),
			cv::Scalar(128, 128, 128),
			1,
			cv::LINE_AA
		);
	}
}

int main(int argc, char** argv)
{
	image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	if (image.empty()) return -1;

	cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("canny1", "Canny", &canny1, 1000, onCanny1Change);
	cv::createTrackbar("canny2", "Canny", &canny2, 1000, onCanny2Change);

	cv::Canny(image, canny, canny1, canny2);

	cv::imshow("Canny", canny);
	cv::waitKey(0);
	cv::destroyWindow("Canny");

	max_image_len = image.cols > image.rows ? image.cols : image.rows;

	minRadius = cvRound(max_image_len / 42.0);
	maxRadius = cvRound(max_image_len / 16.0);
	accum_thresh = cvRound(2.0 * CV_PI * minRadius);

	std::cout << "max_image_len: " << max_image_len << std::endl;
	std::cout << "min radius: " << minRadius << std::endl;
	std::cout << "max radius: " << maxRadius << std::endl;
	std::cout << "accum_thresh: " << accum_thresh << std::endl;

	cv::namedWindow("Circles", cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("accum_thresh", "Circles", &accum_thresh, 200, onAccumChange);

	detect_and_draw_circles();

	cv::imshow("Circles", canny_circles);
	cv::waitKey(0);
	cv::destroyWindow("Circles");

	return 0;
}
