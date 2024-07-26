cmake_minimum_required(VERSION 3.14)
project(poker-game)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



enable_testing()

include_directories(PlayerList.h Player.h)

add_executable(test_PlayerList test_PlayerList.cpp PlayerList.cpp Player.cpp
Card.cpp Dealer.cpp Deck.cpp)

# add_executable(PlayerList PlayerList.cpp)

# add_executable(Player Player.cpp)

# add_executable(Card Card.cpp)

# add_executable(Dealer Dealer.cpp)

# add_executable(Deck Deck.cpp)

target_link_libraries(test_PlayerList GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_PlayerList)