#include <iostream>

int main()
{
    const int imageWidth = 3;
    const int imageHeight = 2;
    const int maxColor = 255;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n" << maxColor << "\n";
    std::cout << "255 0 0 0 255 0 0 0 255\n255 255 0 255 255 255 0 0 0\n";

    return 0;
}

