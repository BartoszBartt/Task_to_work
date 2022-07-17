#!/usr/bin/python
# -*- coding: utf-8 -*-
import argparse
import os
import re

class Color:
    def __init__(self, path, mode, color):
        self.mode = mode
        self.color = color
        self.path = path

    def read_variables(self):
        list_var = [[], [], [], []]
        with open(self.path, "r") as file:
            for line in file:
                line = line.strip('\n')
                if line.strip() == '':
                    continue
                colors = line.split(',')
                #sprawdzanie poprawności danych
                regex = re.compile(r'^([0-9]{1,3},){3}[0-9]{1,3}$')
                if re.match(regex, line) is None:
                    raise argparse.ArgumentTypeError('Wrong type of data')
                else:
                    for color_index in range(len(colors)):
                        list_var[color_index].append(int(colors[color_index]))

        if self.mode == 'mix':
            return [sum(list_var[0])/len(list_var[0]), sum(list_var[1])/len(list_var[1]),
                    sum(list_var[2])/len(list_var[2]), sum(list_var[3])/len(list_var[3])]
        elif self.mode == 'lowest':
            return [min(list_var[0]), min(list_var[1]), min(list_var[2]), min(list_var[3])]
        elif self.mode == 'highest':
            return [max(list_var[0]), max(list_var[1]), max(list_var[2]), max(list_var[3])]
        elif self.mode == 'mix-saturate':
            return [max(list_var[0]), max(list_var[1]), max(list_var[2]), sum(list_var[3])/len(list_var[3])]
        else:
            return [sum(list_var[0]) / len(list_var[0]), sum(list_var[1]) / len(list_var[1]),
                    sum(list_var[2]) / len(list_var[2]), sum(list_var[3]) / len(list_var[3])]

    def enter_new_color(self):
        with open(self.path, "a+") as file:
            file.seek(0)
            data = file.read(100)
            if len(data) > 0:
                file.write("\n")
            file.write(self.color)


def hue_counter(r, g, b):
    hue = 0
    max_of_colors = max(r, g, b)
    min_of_colors = min(r, g, b)

    if max_of_colors - min_of_colors == 0:
        hue = 0
    elif max_of_colors == r:
        hue = (g - b)/(max_of_colors - min_of_colors)
    elif max_of_colors == g:
        hue = 2 + (b - r) / (max_of_colors - min_of_colors)
    elif max_of_colors == b:
        hue = 4 + (r - g) / (max_of_colors - min_of_colors)
    hue *= 60
    hue %= 360
    if hue < 0:
        hue += 360
    return hue


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--mode', action='store',
                        help='Printing modes of colors', type=str, dest='mode')
    parser.add_argument('-c', '--color', action='store',
                        help='You can add here more colors', type=str, dest='new_color')
    args = parser.parse_args()

    list_modes = ['mix', 'lowest', 'highest', 'mix-saturate']
    if os.path.exists('colors.txt'):
        if args.mode in list_modes:
            pass
    else:
        raise argparse.ArgumentTypeError('There is not "colors.txt" or path is wrong')

    example = Color('colors.txt', args.mode, args.new_color)

    if args.new_color is not None:
        example.enter_new_color()
    data_print = example.read_variables()

    hue = hue_counter(data_print[0], data_print[1], data_print[2])

    print("Red", data_print[0])
    print("\nGreen", data_print[1])
    print("\nBlue", data_print[2])
    print("\nAplha", data_print[3])
    print("\nRed in hex", hex(int(data_print[0])))
    print("\nHue", hue)
    print("\nSaturation", (data_print[0] + data_print[1] + data_print[2])/765)
    print("\nLightness", (data_print[0]*0.2126 + data_print[1]*0.7152 + data_print[2]*0.0722)/255)

if __name__ == "__main__":
    main()
