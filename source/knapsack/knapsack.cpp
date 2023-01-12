#include <knapsack/knapsack.hpp>

Knapsack* Knapsack::solve(Knapsack::SolveProps props) {
  auto [method, capacity, benefits, weights] = props;

  this->capacity = capacity;
  this->benefits = benefits;
  this->weights = weights;

  if (method._to_integral() == Knapsack::SolvingMethods::BRUTE_FORCE)
    return brute_force();
  else if (method._to_integral() == Knapsack::SolvingMethods::GREEDY)
    return greedy();

  fmt::print(fmt::emphasis::bold | bg(fmt::color::red), "Method not implemented\n");

  exit(1);
}

Knapsack* Knapsack::brute_force() {
  // fmt::print("brute force method\n");

  // fmt::print("capacity: {}\n", this->capacity);
  // std::cout << "benefits: " << this->benefits << std::endl;
  // std::cout << "weights: " << this->weights << std::endl;
  return this;
}

Knapsack* Knapsack::greedy() {
  // fmt::print("greedy method\n");

  // fmt::print("capacity: {}\n", this->capacity);
  // std::cout << "benefits: " << this->benefits << std::endl;
  // std::cout << "weights: " << this->weights << std::endl;
  return this;
}