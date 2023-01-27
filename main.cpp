#include <filesystem>
#include "compare_pixels.h"

int main(int argc, char *argv[])
{
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    std::string filename1;
    std::string filename2;
    if (args.size() == 0)
    {
        std::cout << "Source filename: ";
        std::cin >> filename1;
        std::cout << "Compare filename: ";
        std::cin >> filename2;
    }
    else
    {
        filename1 = args[0];
        filename2 = args[1];
    }

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

    auto filename1Normal = std::filesystem::canonical(filename1);
    auto filename2Normal = std::filesystem::canonical(filename2);

    auto out = compareImages(filename1Normal.string(), filename2Normal.string(), true);
    std::cout << "Result:\n";
    std::cout << "Different pixels: " << out[0] << " \n";
    std::cout << "That's " << out[1] << "\% different image.\n";
    return 0;
}