#include "ItemRepository.h"
#include <fstream>

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

static constexpr const char* s_MetaFile = "./resources/meta/item.json";

void ItemRepository::Init()
{
    std::ifstream myfile(s_MetaFile);
    rapidjson::IStreamWrapper isw(myfile);
    rapidjson::Document document;
    document.ParseStream<0>(isw);
    auto& tmp = document["data"];

    for (rapidjson::Value::ConstMemberIterator iter = tmp.MemberBegin(); iter != tmp.MemberEnd(); ++iter)
    {
        const char* itemName = iter->name.GetString();
        ItemDescription itemDescription;
        const auto& item = iter->value;
        for (auto& itemIter = item.MemberBegin(); itemIter != item.MemberEnd(); ++itemIter)
        {
            const auto& value = itemIter->value;

            const char* key = itemIter->name.GetString();
            if (!value.IsArray() && !value.IsObject())
            {
                rapidjson::StringBuffer buffer;
                const char* valueStr;
                if (!value.IsString())
                {
                    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
                    value.Accept(writer);
                    valueStr = buffer.GetString();
                }
                else
                {
                    valueStr = value.GetString();
                }

                itemDescription.emplace(key, valueStr);
            }
        }
        m_repository.emplace(itemName, itemDescription);
    }
}

bool ItemRepository::Get(const char* itemName, ItemDescription& description) const
{
    const auto& it = m_repository.find(itemName);
    if (it != m_repository.end())
    {
        description = it->second;
        return true;
    }

    return false;
}
