#pragma once
#include <opencv2/core.hpp>

class FeatureExtractor
{
public:
    static cv::Ptr<cv::Mat> Extract(const char* path);
};

