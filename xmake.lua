set_languages("c++20")
add_rules("mode.debug", "mode.release")

local libs = {"cxxopts", "spdlog", "nlohmann_json", "gtest"}

add_includedirs("include")
add_requires(table.unpack(libs))

target("knapsack")
set_kind("binary")
add_files("standalone/*.cpp")
add_packages(table.unpack(libs))

target("test")
set_kind("binary")
add_files("test/*.cpp")
add_packages(table.unpack(libs))
