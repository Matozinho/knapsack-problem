#include <gtest/gtest.h>

#include <knapsack/knapsack.hpp>
#include <utils/assets.hpp>

// TODO: Create a validator to match wich items was selected
TEST(KNAPSACK_SOLVING, brute_force_1) {
  Knapsack knapsack;
  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file("assets/test/Mochila1.txt");

  knapsack.solve({.method = Knapsack::SolvingMethods::BRUTE_FORCE,
                  .capacity = capacity,
                  .benefits = benefits,
                  .weights = weights});

  EXPECT_EQ(knapsack.get_total_benefit(), 36);
  EXPECT_EQ(knapsack.get_total_weight(), 20);
}

TEST(KNAPSACK_SOLVING, greedy_1) {
  Knapsack knapsack;
  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file("assets/test/Mochila1.txt");

  knapsack.solve({.method = Knapsack::SolvingMethods::GREEDY,
                  .capacity = capacity,
                  .benefits = benefits,
                  .weights = weights});

  // Benefit = 18 + 18 = 36
  // Weight  = 10 + 10 = 20
  // items   = 1 | 2 = {0, 1, 1, 0}

  EXPECT_EQ(knapsack.get_total_benefit(), 36);
  EXPECT_EQ(knapsack.get_total_weight(), 20);
}

TEST(KNAPSACK_SOLVING, brute_force_2) {
  Knapsack knapsack;
  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file("assets/test/Mochila2.txt");

  knapsack.solve({.method = Knapsack::SolvingMethods::BRUTE_FORCE,
                  .capacity = capacity,
                  .benefits = benefits,
                  .weights = weights});

  EXPECT_EQ(knapsack.get_total_benefit(), 189);
  EXPECT_EQ(knapsack.get_total_weight(), 104);
}

TEST(KNAPSACK_SOLVING, greedy_2) {
  Knapsack knapsack;
  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file("assets/test/Mochila2.txt");

  knapsack.solve({.method = Knapsack::SolvingMethods::GREEDY,
                  .capacity = capacity,
                  .benefits = benefits,
                  .weights = weights});

  // Benefit = 42 + 12 + 37 + 48 + 3 + 3 + 20 + 13 = 178
  // Weight  = 9  + 4  + 17 + 29 + 2 + 2 + 14 + 25 = 102
  // items   = 4  | 8  | 9  | 3  | 0 | 6 | 7  | 5 = {1, 0, 0, 1, 1, 1, 1, 1, 1, 1}

  EXPECT_EQ(knapsack.get_total_benefit(), 178);
  EXPECT_EQ(knapsack.get_total_weight(), 102);
}

TEST(KNAPSACK_SOLVING, brute_force_3) {
  Knapsack knapsack;
  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file("assets/test/Mochila3.txt");

  knapsack.solve({.method = Knapsack::SolvingMethods::BRUTE_FORCE,
                  .capacity = capacity,
                  .benefits = benefits,
                  .weights = weights});

  EXPECT_EQ(knapsack.get_total_benefit(), 51);
  EXPECT_EQ(knapsack.get_total_weight(), 20);
}

TEST(KNAPSACK_SOLVING, greedy_3) {
  Knapsack knapsack;
  auto [capacity, benefits, weights]
      = utils::assets::get_params_from_file("assets/test/Mochila3.txt");

  knapsack.solve({.method = Knapsack::SolvingMethods::GREEDY,
                  .capacity = capacity,
                  .benefits = benefits,
                  .weights = weights});

  EXPECT_EQ(knapsack.get_total_benefit(), 50);
  EXPECT_EQ(knapsack.get_total_weight(), 19);
}