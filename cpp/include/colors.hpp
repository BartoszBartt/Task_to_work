//
// Created by Bartosz on 15.07.2022.
//

#ifndef CPP_COLORS_HPP
#define CPP_COLORS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::vector;

template <typename T>
static T sum(const vector<T> &vec)
{
    T out = 0;
    for (const auto &x : vec)
    {
        out += x;
    }
    return out;
}

template <typename T>
static T min(const vector<T> &vec)
{
    T out = vec[0];
    for (const auto &x : vec)
    {
        if (x < out)
        {
            out = x;
        }
    }
    return out;
}

template <typename T>
static T max(const vector<T> &vec)
{
    T out = vec[0];
    for (const auto &x : vec)
    {
        if (x > out)
        {
            out = x;
        }
    }
    return out;
}

class Colors {
public:

    Colors(string path, string mode, string color)
        : _path(std::move(path))
        , _mode(std::move(mode))
        , _color(std::move(color))
    {

    }

    void enter_new_color()
    {
        std::fstream file;
        file.open(_path, std::fstream::app);

        file << '\n';
        file << _color;

        file.close();
    }

    vector<double> read_variables()
    {
        vector<vector<double>> list_var = {{}, {}, {}, {}};
        std::fstream file;
        file.open(_path, std::fstream::in);
        while (!file.eof())
        {
            string line;
            std::getline(file, line);
            if (line.empty()) continue;

            vector<string> colors;
            std::stringstream ss(line);
            while (!ss.eof())
            {
                string color;
                std::getline(ss, color, ',');
                colors.push_back(color);
            }

            for (auto color_index = 0ULL; color_index < colors.size(); ++color_index)
            {
                list_var[color_index].push_back(std::stod(colors[color_index]));
            }
        }

        if (_mode == "mix") {
            return {sum(list_var[0]) / (double) list_var[0].size(), sum(list_var[1]) / (double) list_var[1].size(),
                    sum(list_var[2]) / (double) list_var[2].size(), sum(list_var[3]) / (double) list_var[3].size()};
        }
        else if (_mode == "lowest") {
            return {min(list_var[0]), min(list_var[1]), min(list_var[2]), min(list_var[3])};
        }
        else if (_mode == "highest") {
            return {max(list_var[0]),  max(list_var[1]), max(list_var[2]), max(list_var[3])};
        }
        else if (_mode == "mix-saturate") {
            return {max(list_var[0]), max(list_var[1]), max(list_var[2]), sum(list_var[3])/(double) list_var[3].size()};
        }
        else {
            return {sum(list_var[0]) / (double) list_var[0].size(), sum(list_var[1]) / (double) list_var[1].size(),
                    sum(list_var[2]) / (double) list_var[2].size(), sum(list_var[3]) / (double) list_var[3].size()};
        }
    }

private:
    string _path;
    string _mode;
    string _color;
};


#endif //CPP_COLORS_HPP
