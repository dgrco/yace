#include "../header/board.h"
#include "../header/board_display.h"
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "YACE");
  Board board;
  board.set_squares(board.GetBoardFromFEN(
      "rn1qkbnr/ppp1pppp/8/3p4/3P2b1/2N5/PPP1PPPP/R1BQKBNR w KQkq - 0 1"));
      BoardDisplay board_display(board);

  // run program as long as the window is open
  while (window.isOpen()) {
    // checks all events since last iteration of loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // if user requested the window to be closed
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    // Draw squares and pieces
    board_display.DrawBoard(window, board);

    window.display();
  }

  return 0;
}
