#pragma once

#include <opencv2/core.hpp>

class FeatureExtractor
{
public:
    cv::Ptr<cv::Mat> Extract(const char* path);
};

