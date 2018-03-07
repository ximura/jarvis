#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "FeatureExtractor.h"
#include "Utils.h"

static constexpr const char* s_ImgFolder = "./resources/img/";
static constexpr const char* s_DescriptorsFolder = "./resources/descriptors/";

int main(int argc, char** argv)
{
    stringvec v;
    read_directory(s_ImgFolder, v);

    for (const auto& path : v)
    {
        std::cout << "Reading " << path.second.c_str() << std::endl;

        FeatureExtractor extractor;
        auto& descriptors_object = extractor.Extract(path.first.c_str());

        if (descriptors_object.get())
        {
            std::ostringstream oss;
            oss << s_DescriptorsFolder << path.second.c_str() << ".xml";
            std::string descriptorPath = oss.str();

            cv::FileStorage fsWrite(descriptorPath, cv::FileStorage::WRITE);
            fsWrite << "descriptor" << *descriptors_object.get();
            fsWrite.release();

            cv::Mat descriptor;
            cv::FileStorage fs(descriptorPath, cv::FileStorage::READ);
            fs["descriptor"] >> descriptor;
            fs.release();

            std::cout << descriptor.rows << std::endl;
        }
        else
        {
            std::cout << "Can't extract features from " << path.first << std::endl;
        }
    }

    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}