#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>

#include "../include/env_loader.hpp"

std::unordered_map<std::string, std::string>
loadEnvFile(const std::string &filepath) {
  std::unordered_map<std::string, std::string> env;
  std::string path = filepath;
  try {
    std::cout << "Current working directory: "
              << std::filesystem::current_path() << std::endl;

    std::ifstream file(path);

    if (!file.is_open()) {
      throw EnvFileException("Cannot open env file: " + path +
                             " (Current path: " + std::filesystem::current_path().string() + ")");
    }

    std::string line;

    while (std::getline(file, line)) {
      auto pos = line.find('=');
      if (pos == std::string::npos)
        continue;

      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + 1);
      env[key] = value;
    }

    return env;
  } catch (const std::ios_base::failure &e) {
    throw EnvFileException("File operation failed: " + std::string(e.what()));
  } catch (const std::exception &e) {
    throw EnvFileException("Unexpected error: " + std::string(e.what()));
  }
}