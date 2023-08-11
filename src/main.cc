#include "../header/board.h"
#include "../header/board_display.h"
#include "../header/input_handler.h"
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "YACE");
  Board board;

  BoardDisplay board_display(board);
  InputHandler input;

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
    board_display.DrawBoard(window);

    // Handle input
    input.Update(window, event, board);

    Piece *selected_piece = input.get_selected_piece();
    if (selected_piece && !selected_piece->IsType(NoType)) {
      board_display.Highlight(window,
                              input.get_selected_piece()->get_position());
    } else {
      // clear the board if no selection
      board_display.DrawSquares();
    }

    window.display();
  }

  return 0;
}
