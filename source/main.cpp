#include <iostream>

#include "FeaturesRepository.h"
#include "ItemRepository.h"

int main(int argc, char** argv)
{
    ItemRepository itemRepository;
    itemRepository.Init();

    FeaturesRepository featuresRepository;
    featuresRepository.Train();
    featuresRepository.Export();

    const char* item = "./resources/img/1002.png";

    const char* itemName = featuresRepository.Match(item);
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

    return 0;
}