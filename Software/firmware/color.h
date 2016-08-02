#pragma once

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Color():
        red{0}, green{0}, blue{0}
    {}
    Color(int r, int g, int b)
        : red{(uint8_t)r}, green{(uint8_t)g}, blue{(uint8_t)b}
    {}
};

