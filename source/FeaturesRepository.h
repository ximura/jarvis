#pragma once

#include <string>
#include <unordered_map>

#include <opencv2/core.hpp>

class FeaturesRepository
{
public:
    void Train();

    void Import();
    void Export();

    const char* Match(const char* fileName) const;

private:
    std::unordered_map<std::string, cv::Mat> m_features;
};

