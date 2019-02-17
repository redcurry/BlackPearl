//
//  UIImage+OpenCV.h
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/17/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#ifdef __cplusplus
#include <opencv2/opencv.hpp>
#endif

#import <UIKit/UIKit.h>

@interface UIImage (OpenCV)

    // cv::Mat to UIImage
    + (UIImage *)imageWithCVMat:(const cv::Mat &)cvMat;

    // UIImage to cv::Mat
    - (cv::Mat)CVMat;

@end
