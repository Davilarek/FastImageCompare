#include <filesystem>
#include "compare_pixels.h"

int main()
{
    std::string filename1;
    std::string filename2;
    std::cin >> filename1;
    std::cin >> filename2;

    if (!std::filesystem::exists(filename1))
        return 1;
    if (!std::filesystem::exists(filename2))
        return 1;

    auto out = compareImages(filename1, filename2);
    std::cout << "Result:\n";
    std::cout << "Different pixels: " << out[0] << " \n";
    std::cout << "That's " << out[1] << "\% different image.\n";
    return 0;
}