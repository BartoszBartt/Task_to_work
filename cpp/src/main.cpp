//
// Created by Bartosz on 15.07.2022.
//

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>

#include "colors.hpp"

using std::string;
using std::vector;

template <typename T>
static T min(T a, T b, T c)
{
    if(a <= b && a <= c)
        return a;
    else if (b <= a && b <= c)
        return b;
    else
        return c;
}

template <typename T>
static T max(T a, T b, T c)
{
    if(a >= b && a >= c)
        return a;
    else if (b >= a && b >= c)
        return b;
    else
        return c;
}

template <typename T>
static T hue_counter(T r, T g, T b)
{
    T hue = 0;
    T max_of_colors = max(r, g, b);
    T min_of_colors = min(r, g, b);

    if (max_of_colors - min_of_colors == 0)
        hue = 0;
    else if (max_of_colors == r)
        hue = (g - b)/(max_of_colors - min_of_colors);
    else if (max_of_colors == g)
        hue = 2 + (b - r) / (max_of_colors - min_of_colors);
    else if (max_of_colors == b)
        hue = 4 + (r - g) / (max_of_colors - min_of_colors);

    hue *= 60;
    hue = (int) hue % 360;
    if (hue < 0)
        hue += 360;

    return hue;
}

int main(int argc, char **argv)
{
    string mode, new_color;

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp("-m", argv[i]) || !strcmp("--mode", argv[i]))
        {
            i++;
            mode = argv[i];
        }
        else if (!strcmp("-c", argv[i]) || !strcmp("--color", argv[i]))
        {
            i++;
            new_color = argv[i];
        }
        else
        {
            std::cerr << "Invalid argument: " << argv[i] << std::endl;
            return -1;
        }
    }

    Colors example("colors.txt", mode, new_color);

    if (!new_color.empty())
        example.enter_new_color();

    auto data_print = example.read_variables();

    double hue = 0;
    hue = hue_counter(data_print[0], data_print[1], data_print[2]);

    std::cout <<"Red: " << data_print[0] << std::endl;
    std::cout << "\nGreen: " << data_print[1] << std::endl;
    std::cout << "\nBlue: " << data_print[2] << std::endl;
    std::cout << "\nAlpha: " << data_print[3] << std::endl;
    printf("\nRed in hex: 0x%x\n", (int) data_print[0]);
    std::cout << "\nHue: " << hue << std::endl;
    std::cout << "\nSaturation: " << (data_print[0] + data_print[1] + data_print[2])/765 << std::endl;
    std::cout << "\nSaturation: " << (data_print[0]*0.2126 + data_print[1]*0.7152 + data_print[2]*0.0722)/255 << std::endl;

    return 0;
}
