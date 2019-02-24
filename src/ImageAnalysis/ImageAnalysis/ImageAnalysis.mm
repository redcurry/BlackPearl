//
//  ImageAnalysis.m
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/16/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#ifdef __cplusplus
#include "CoinFinder.h"
#endif

#import "ImageAnalysis.h"
#import "UIImage+OpenCV.h"

@implementation ImageAnalysis

- (NSArray *)findCoin:(UIImage *)image
{
    cv::Mat mat = [image CVMat];
    CoinFinder coinFinder;
    cv::RotatedRect coin = coinFinder.find_coin(mat);
    return @[ [NSNumber numberWithDouble:(coin.center.x)],
              [NSNumber numberWithDouble:(coin.center.y)],
              [NSNumber numberWithDouble:(coin.size.width)],
              [NSNumber numberWithDouble:(coin.size.height)],
              [NSNumber numberWithDouble:(coin.angle)] ];
}

@end
