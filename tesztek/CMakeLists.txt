cmake_minimum_required(VERSION 2.6)

project(JsonparserTest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable( runTests JsonTest.cpp ../JSON.cpp ../units.cpp ../Hero.cpp ../Monster.cpp ../Game.cpp ../PreparedGame.cpp ../Map.cpp ../MarkedMap.cpp ../Renderer.cpp )
target_link_libraries(runTests gtest gtest_main pthread)
target_compile_features(runTests PRIVATE cxx_std_17)