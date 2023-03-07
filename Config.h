#ifndef CONFIG_H
#define CONFIG_H

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Eigen/Eigen"

#define MW_ALERT printf("Alert At: %s %d.\n", __FILE__, __LINE__);
#define MW_ERROR                                      \
    printf("Error At: %s %d.\n", __FILE__, __LINE__); \
    exit(0);

using Real = long double;
using Integer = long long int;

using Matrix = Eigen::Matrix<Real, Eigen::Dynamic, Eigen::Dynamic>;
using Vector = Eigen::Matrix<Real, Eigen::Dynamic, 1>;

constexpr Integer MAX_LOOP_NUM = 0x10000ll;
constexpr Real DELTA = std::numeric_limits<float>::epsilon();
constexpr Real MAX = std::numeric_limits<float>::max();

std::vector<std::string> split(const std::string &s, const char &c);

std::vector<std::string> split(const std::string &s, const char &c)
{
    std::vector<std::string> res;
    Integer begin = 0;
    Integer i = 0;
    Integer l = s.length();
    while (i < l)
    {
        if (s[i] == c)
        {
            res.push_back(s.substr(begin, i - begin));
            begin = i + 1;
        }
        i++;
    }
    res.push_back(s.substr(begin));
    return res;
}

#endif
