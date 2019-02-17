//
//  ImageDrawer.cpp
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/17/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#include "ImageDrawer.hpp"
#include <opencv2/opencv.hpp>

void ImageDrawer::DrawOn(cv::Mat& image)
{
    cv::drawMarker(image, cv::Point(20, 20), cv::Scalar(0, 255, 0),
        cv::MARKER_CROSS, 20, 4);
}
