#include <gtest/gtest.h>

#include <knapsack/main.hpp>

TEST(Kanpsack, brute_force_exists)
{
  Kanpsack::brute_force();

  SUCCEED();
}

TEST(Kanpsack, greedy_exists)
{
  Kanpsack::greedy();

  SUCCEED();
}
