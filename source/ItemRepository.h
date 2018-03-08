#pragma once

#include <string>
#include <unordered_map>

//it would be better to make some struct for it
using ItemDescription = std::unordered_map<std::string, std::string>;

class ItemRepository
{
public:
    void Init();

    bool Get(const char* itemName, ItemDescription& description) const;
private:
    std::unordered_map<std::string, ItemDescription> m_repository;
};

