#include "../header/board_display.h"
#include <SFML/System/Vector2.hpp>

BoardDisplay::BoardDisplay() {
  bool white = false;
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      sf::RectangleShape *square = new sf::RectangleShape();
      square->setSize(sf::Vector2f(100, 100));
      square->setFillColor(white ? sf::Color(232, 206, 135, 255)
                                 : sf::Color(130, 78, 38, 255));
      square->setPosition(file * 100.0f, 700 - rank * 100.0f);
      squares_[rank * 8 + file] = square;
      white = !white;
    }
    white = !white;
  }
}

void BoardDisplay::DrawEach(sf::RenderWindow& window) {
  for (int i = 0; i < 64; i++) {
    window.draw(*squares_[i]);
  }
}

BoardDisplay::~BoardDisplay() {
  for (int i = 0; i < 64; i++) {
    delete squares_[i];
  }
}
