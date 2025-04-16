#pragma once

#include <map>
#include <string>

class EnvFileException : public std::runtime_error {
public:
  explicit EnvFileException(const std::string& message)
      : std::runtime_error(message) {}
};

std::unordered_map<std::string, std::string>
loadEnvFile(const std::string &filepath);