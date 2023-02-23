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
// clang-format off
Knapsack* Knapsack::iterative() {                           // O(n * 2^n)
  uint32_t n = weights.size();                              // 1

  uint32_t bestValue = 0;                                   // 1   
  uint32_t bestWeight = 0;                                  // 1

  for (uint32_t i = 0; i < std::pow(2, n); i++) {           // 2^n    
    uint32_t currentWeight = 0;                             // 2^n
    uint32_t currentValue = 0;                              // 2^n

    for (uint32_t j = 0; j < n; j++) {                      // 2^n * n
      if (i & (1 << j)) {                                   // 2^n * n + 3
        currentWeight += this->weights[j];                  // 2^n * n + 3
        currentValue += this->benefits[j];                  // 2^n * n + 3
      }
    }

    if ((currentValue > bestValue) && (currentWeight <= this->capacity)) {      // 2^n * n + 4
      bestValue = currentValue;                                                 // 2^n * n
      bestWeight = currentWeight;                                               // 2^n * n
    }
  }

  this->total_benefit = bestValue;                                             // 1
  this->total_weight = bestWeight;                                             // 1

  return this;
}
// clang-format on

Knapsack* Knapsack::brute_force() {
  /// uncomment it for recursive solution
  // auto [totalWeight, totalBenefit]
  //     = this->recursive(this->benefits.size(), this->capacity, this->weights, this->benefits, 0,
  //     0);

  // this->total_benefit = totalBenefit;
  // this->total_weight = totalWeight;

  this->iterative();

  return this;
}

// clang-format off
Knapsack* Knapsack::greedy() {                                // O(n²+n)    
  uint32_t w = this->capacity;                                // 1
  std::vector<uint32_t> W(this->weights);                     // n
  std::vector<uint32_t> V(this->benefits);                    // n

  // v = V / W
  std::vector<float_t> v(this->benefits.size(), 0);           // n+1
  std::transform(                                             // 4
    V.begin(),                                                
    V.end(),                                                                  
    W.begin(),                                                
    v.begin(),                                                
    std::divides<float>()                                     // n
  );                                                         

  this->total_weight = 0;                                     // 1
  uint32_t* P = &this->total_weight;                          // 2
  this->total_benefit = 0;                                    // 1

  while (*P < w && v.size() > 0) {                            // n
    /* get the index of the max element */
    int idx = std::distance(                                  // (n²+n)/2
      v.begin(),
      std::max_element(                                       // (n²+n)/2
        v.begin(),
        v.end()
      )
    );

    int32_t a = std::min(W[idx], w - *P);                     // 5n

    if (a == W[idx]) {                                        // 2n
      *P += a;                                                // 2n
      this->total_benefit += V[idx];                          // 2n
    }

    // remove o elemento escolhido
    v.erase(v.begin() + idx);                                 // 3n
    V.erase(V.begin() + idx);                                 // 3n
    W.erase(W.begin() + idx);                                 // 3n
  }

  return this;
}
// clang-format off
