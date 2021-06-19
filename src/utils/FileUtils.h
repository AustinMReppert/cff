#ifndef CFF_FILEUTILS_H
#define CFF_FILEUTILS_H

#include "StringUtils.h"

#include <unicode/unistr.h>

#include <memory>
#include <filesystem>
#include <fstream>
#include <cstdio>

namespace fs = std::filesystem;

namespace CFF {

  [[nodiscard]] auto getLength(std::ifstream& file);

  icu::UnicodeString load(const fs::path& path);

}

#endif
