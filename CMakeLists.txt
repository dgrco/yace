cmake_minimum_required(VERSION 3.5)
project(dev)

find_package(SFML 2.6 
  COMPONENTS 
    system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} 
  src/main.cc 
  src/board_display.cc
  src/board.cc
  src/piece.cc
  src/piece_display.cc
  src/input_handler.cc
  src/ai.cc
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

target_compile_options(${PROJECT_NAME} PRIVATE -g)
