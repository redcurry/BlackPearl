//
//  ImageDrawer.hpp
//  ImageAnalysis
//
//  Created by Carlos Anderson on 2/17/19.
//  Copyright © 2019 Carlos Anderson. All rights reserved.
//

#ifndef ImageDrawer_hpp
#define ImageDrawer_hpp

#include <opencv2/opencv.hpp>

class ImageDrawer
{
public:
    void DrawOn(cv::Mat& image);
};

#endif /* ImageDrawer_hpp */
