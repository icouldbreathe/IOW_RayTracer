#include "color.h"
#include "vec3.h"

#include <iostream>

int main()
{
    const int imageWidth = 512;
    const int imageHeight = 512;
    const int maxColor = 255;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n" << maxColor << "\n";
    
    for (int i = imageHeight-1; i >= 0; --i)
    {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < imageWidth; ++j)
        {
            // Red from left to right 0-255, Green from top to bottom 255-0, Blue tint of 0.25
            color pixelColor(double(j)/(imageWidth-1), double(i)/(imageHeight-1), 0.25);
            writeColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone.\n";
    
    return 0;
}

