//
//  MeanCalc.cpp
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/17/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#include "MeanCalc.hpp"
#include <opencv2/opencv.hpp>

double MeanCalc::GetMean()
{
    return cv::mean(cv::Scalar(10.0, 20.0, 30.0, 40.0))[0];
}
