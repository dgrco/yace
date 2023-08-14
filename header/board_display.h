#ifndef BOARD_DISPLAY
#define BOARD_DISPLAY

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "board.h"
#include "piece_display.h"

class BoardDisplay {
private:
  std::vector<std::tuple<PieceDisplay, int>> pieces_;
  sf::RectangleShape *squares_[64];

public:
  BoardDisplay(Board &board);
  ~BoardDisplay();

  // Draws each square and piece on the board
  void DrawBoard(sf::RenderWindow &window);
  void DrawSquares();
  void Highlight(sf::RenderWindow &window, Board &board, int position);
  void UpdateDisplayPieces(Board &board);
};

#endif
