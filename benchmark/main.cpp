#include <benchmark/benchmark.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <knapsack/knapsack.hpp>
#include <ranges>
#include <utils/assets.hpp>

const std::vector<int32_t> filesRanges = utils::assets::get_size_of_assets("assets");

static void custom_arguments(benchmark::internal::Benchmark *b) {
  auto elements = utils::assets::get_size_of_assets("assets");

  for (auto size : elements) b->Args({size});
}

template <typename... Args> static void BM_BruteForce(benchmark::State &state, Args &&...args) {
  auto args_tuple = std::make_tuple(std::move(args)...);

  Knapsack solving_knapsack;
  auto memoGetParams = utils::assets::memo(utils::assets::get_params_from_file);

  for (auto _ : state) {
    std::string fileName = fmt::format("assets/{}{}.txt", std::get<0>(args_tuple), state.range(0));
    auto [capacity, benefits, weights] = memoGetParams(fileName);

    state.PauseTiming();
    solving_knapsack.solve({.method = Knapsack::SolvingMethods::BRUTE_FORCE,
                            .capacity = capacity,
                            .benefits = benefits,
                            .weights = weights});
    state.ResumeTiming();
  }
}

template <typename... Args> static void BM_Greedy(benchmark::State &state, Args &&...args) {
  auto args_tuple = std::make_tuple(std::move(args)...);

  Knapsack solving_knapsack;
  auto memoGetParams = utils::assets::memo(utils::assets::get_params_from_file);

  for (auto _ : state) {
    std::string fileName = fmt::format("assets/{}{}.txt", std::get<0>(args_tuple), state.range(0));
    auto [capacity, benefits, weights] = memoGetParams(fileName);

    state.PauseTiming();
    solving_knapsack.solve({.method = Knapsack::SolvingMethods::GREEDY,
                            .capacity = capacity,
                            .benefits = benefits,
                            .weights = weights});
    state.ResumeTiming();
  }
}

BENCHMARK_CAPTURE(BM_Greedy, greedy_method, "Mochila")->Apply(custom_arguments)->Complexity();

BENCHMARK_CAPTURE(BM_BruteForce, brute_force_method, "Mochila")->Apply(custom_arguments)->Complexity();

BENCHMARK_MAIN();
