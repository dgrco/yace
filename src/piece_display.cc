#include "../header/piece_display.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>

PieceDisplay::PieceDisplay(std::string path) {
  this->sprite_ = sf::Sprite();

  if (!this->texture_.loadFromFile(path)) {
    throw new std::runtime_error("Piece sprite loading failed");
  }
}

PieceDisplay::PieceDisplay() {}

void PieceDisplay::Draw(sf::RenderWindow &window, int board_position) {
  int rank = board_position / 8;
  int file = board_position % 8;
  // add 10 to the position due to square-to-piece sizes (20 pixel difference ->
  // divide by 2 to center)
  this->sprite_.setPosition(100.0f * file + 10, 100.0f * rank + 10);
  this->sprite_.setTexture(this->texture_);
  window.draw(this->sprite_);
}

sf::Sprite &PieceDisplay::get_sprite() { return this->sprite_; }
