#ifndef PIECE_DISPLAY
#define PIECE_DISPLAY

#include <SFML/Graphics.hpp>

class PieceDisplay {
private:
  sf::Sprite sprite_;
  sf::Texture texture_;
  
public:
  // Sets up the piece image given a path
  PieceDisplay();
  PieceDisplay(std::string path);

  // Draws the image to the screen at a board position
  void Draw(sf::RenderWindow &window, int board_position);

  sf::Sprite &get_sprite();
};

#endif
