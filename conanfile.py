from conans import ConanFile, CMake

class CFF(ConanFile):
  requires = "icu/68.2"
  generators = "cmake"