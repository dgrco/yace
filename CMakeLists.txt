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
  src/piece_display_manager.cc
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
