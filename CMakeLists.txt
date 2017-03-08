cmake_minimum_required(VERSION 3.5)
project(Blackjack)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Deck.cpp Deck.h Card.h Player.cpp Player.h)
add_executable(Blackjack ${SOURCE_FILES})