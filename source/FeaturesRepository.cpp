#include "FeaturesRepository.h"
#include "FeatureExtractor.h"

#include "Utils.h"

#include <iostream>

#include <opencv2/features2d.hpp>

static constexpr const char* s_ImgFolder = "./resources/img/";
static constexpr const char* s_DescriptorsFolder = "./resources/descriptors/";

static constexpr const float s_MatchRatio = 0.8f;   // Nearest neighbor matching ratio

void FeaturesRepository::Train()
{
    stringvec v;
    read_directory(s_ImgFolder, v);

    for (const auto& path : v)
    {
        auto& descriptors_object = FeatureExtractor::Extract(path.first.c_str());

        if (descriptors_object.get())
        {
            m_features.emplace(path.second, *descriptors_object.get());
        }
        else
        {
            std::cout << "Can't extract features from " << path.first << std::endl;
        }
    }
}

void FeaturesRepository::Import()
{
    stringvec v;
    read_directory(s_DescriptorsFolder, v);
    for (const auto& path : v)
    {
        cv::Mat descriptor;
        cv::FileStorage fs(path.first.c_str(), cv::FileStorage::READ);
        fs["descriptor"] >> descriptor;
        fs.release();

        std::cout << descriptor.rows << std::endl;

        m_features.emplace(path.second, descriptor);
    }
}

void FeaturesRepository::Export()
{
    for (const auto& pair : m_features)
    {
        const char* name = pair.first.c_str();
        const auto& descriptor = pair.second;

        std::ostringstream oss;
        oss << s_DescriptorsFolder << name << ".yml";
        std::string descriptorPath = oss.str();

        cv::FileStorage fsWrite(descriptorPath, cv::FileStorage::WRITE);
        fsWrite << "descriptor" << descriptor;
        fsWrite.release();
    }
}

const char* FeaturesRepository::Match(const char* fileName) const
{
    auto& descriptors_object = FeatureExtractor::Extract(fileName);
    const char* result = nullptr;
    int bestMatchCounter{ 0 };

    if (descriptors_object.get())
    {
        const auto& queryDescriptor = *descriptors_object.get();
        auto& matcher = cv::BFMatcher();

        for (const auto& pair : m_features)
        {
            const char* name = pair.first.c_str();
            const auto& descriptor = pair.second;

            std::vector<std::vector<cv::DMatch>> matches;
            matcher.knnMatch(queryDescriptor, descriptor, matches, 2);

            int matchCounter { 0 };

            std::vector<cv::DMatch> good_matches;
            for (size_t i = 0; i < matches.size(); i++) 
            {
                float dist1 = matches[i][0].distance;
                float dist2 = matches[i][1].distance;

                if (dist1 < s_MatchRatio * dist2) 
                {
                    ++matchCounter;
                }
            }

            if (matchCounter > bestMatchCounter)
            {
                bestMatchCounter = matchCounter;
                result = name;
            }
        }
    }
    else
    {
        std::cout << "Can't extract features from " << fileName << std::endl;
    }

    return result;
}
