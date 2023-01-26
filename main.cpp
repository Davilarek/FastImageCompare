#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <vector>

std::vector<std::string> compareImages(std::string filename1, std::string filename2)
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
            std::cout << "Failed to load image: " << path << std::endl;
            continue;
        }
        imagesData.push_back(std::vector<unsigned char>(data, data + width * height * nrChannels));
        imagesDim.emplace_back(width, height);
        stbi_image_free(data);
    }

    // // for (int i = 0; i < imagesData.size(); ++i)
    // // {
    // //     std::cout << "image: " << imagesPaths[i] << " with dimension: " << imagesDim[i].first << "x" << imagesDim[i].second << std::endl;
    // //     // You can access the pixels of i-th image by imagesData[i]
    // //     std::cout << "" << imagesData[i][0] << " " << imagesData[i][1] << " " << imagesData[i][2] << std::endl;
    // // }
    // // for (int i = 0; i < imagesData.size(); ++i)
    // // {
    // //     std::cout << "image: " << imagesPaths[i] << " with dimension: " << imagesDim[i].first << "x" << imagesDim[i].second << std::endl;
    // //     int width = imagesDim[i].first;
    // //     int height = imagesDim[i].second;
    // //     int nrChannels = 3;
    // //     std::cout << "Printing pixels of image: " << imagesPaths[i] << std::endl;
    // //     for (int y = 0; y < height; ++y)
    // //     {
    // //         for (int x = 0; x < width; ++x)
    // //         {
    // //             int index = (y * width + x) * nrChannels;
    // //             unsigned char red = imagesData[i][index];
    // //             unsigned char green = imagesData[i][index + 1];
    // //             unsigned char blue = imagesData[i][index + 2];
    // //             std::cout << "Pixel (" << x << ", " << y << ") has RGB values: " << (int)red << ", " << (int)green << ", " << (int)blue << std::endl;
    // //         }
    // //     }
    // // }
    // for (int i = 0; i < imagesData.size(); ++i)
    // {
    //     std::cout << "image: " << imagesPaths[i] << " with dimension: " << imagesDim[i].first << "x" << imagesDim[i].second << std::endl;
    //     int width = imagesDim[i].first;
    //     int height = imagesDim[i].second;
    //     int nrChannels = 4;
    //     std::cout << "Printing pixels of image: " << imagesPaths[i] << std::endl;
    //     for (int y = 0; y < height; ++y)
    //     {
    //         for (int x = 0; x < width; ++x)
    //         {
    //             int index = (y * width + x) * nrChannels;
    //             unsigned char red = imagesData[i][index];
    //             unsigned char green = imagesData[i][index + 1];
    //             unsigned char blue = imagesData[i][index + 2];
    //             unsigned char alpha = imagesData[i][index + 3];
    //             if (nrChannels == 4)
    //             {
    //                 std::cout << "Pixel (" << x << ", " << y << ") has RGBA values: " << (int)red << ", " << (int)green << ", " << (int)blue << ", " << (int)alpha << std::endl;
    //             }
    //             else
    //             {
    //                 alpha = 255; // Set alpha value to 255 if the image has no alpha channel
    //                 std::cout << "Pixel (" << x << ", " << y << ") has RGB values: " << (int)red << ", " << (int)green << ", " << (int)blue << std::endl;
    //             }
    //         }
    //     }
    // }

    int selectedImageIndex = 0;

    std::cout << "You have selected image: " << imagesPaths[selectedImageIndex] << std::endl;

    std::vector<unsigned char> sourceImageData = imagesData[selectedImageIndex];
    std::pair<int, int> sourceImageDim = imagesDim[selectedImageIndex];
    int diffPixels = 0;
    for (int i = 0; i < imagesData.size(); ++i)
    {
        if (i == selectedImageIndex)
        {
            continue;
        }

        std::cout << "Comparing image: " << imagesPaths[i] << " with source image: " << imagesPaths[selectedImageIndex] << std::endl;

        int width = imagesDim[i].first;
        int height = imagesDim[i].second;
        int nrChannels = 4;

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int index = (y * width + x) * nrChannels;

                unsigned char red1 = sourceImageData[index];
                unsigned char green1 = sourceImageData[index + 1];
                unsigned char blue1 = sourceImageData[index + 2];
                unsigned char alpha1 = sourceImageData[index + 3];

                unsigned char red2 = imagesData[i][index];
                unsigned char green2 = imagesData[i][index + 1];
                unsigned char blue2 = imagesData[i][index + 2];
                unsigned char alpha2 = imagesData[i][index + 3];

                if (red1 != red2 || green1 != green2 || blue1 != blue2 || alpha1 != alpha2)
                {
                    // std::cout << "Pixel (" << x << ", " << y << ") is different in image: " << imagesPaths[i] << std::endl;
                    diffPixels += 1;
                }
            }
        }
    }
    // std::cout << "Result:\n";
    // std::cout << "Different pixels: " << diffPixels << " \n";
    // std::cout << (float)diffPixels / ((float)(imagesDim[1].first * imagesDim[1].second))  << std::endl;
    // std::cout << "That's " << (float)diffPixels / ((float)(imagesDim[1].first * imagesDim[1].second)) * 100 << "\% different image.\n";

    std::vector<std::string> out;
    out.push_back(std::to_string(diffPixels));
    out.push_back(std::to_string((float)diffPixels / ((float)(imagesDim[1].first * imagesDim[1].second)) * 100));
    return out;
}

int main()
{
    // std::vector<std::vector<unsigned char>> imagesData;
    // std::vector<std::pair<int, int>> imagesDim;
    // std::vector<std::string> imagesPaths = {"test.png", "test3.png"};

    // for (const auto &path : imagesPaths)
    // {
    //     int width, height, nrChannels;
    //     unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    //     if (data == nullptr)
    //     {
    //         std::cout << "Failed to load image: " << path << std::endl;
    //         continue;
    //     }
    //     imagesData.push_back(std::vector<unsigned char>(data, data + width * height * nrChannels));
    //     imagesDim.emplace_back(width, height);
    //     stbi_image_free(data);
    // }

    // // // for (int i = 0; i < imagesData.size(); ++i)
    // // // {
    // // //     std::cout << "image: " << imagesPaths[i] << " with dimension: " << imagesDim[i].first << "x" << imagesDim[i].second << std::endl;
    // // //     // You can access the pixels of i-th image by imagesData[i]
    // // //     std::cout << "" << imagesData[i][0] << " " << imagesData[i][1] << " " << imagesData[i][2] << std::endl;
    // // // }
    // // // for (int i = 0; i < imagesData.size(); ++i)
    // // // {
    // // //     std::cout << "image: " << imagesPaths[i] << " with dimension: " << imagesDim[i].first << "x" << imagesDim[i].second << std::endl;
    // // //     int width = imagesDim[i].first;
    // // //     int height = imagesDim[i].second;
    // // //     int nrChannels = 3;
    // // //     std::cout << "Printing pixels of image: " << imagesPaths[i] << std::endl;
    // // //     for (int y = 0; y < height; ++y)
    // // //     {
    // // //         for (int x = 0; x < width; ++x)
    // // //         {
    // // //             int index = (y * width + x) * nrChannels;
    // // //             unsigned char red = imagesData[i][index];
    // // //             unsigned char green = imagesData[i][index + 1];
    // // //             unsigned char blue = imagesData[i][index + 2];
    // // //             std::cout << "Pixel (" << x << ", " << y << ") has RGB values: " << (int)red << ", " << (int)green << ", " << (int)blue << std::endl;
    // // //         }
    // // //     }
    // // // }
    // // for (int i = 0; i < imagesData.size(); ++i)
    // // {
    // //     std::cout << "image: " << imagesPaths[i] << " with dimension: " << imagesDim[i].first << "x" << imagesDim[i].second << std::endl;
    // //     int width = imagesDim[i].first;
    // //     int height = imagesDim[i].second;
    // //     int nrChannels = 4;
    // //     std::cout << "Printing pixels of image: " << imagesPaths[i] << std::endl;
    // //     for (int y = 0; y < height; ++y)
    // //     {
    // //         for (int x = 0; x < width; ++x)
    // //         {
    // //             int index = (y * width + x) * nrChannels;
    // //             unsigned char red = imagesData[i][index];
    // //             unsigned char green = imagesData[i][index + 1];
    // //             unsigned char blue = imagesData[i][index + 2];
    // //             unsigned char alpha = imagesData[i][index + 3];
    // //             if (nrChannels == 4)
    // //             {
    // //                 std::cout << "Pixel (" << x << ", " << y << ") has RGBA values: " << (int)red << ", " << (int)green << ", " << (int)blue << ", " << (int)alpha << std::endl;
    // //             }
    // //             else
    // //             {
    // //                 alpha = 255; // Set alpha value to 255 if the image has no alpha channel
    // //                 std::cout << "Pixel (" << x << ", " << y << ") has RGB values: " << (int)red << ", " << (int)green << ", " << (int)blue << std::endl;
    // //             }
    // //         }
    // //     }
    // // }

    // int selectedImageIndex;
    // std::cin >> selectedImageIndex;

    // // Validate user input
    // while (selectedImageIndex < 0 || selectedImageIndex >= imagesData.size())
    // {
    //     std::cin >> selectedImageIndex;
    // }

    // std::cout << "You have selected image: " << imagesPaths[selectedImageIndex] << std::endl;

    // std::vector<unsigned char> sourceImageData = imagesData[selectedImageIndex];
    // std::pair<int, int> sourceImageDim = imagesDim[selectedImageIndex];
    // int diffPixels = 0;
    // for (int i = 0; i < imagesData.size(); ++i)
    // {
    //     if (i == selectedImageIndex)
    //     {
    //         continue;
    //     }

    //     std::cout << "Comparing image: " << imagesPaths[i] << " with source image: " << imagesPaths[selectedImageIndex] << std::endl;

    //     int width = imagesDim[i].first;
    //     int height = imagesDim[i].second;
    //     int nrChannels = 4;

    //     for (int y = 0; y < height; ++y)
    //     {
    //         for (int x = 0; x < width; ++x)
    //         {
    //             int index = (y * width + x) * nrChannels;

    //             unsigned char red1 = sourceImageData[index];
    //             unsigned char green1 = sourceImageData[index + 1];
    //             unsigned char blue1 = sourceImageData[index + 2];
    //             unsigned char alpha1 = sourceImageData[index + 3];

    //             unsigned char red2 = imagesData[i][index];
    //             unsigned char green2 = imagesData[i][index + 1];
    //             unsigned char blue2 = imagesData[i][index + 2];
    //             unsigned char alpha2 = imagesData[i][index + 3];

    //             if (red1 != red2 || green1 != green2 || blue1 != blue2 || alpha1 != alpha2)
    //             {
    //                 std::cout << "Pixel (" << x << ", " << y << ") is different in image: " << imagesPaths[i] << std::endl;
    //                 diffPixels += 1;
    //             }
    //         }
    //     }
    // }
    // std::cout << "Result:\n";
    // std::cout << "Different pixels: " << diffPixels << " \n";
    // // std::cout << (float)diffPixels / ((float)(imagesDim[1].first * imagesDim[1].second))  << std::endl;
    // std::cout << "That's " << (float)diffPixels / ((float)(imagesDim[1].first * imagesDim[1].second)) * 100 << "\% different image.\n";

    auto out = compareImages("test.png", "test3.png");
    std::cout << "Result:\n";
    std::cout << "Different pixels: " << out[0] << " \n";
    std::cout << "That's " << out[1] << "\% different image.\n";
    return 0;
}