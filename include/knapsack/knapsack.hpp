#pragma once

#include <better-enums/enum.h>
#include <bits/stdc++.h>
#include <fmt/color.h>
#include <fmt/core.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

BETTER_ENUM(_SolvingMethods, int, BRUTE_FORCE, GREEDY);

class Knapsack {
private:
  std::string file_name;

  uint32_t capacity;
  std::vector<uint32_t> benefits;
  std::vector<uint32_t> weights;

  uint32_t total_benefit;

  Knapsack* brute_force();
  Knapsack* greedy();

public:
  typedef _SolvingMethods SolvingMethods;
  struct SolveProps {
    SolvingMethods method;

    uint32_t capacity;
    std::vector<uint32_t> benefits;
    std::vector<uint32_t> weights;
  };

  Knapsack() = default;
  ~Knapsack() = default;

  Knapsack* solve(SolveProps props = {
                      .method = SolvingMethods::BRUTE_FORCE,
                  });
};

template <typename S> std::ostream& operator<<(std::ostream& os, const std::vector<S>& vector) {
  for (auto element : vector) {
    os << element << " ";
  }
  return os;
}