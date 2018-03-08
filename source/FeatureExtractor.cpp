#include "FeatureExtractor.h"
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>

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
    auto& descriptors_object = cv::makePtr<cv::Mat>();

    // Initiate KAZE detector
    cv::Ptr<cv::FeatureDetector> detector = cv::KAZE::create();

    // find the keypoints and descriptors with KAZE
    detector->detect(image, keypoints_object);

    cv::Ptr<cv::DescriptorExtractor> extractor = cv::KAZE::create();
    extractor->compute(image, keypoints_object, *descriptors_object.get());

    /*cv::Mat outImage;
    cv::drawKeypoints(image, keypoints_object, outImage);
    cv::imshow("Display Image", outImage);
    cv::waitKey(0);*/

    return descriptors_object;
}
