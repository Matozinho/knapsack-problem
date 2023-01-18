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
  uint32_t total_weight;
  std::vector<uint32_t> selected_items;

  Knapsack* brute_force();
  std::tuple<uint32_t, uint32_t> recursive(uint32_t n, uint32_t w, std::vector<uint32_t> weights,
                                           std::vector<uint32_t> values, uint32_t currentItem,
                                           uint32_t currentWeight);
  Knapsack* greedy();

public:
  typedef _SolvingMethods SolvingMethods;
  struct SolveProps {
    SolvingMethods method;

    uint32_t capacity;
    std::vector<uint32_t> benefits;
    std::vector<uint32_t> weights;
  };

  // params getters
  uint32_t get_capacity() const { return this->capacity; }
  std::vector<uint32_t> get_benefits() const { return this->benefits; }
  std::vector<uint32_t> get_weights() const { return this->weights; }

  // solution getters
  uint32_t get_total_benefit() const { return this->total_benefit; }
  uint32_t get_total_weight() const { return this->total_weight; }
  std::vector<uint32_t> get_selected_items() const { return this->selected_items; }

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