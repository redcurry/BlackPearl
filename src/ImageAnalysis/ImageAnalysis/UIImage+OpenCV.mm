//
//  UIImage+OpenCV.m
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/17/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#import "UIImage+OpenCV.h"

@implementation UIImage (OpenCV)

    + (UIImage *)imageWithCVMat:(const cv::Mat&)cvMat;
    {
        // Fix the order of channels (not in original conversion code)
        cv::Mat bgr;
        cv::cvtColor(cvMat, bgr, cv::COLOR_BGR2RGB);

        NSData *data = [NSData dataWithBytes:bgr.data
            length:bgr.elemSize() * bgr.total()];
        CGColorSpaceRef colorSpace;

        if (bgr.elemSize() == 1) {
            colorSpace = CGColorSpaceCreateDeviceGray();
        } else {
            colorSpace = CGColorSpaceCreateDeviceRGB();
        }

        CGDataProviderRef provider =
            CGDataProviderCreateWithCFData((__bridge CFDataRef)data);

        // Create CGImage from cv::Mat
        CGImageRef imageRef = CGImageCreate(
            bgr.cols,                                    // width
            bgr.rows,                                    // height
            8,                                             // bits per component
            8 * bgr.elemSize(),                          // bits per pixel
            bgr.step[0],                                 // bytes per row
            colorSpace,                                    // color space
            kCGImageAlphaNone | kCGBitmapByteOrderDefault, // bitmap info
            provider,                                      // CGDataProviderRef
            NULL,                                          // decode
            false,                                         // should interpolate
            kCGRenderingIntentDefault);                    // intent

        // Get UIImage from CGImage
        UIImage *finalImage = [UIImage imageWithCGImage:imageRef];
        CGImageRelease(imageRef);
        CGDataProviderRelease(provider);
        CGColorSpaceRelease(colorSpace);

        return finalImage;
    }

    - (cv::Mat)CVMat
    {
        CGColorSpaceRef colorSpace = CGImageGetColorSpace(self.CGImage);
        CGFloat cols = self.size.width;
        CGFloat rows = self.size.height;

        cv::Mat cvMat(rows, cols, CV_8UC4); // 8 bits per component, 4 channels

        CGContextRef contextRef = CGBitmapContextCreate(
            cvMat.data,                                    // pointer to  data
            cols,                                          // width
            rows,                                          // height
            8,                                             // bits per component
            cvMat.step[0],                                 // bytes per row
            colorSpace,                                    // color space
            kCGImageAlphaNoneSkipLast | kCGBitmapByteOrderDefault);

        CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), self.CGImage);
        CGContextRelease(contextRef);

        // Fix the order of channels (not in original conversion code)
        cv::Mat finalMat;
        cv::cvtColor(cvMat, finalMat, cv::COLOR_RGBA2BGR);

        return finalMat;
    }

@end
