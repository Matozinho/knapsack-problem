#pragma once

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

namespace utils::assets {
  inline std::vector<int32_t> get_size_of_assets(const std::string& path) {
    std::vector<int32_t> sizes;

    // Read the name of the files from path
    std::filesystem::path p(path);
    for (const auto& entry : std::filesystem::directory_iterator(p)) {
      // Extract only the number from the name of the file
      std::string name = entry.path().filename().string();
      std::regex re("[0-9]+");
      std::smatch match;
      std::regex_search(name, match, re);

      // Convert the number to int32_t and add it to the vector
      int32_t size = std::stoi(match[0]);
      sizes.push_back(size);
    }

    std::ranges::sort(sizes);

    return sizes;
  }

  template <typename R, typename... Args> std::function<R(Args...)> memo(R (*fn)(Args...)) {
    std::map<std::tuple<Args...>, R> table;
    return [fn, table](Args... args) mutable -> R {
      auto argt = std::make_tuple(args...);
      auto memoized = table.find(argt);
      if (memoized == table.end()) {
        auto result = fn(args...);
        table[argt] = result;
        return result;
      } else {
        return memoized->second;
      }
    };
  }

  inline std::tuple<uint32_t, std::vector<uint32_t>, std::vector<uint32_t>> get_params_from_file(
      std::string fileName) {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) throw std::runtime_error("Unable to open file");

    std::string line;
    std::stringstream lineStream;

    getline(inputFile, line);
    auto capacity = std::stoi(line);

    getline(inputFile, line);
    lineStream = std::stringstream(line);
    auto benefits = std::vector<uint32_t>(std::istream_iterator<uint32_t>(lineStream), {});

    getline(inputFile, line);
    lineStream = std::stringstream(line);
    auto weights = std::vector<uint32_t>(std::istream_iterator<uint32_t>(lineStream), {});

    inputFile.close();

    return {capacity, benefits, weights};
  }
}  // namespace utils::assets
