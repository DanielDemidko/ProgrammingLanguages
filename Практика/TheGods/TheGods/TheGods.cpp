#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>

bool IsName(const std::string_view &name, const std::string_view &word)
{
    size_t res = 0;
    for (auto i = cbegin(name), j = cbegin(word); i < cend(name); ++i, ++j)
    {
        if (*i != *j)
        {
            ++res;
        }
        if (res > 1)
        {
            return false;
        }
    }
    return true;
}

std::vector<std::string> ReadBlock()
{
    static std::ifstream input("Input.txt");
    std::vector<std::string> res(*std::istream_iterator<size_t>(input));
    for (auto &i : res)
    {
        input >> i;
    }
    return res;
}

std::unordered_map<size_t, std::vector<std::string>> SplitBySize(const std::vector<std::string> &block)
{
    std::unordered_map<size_t, std::vector<std::string>> res;
    for (const auto &i : block)
    {
        res[size(i)].push_back(i);
    }
    return res;
}

int main()
{
    const auto trueNames = ReadBlock();
    auto allNames = SplitBySize(ReadBlock());
    std::ofstream output("Output.txt");
    for (const auto &i : trueNames)
    {
        size_t res = 0;
        for (auto &j : allNames[size(i)])
        {
            if (IsName(i, j))
            {
                ++res;
            }
        }
        output << res << ' ';
    }
}
