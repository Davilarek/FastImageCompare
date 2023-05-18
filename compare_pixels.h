#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
// #include <iostream>
#include <vector>

double reversePercentage(double percentage)
{
    return 100.0 - percentage;
}

struct CompareResult
{
    float percent;
    int pixels;
};

bool ColorsAreClose(int r1, int g1, int b1, int r2, int g2, int b2, int threshold = 50)
{
    int rDist = std::abs(r1 - r2),
        gDist = std::abs(g1 - g2),
        bDist = std::abs(b1 - b2);
    // return (r * r + g * g + b * b) <= threshold * threshold;
    if (rDist + gDist + bDist > threshold)
        return false;
    return true;
}

/// @brief Compares image pixel by pixel. Outputs results.
/// @param filename1 Source filename
/// @param filename2 Compare filename
/// @param enableLog Enable info log
/// @return Vector with results. First element: different pixel count, Second element: difference percent
CompareResult compareImages(std::string filename1, std::string filename2, bool enableLog)
{
    std::vector<std::vector<unsigned char>> imagesData;
    std::vector<std::pair<int, int>> imagesDim;
    std::vector<std::string> imagesPaths = {filename1, filename2};

    for (const auto &path : imagesPaths)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data == nullptr)
        {
            if (enableLog)
                printf("Failed to load image: %s\n", path.c_str());
            continue;
        }
        imagesData.push_back(std::vector<unsigned char>(data, data + width * height * nrChannels));
        imagesDim.emplace_back(width, height);
        stbi_image_free(data);
    }

    int selectedImageIndex = 0;
    if (enableLog)
        printf("You have selected image: %s\n", imagesPaths[selectedImageIndex].c_str());

    std::vector<unsigned char> sourceImageData = imagesData[selectedImageIndex];
    std::pair<int, int> sourceImageDim = imagesDim[selectedImageIndex];
    int diffPixels = 0;
    for (int i = 0; i < imagesData.size(); ++i)
    {
        if (i == selectedImageIndex)
        {
            continue;
        }
        if (enableLog)
            printf("Comparing image: %s with source image: %s\n", imagesPaths[i].c_str(), imagesPaths[selectedImageIndex].c_str());

        int width = std::min(sourceImageDim.first, imagesDim[i].first);
        int height = std::min(sourceImageDim.second, imagesDim[i].second);
        // int nrChannels = 4;
        int nrChannels = 3;

        // for (auto i : imagesData[i])
        //     std::cout << std::to_string(i) << ' ';
        // for (auto i : sourceImageData)
        //     std::cout << std::to_string(i) << ' ';

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int index = (y * width + x) * nrChannels;

                unsigned char red1 = sourceImageData[index];
                unsigned char green1 = sourceImageData[index + 1];
                unsigned char blue1 = sourceImageData[index + 2];
                // unsigned char alpha1 = sourceImageData[index + 3];

                unsigned char red2 = imagesData[i][index];
                unsigned char green2 = imagesData[i][index + 1];
                unsigned char blue2 = imagesData[i][index + 2];
                // unsigned char alpha2 = imagesData[i][index + 3];

                // Color colors1 = Color();
                // colors1.R = red1;
                // colors1.G = green1;
                // colors1.B = blue1;
                // Color colors2 = Color();
                // colors2.R = red2;
                // colors2.G = green2;
                // colors2.B = blue2;

                bool matchesAnyColor = (red1 != red2 || green1 != green2 || blue1 != blue2);
                bool matchesClose = ColorsAreClose((int)red1, (int)green1, (int)blue1, (int)red2, (int)green2, (int)blue2, 50);
                // if (red1 != red2 || green1 != green2 || blue1 != blue2 || alpha1 != alpha2)
                // if (red1 != red2 || green1 != green2 || blue1 != blue2)
                // printf("Pixel (%d, %d) has RGBA values: %d, %d, %d\n", x, y, (int)red1, (int)green1, (int)blue1);
                // printf("Pixel (%d, %d) has RGBA values: %d, %d, %d\n", x, y, (int)red2, (int)green2, (int)blue2);
                if (matchesAnyColor || !matchesClose)
                {
                    // std::cout << "Pixel (" << x << ", " << y << ") is different in image: " << imagesPaths[i] << std::endl;
                    // std::cout << "Pixel (" << x << ", " << y << ") has RGBA values: " << (int)red1 << ", " << (int)green1 << ", " << (int)blue1 << ", " << (int)alpha1 << std::endl;
                    // std::cout << "Pixel (" << x << ", " << y << ") has RGBA values: " << (int)red2 << ", " << (int)green2 << ", " << (int)blue2 << ", " << (int)alpha2 << std::endl;
                    diffPixels += 1;
                }
                else 
                ;
            }
        }
    }

    // std::vector<std::string> out;
    float percent = (float)diffPixels / ((float)(imagesDim[1].first * imagesDim[1].second)) * 100;
    // out.push_back(std::to_string(diffPixels));
    // out.push_back(std::to_string(reversePercentage(percent)));
    CompareResult out = CompareResult();
    out.pixels = diffPixels;
    out.percent = reversePercentage(percent);
    return out;
}