#include <iostream>
#include <knapsack/main.hpp>
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

int main(int argc, char **argv)
{
  spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
  cxxopts::Options options("knapsack-solver", "Solve the knapsack problem using brute force or greedy method");

  // clang-format off
  options.add_options()
    ("b,brute-force", "Solve the problem using brute force method", cxxopts::value<bool>()->default_value("false"))
    ("g,greedy-method", "Solve the problem using greedy method", cxxopts::value<bool>()->default_value("false"))
    ("f,file", "The file with the knapsack data", cxxopts::value<std::string>())
    ("h,help", "Print help");
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (result.count("file"))
    spdlog::info("Using file: {}", result["file"].as<std::string>());
  else
  {
    spdlog::error("No file provided");
    exit(1);
  }

  if (result.count("brute-force"))
  {
    Kanpsack::brute_force();
    exit(0);
  }

  if (result.count("greedy-method"))
  {
    Kanpsack::greedy();
    exit(0);
  }

  return 0;
}