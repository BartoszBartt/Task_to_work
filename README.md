# Task_to_work
Zadanie rekrutacyjne

0. General rules:
    - Do not use any external library except those included into default bundle
    - Catch exceptions in all places which need that
    - Shebang
    - Python 2.7 or 3
    - Valid color formats:
        - /^([0-9a-f]{3}|[0-9a-f]{6}|[0-9a-f]{8})$/i e.g ff0000ff = fully visible red
        - /^([0-9]{1,3},){3}[0-9]{1,3}$/ e.g 255,0,0,255 = fully visible red
1. Application:
    - Your code have to contain class named `Color`
    - Your code have to read file 'colors.txt' in the same directory
        - Format of file have to contain valid color value in each not empty line, rest have to be ignored
    - Your code have to parse arguments from CLI by itself, arguments can:
        - "--mode MODE" or "-m MODE" - Have to allow select mode
        - "..." - other arguments have to be used as values
    - MODEs:
        - "mix" - New color have to be average of values from given values (default mode if invalid or empty)
        - "lowest" - New color have to be created from the lowest from all of colors (independently r,g,b,a)
        - "highest" - New color have to be created from the highest from all of colors (independently r,g,b,a)
        - "mix-saturate" - Last color have to have new saturation equal to average of other colors
    - Your code have to use all colors, from file and from CLI
    - Your code have to print in terminal such informations about :
        - red - in range between 0 and 255
        - green - in range between 0 and 255
        - blue - in range between 0 and 255
        - alpha - in range between 0 and 255
        - hex - e.g #ff0000ff for red
        - hue - in range between 0 and 360
        - saturation - in range between 0 and 1
        - lightness - in range between 0 and 1
    - For invalid cases print some message