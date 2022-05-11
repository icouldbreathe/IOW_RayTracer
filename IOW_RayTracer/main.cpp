#include <iostream>

int main()
{
    const int imageWidth = 512;
    const int imageHeight = 512;
    const int maxColor = 255;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n" << maxColor << "\n";
    
    for (int i = imageHeight-1; i >= 0; --i)
    {
        for (int j = 0; j < imageWidth; ++j)
        {
            // Scales the rgb values across the image
            // Red from left to right 0-255, Green from top to bottom 255-0
            // Blue tint of 0.25
            auto r = double(j) / (imageWidth-1);
            auto g = double(i) / (imageHeight-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << "\n";
        }
    }
    
    return 0;
}

