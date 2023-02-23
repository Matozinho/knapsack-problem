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

std::tuple<uint32_t, uint32_t> Knapsack::recursive(uint32_t n, uint32_t w,
                                                   std::vector<uint32_t> weights,
                                                   std::vector<uint32_t> values,
                                                   uint32_t currentItem, uint32_t currentWeight) {
  // base case -> the end of the items
  if (currentItem == n) return std::make_tuple(currentWeight, 0);

  // if the current item weight is greater than the capacity, skip it
  if (currentWeight + weights[currentItem] > w)
    return this->recursive(n, w, weights, values, currentItem + 1, currentWeight);

  // if the current item weight is less than the capacity, check if it's better to take it or not
  auto [weight1, benefit1] = this->recursive(n, w, weights, values, currentItem + 1,
                                             currentWeight + weights[currentItem]);
  benefit1 += values[currentItem];

  auto [weight2, benefit2] = this->recursive(n, w, weights, values, currentItem + 1, currentWeight);

  uint32_t maxBenefit = std::max(benefit1, benefit2);
  return maxBenefit == benefit1 ? std::make_tuple(weight1, benefit1)
                                : std::make_tuple(weight2, benefit2);
}

Knapsack* Knapsack::iterative() {
  uint32_t n = weights.size();

  uint32_t bestValue = 0;
  uint32_t bestWeight = 0;

  for (uint32_t i = 0; i < std::pow(2, n); i++) {
    uint32_t currentWeight = 0;
    uint32_t currentValue = 0;

    for (uint32_t j = 0; j < n; j++) {
      if (i & (1 << j)) {
        currentWeight += this->weights[j];
        currentValue += this->benefits[j];
      }
    }

    if ((currentValue > bestValue) && (currentWeight <= this->capacity)) {
      bestValue = currentValue;
      bestWeight = currentWeight;
    }
  }

  this->total_benefit = bestValue;
  this->total_weight = bestWeight;

  return this;
}

Knapsack* Knapsack::brute_force() {
  /// uncomment it for recursive solution
  // auto [totalWeight, totalBenefit]
  //     = this->recursive(this->benefits.size(), this->capacity, this->weights, this->benefits, 0, 0);

  // this->total_benefit = totalBenefit;
  // this->total_weight = totalWeight;

  this->iterative();

  return this;
}

Knapsack* Knapsack::greedy() {
  uint32_t w = this->capacity;
  std::vector<uint32_t> W(this->weights);
  std::vector<uint32_t> V(this->benefits);
  std::vector<uint32_t> x(this->weights.size(), 0);

  // v[i] = V[i] / W[i]
  std::vector<float_t> v(this->benefits.size(), 0);
  std::transform(V.begin(), V.end(), W.begin(), v.begin(), std::divides<float>());

  this->total_weight = 0;
  uint32_t* P = &this->total_weight;
  this->total_benefit = 0;

  while (*P < w && v.size() > 0) {
    int idx = std::distance(
        v.begin(), std::max_element(v.begin(), v.end()));  // get the index of the max element

    int32_t a = std::min(W[idx], w - *P);

    if (a == W[idx]) {
      x[idx] = 1;  // TODO: validate how to get the item idx
      *P += a;
      this->total_benefit += V[idx];
    }

    // remove o elemento escolhido
    v.erase(v.begin() + idx);
    V.erase(V.begin() + idx);
    W.erase(W.begin() + idx);
  }

  this->selected_items = x;

  return this;
}