set_languages("c++20")
add_rules("mode.debug", "mode.release")

local libs = {"cxxopts", "gtest", "benchmark", "fmt", "better-enums"}

add_includedirs("include")
add_requires(table.unpack(libs))

target("knapsack")
set_kind("binary")
add_files("standalone/*.cpp")
add_deps("knapsack-impl")
add_packages(table.unpack(libs))

target("knapsack-impl")
set_kind("static")
add_files("source/**/*.cpp")
add_packages(table.unpack(libs))

target("bench")
set_kind("binary")
add_files("benchmark/main.cpp")
add_deps("knapsack-impl")
add_packages(table.unpack(libs))

target("test")
set_kind("binary")
add_files("test/*.cpp")
add_deps("knapsack-impl")
add_packages(table.unpack(libs))

-- Post build copy assets folder
after_build(function(target)
    os.cp("assets", target:targetdir())
end)
