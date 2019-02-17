//
//  ImageAnalysis.m
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/16/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#ifdef __cplusplus
#include "ImageDrawer.hpp"
#endif

#import "ImageAnalysis.h"
#import "UIImage+OpenCV.h"

@implementation ImageAnalysis

- (UIImage *)drawOn:(UIImage *)image
{
    cv::Mat mat = [image CVMat];
    ImageDrawer drawer;
    drawer.DrawOn(mat);
    return [UIImage imageWithCVMat:mat];
}

@end
