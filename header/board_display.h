#ifndef BOARD_DISPLAY
#define BOARD_DISPLAY

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "board.h"
#include "piece_display.h"

class BoardDisplay {
private:
  // A vector of Piece-Position tuples
  std::vector<std::tuple<PieceDisplay, int>> _pieces;
  // Vector of rectangles representing the game board's squares (background)
  sf::RectangleShape *squares_[64];

public:
  // Initializes the squares of a board on a GUI
  BoardDisplay(Board &board);
  ~BoardDisplay();

  // Draws each square and piece on the board
  void DrawBoard(sf::RenderWindow &window, Board &board);
  void DrawSquares();

  // Highlight a selected square, shows available positions with colored circles
  void Highlight(sf::RenderWindow &window, Board &board, int position);

  // Updates the pieces vector with new moves
  void UpdateDisplayPieces(Board &board);
};

#endif
