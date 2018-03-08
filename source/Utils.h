#pragma once

#include <vector>
#include <filesystem>

using stringvec = std::vector<std::pair<std::string, std::string>>;

struct path_leaf_string
{
    std::pair<std::string, std::string> operator()(const std::experimental::filesystem::directory_entry& entry) const
    {
        const auto& path = entry.path();
        return std::make_pair(path.string(), path.filename().replace_extension().string());
    }
};

void read_directory(const std::string& name, stringvec& v)
{
    std::experimental::filesystem::path p(name);
    std::experimental::filesystem::directory_iterator start(p);
    std::experimental::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(v), path_leaf_string());
}