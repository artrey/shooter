#ifndef SHOOTER_FS_H
#define SHOOTER_FS_H

#include <filesystem>

namespace fs = std::filesystem;

fs::path findFolder(fs::path const& path, std::string const& folderName);

#endif //SHOOTER_FS_H
