#include "FeatureExtractor.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>


#include <iostream>

cv::Ptr<cv::Mat> FeatureExtractor::Extract(const char * path)
{
    cv::Mat image;
    image = cv::imread(path, cv::IMREAD_GRAYSCALE); // Read the file
    if (image.empty()) // Check for invalid input
    {
        std::cout << "Could not open or find the image" << std::endl;
        return cv::Ptr<cv::Mat>();
    }

    std::vector<cv::KeyPoint> keypoints_object;
    cv::Mat descriptors_object;

    // Initiate ORB detector
    cv::Ptr<cv::FeatureDetector> detector = cv::KAZE::create();

    // find the keypoints and descriptors with ORB
    detector->detect(image, keypoints_object);

    cv::Ptr<cv::DescriptorExtractor> extractor = cv::KAZE::create();
    extractor->compute(image, keypoints_object, descriptors_object);

    return cv::makePtr<cv::Mat>(descriptors_object);
}
