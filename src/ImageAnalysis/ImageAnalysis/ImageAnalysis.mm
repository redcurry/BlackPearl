//
//  ImageAnalysis.m
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/16/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#ifdef __cplusplus
#include "MeanCalc.hpp"
#endif

#import "ImageAnalysis.h"

@implementation ImageAnalysis

- (double)getMean
{
    return MeanCalc().GetMean();
}

@end
