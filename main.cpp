#include <filesystem>
#include <string>
#include "compare_pixels.h"

void readLine(char *outputHere)
{
    char tmp[101];
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    strncpy(outputHere, tmp, 100);
    outputHere[100] = '\0';
}

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
        char filename1a[101];
        char filename2a[101];
        printf("Source filename: ");
        readLine(filename1a);
        // scanf("%s",filename1);
        // char tmp1[101];
        // scanf("%100s", tmp1);
        // filename1 = tmp1;
        printf("Compare filename: ");
        readLine(filename2a);
        filename1 = filename1a;
        filename2 = filename2a;
        // std::cin >> filename2;
        // char tmp2[101];
        // scanf("%100s", tmp2);
        // filename2 = tmp2;
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
            printf("Result:\n");
            printf("Different pixels: %d \n", out.pixels);
            printf("That's %f%% different image.\n", out.percent);
        }
        return 0;
    }

    auto filename1Normal = std::filesystem::canonical(filename1);
    auto filename2Normal = std::filesystem::canonical(filename2);

    auto out = compareImages(filename1Normal.string(), filename2Normal.string(), true);
    printf("Result:\n");
    printf("Different pixels: %d \n", out.pixels);
    printf("That's %f%% different image.\n", out.percent);
    return 0;
}