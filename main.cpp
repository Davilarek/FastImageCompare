#include <filesystem>
#include "compare_pixels.h"

int main()
{
    std::string filename1;
    std::string filename2;
    std::cout << "Source filename: ";
    std::cin >> filename1;
    std::cout << "Compare filename: ";
    std::cin >> filename2;

    if (!std::filesystem::exists(filename1))
        return 1;
    if (!std::filesystem::exists(filename2))
        return 1;

    if (std::filesystem::is_directory(filename2))
    {
        for (const auto &dirEntry : std::filesystem::recursive_directory_iterator(filename2))
        {
            auto entryNormal = std::filesystem::canonical(dirEntry);
            auto filenameNormal = std::filesystem::canonical(filename1);
            if (entryNormal == filenameNormal)
            {
                continue;
            }

            auto out = compareImages(filename1, entryNormal.string(), true);
            std::cout << "Result:\n";
            std::cout << "Different pixels: " << out[0] << " \n";
            std::cout << "That's " << out[1] << "\% different image.\n";
        }
        return 0;
    }

    auto out = compareImages(filename1, filename2, true);
    std::cout << "Result:\n";
    std::cout << "Different pixels: " << out[0] << " \n";
    std::cout << "That's " << out[1] << "\% different image.\n";
    return 0;
}