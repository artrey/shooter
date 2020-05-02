#include "fs.h"

fs::path findFolder(fs::path const& path, std::string const& folderName)
{
    for (auto const& entry : fs::directory_iterator(path))
    {
        if (!entry.is_directory()) continue;
        if (entry.path().filename() == folderName)
        {
            return entry.path();
        }
    }
    return {};
}
