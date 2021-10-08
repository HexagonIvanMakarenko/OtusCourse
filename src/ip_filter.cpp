#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void sort(std::vector<std::vector<std::string>> & ip_pool)
{
    auto isEqual = [](const std::string& firstIPPart, const std::string& secondIPPart)
    {
        return firstIPPart == secondIPPart;
    };
    auto isLess = [](const std::string & firstIPPart, const std::string & secondIPPart)
    {
        if (firstIPPart.size() < secondIPPart.size())
            return true;

        if (firstIPPart.size() > secondIPPart.size())
            return false;

        for (size_t idx = 0; idx < firstIPPart.size(); ++idx)
        {
            if (firstIPPart[idx] < secondIPPart[idx])
                return true;

            if (secondIPPart[idx] < firstIPPart[idx])
                return false;
        }
        return false;
    };
    std::sort(ip_pool.begin(), ip_pool.end(), [&isLess, &isEqual](const auto & firstIP, const auto & secondIP)
    {
        for (size_t idx = 0; idx < 4; ++idx)
        {
            if (isEqual(firstIP[idx], secondIP[idx]))
                continue;

            return isLess(firstIP[idx], secondIP[idx]);
        }
        return false;
    });
}

void printWithCriteria(const std::vector<std::vector<std::string>>& ip_pool, const std::function<bool(const std::vector<std::string> &)> & criteria)
{
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if (!criteria(*ip))
            continue;

        for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
                std::cout << ".";

            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;
        for (std::string line; std::getline(std::cin, line);)
        {
            if (line.empty())
                break;

            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        sort(ip_pool);
        printWithCriteria(ip_pool, [](const std::vector<std::string> & ip) {return true; });
        printWithCriteria(ip_pool, [](const std::vector<std::string> & ip) {return ip.at(0) == "1"; });
        printWithCriteria(ip_pool, [](const std::vector<std::string> & ip) {return ip.at(0) == "46" && ip.at(1) == "70"; });
        printWithCriteria(ip_pool, [](const std::vector<std::string> & ip) 
        {
            for (const auto& ipPart : ip)
            {
                if (ipPart == "46")
                    return true;
            }
            return false;
        });
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
