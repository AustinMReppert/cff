#include <unicode/unistr.h>
#include "FileUtils.h"

auto CFF::getLength(std::ifstream& file) {
  const auto ref = file.tellg();
  file.seekg(0, std::ios::end);
  const auto length = file.tellg();
  file.seekg(ref);
  return length;
}

icu::UnicodeString CFF::load(const fs::path& path) {
  std::ifstream file(path, std::ifstream::binary | std::ifstream::in);
  if(!file) {
    throw std::runtime_error("File not found: " + std::string(path));
  }
  const auto length = getLength(file);
  auto content = std::string(length.operator+(0), ' ');
  file.read(content.data(), length);
  file.close();
  return {content.c_str(), "utf-8"};
}