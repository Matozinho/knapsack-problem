#include <fmt/color.h>
#include <fmt/core.h>

#include <cxxopts.hpp>
#include <iostream>
#include <knapsack/knapsack.hpp>
#include <utils/assets.hpp>

int main(int argc, char **argv) {
  cxxopts::Options options("knapsack-solver",
                           "Solve the knapsack problem using brute force or greedy method");

  // clang-format off
  options.add_options()
    ("b,brute-force", "Solve the problem using brute force method", cxxopts::value<bool>()->default_value("false"))
    ("g,greedy-method", "Solve the problem using greedy method (default method)", cxxopts::value<bool>()->default_value("false"))
    ("f,file", "The file with the knapsack data", cxxopts::value<std::string>())
    ("h,help", "Print help");
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (!result.count("file")) {
    fmt::print(fmt::emphasis::bold | bg(fmt::color::red), "Any file provided\n");
    exit(1);
  }

  auto method = Knapsack::SolvingMethods::GREEDY;
  // the default is greedy method
  if (result.count("brute-force")) method = Knapsack::SolvingMethods::BRUTE_FORCE;

  Knapsack knapsack;

  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file(result["file"].as<std::string>());

  knapsack.solve(
      {.method = method, .capacity = capacity, .benefits = benefits, .weights = weights});
  exit(0);

  return 0;
}