#include <iostream>

#include "FeaturesRepository.h"
#include "ItemRepository.h"

int main(int argc, char** argv)
{
    // Create repository
    ItemRepository itemRepository;
    itemRepository.Init();

    FeaturesRepository featuresRepository;

    // communicate with user
    char response;
    std::cout << "Do we need perform training?(Y/N)" << std::endl;
    std::cin >> response;
    if (response == 'Y')
    {
        featuresRepository.Train();
        featuresRepository.Export();
    }
    else
    {
        // we should try to load data from previous train
        featuresRepository.Import();
    }

    std::string item;
    std::cout << "Enter file to match: " << std::endl;
    std::cin >> item;

    // try to match image with repository
    const char* itemName = featuresRepository.Match(item.c_str());
    ItemDescription description;
    if (itemName == nullptr || !itemRepository.Get(itemName, description))
    {
        std::cout << "Info for item " << item << " not found" << std::endl;
    }
    else
    {
        for (const auto& pair : description)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    system("pause");
    return 0;
}