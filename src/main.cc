#include "../header/ai.h"
#include "../header/board.h"
#include "../header/board_display.h"
#include "../header/input_handler.h"
#include <SFML/System.hpp>
#include <iostream>

// DEBUGGING PURPOSES
#include <chrono>

std::string file_to_str(int file) {
  switch (file) {
  case 0:;
    return "a";
  case 1:
    return "b";
  case 2:
    return "c";
  case 3:
    return "d";
  case 4:
    return "e";
  case 5:
    return "f";
  case 6:
    return "g";
  case 7:
    return "h";
  default:
    return "";
  }
}

void print_move(std::tuple<Piece *, int> move) {
  int file = std::get<0>(move)->get_position() % 8;
  int rank = 8 - std::get<0>(move)->get_position() / 8;
  int new_file = std::get<1>(move) % 8;
  int new_rank = 8 - std::get<1>(move) / 8;

  std::cout << file_to_str(file) << rank << " -> " << file_to_str(new_file)
            << new_rank << std::endl;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "YACE");
  bool play_as_white = true;

  Board board(play_as_white ? White : Black);

  // DEBUGGING PURPOSES
  // std::chrono::steady_clock::time_point begin =
  //     std::chrono::steady_clock::now();

  // DEBUGGING PURPOSES
  // std::cout << "No. Games: " << AI::get_game_count() << std::endl;
  // std::chrono::steady_clock::time_point end =
  // std::chrono::steady_clock::now(); std::cout << "Time difference = "
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //                                                                    begin)
  //                  .count()
  //           << "[ms]" << std::endl;

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

      window.clear();

      // Handle input
      input.Update(window, event, board, play_as_white);

      // Draw squares and pieces
      board_display.UpdateDisplayPieces(board);
      board_display.DrawBoard(window, board);

      Piece *selected_piece = input.get_selected_piece();
      if (selected_piece && !selected_piece->IsType(NoType) &&
          board.is_player_to_move()) {
        board_display.Highlight(window, board,
                                input.get_selected_piece()->get_position());
      } else {
        // clear the board if no piece is selected
        board_display.DrawSquares();
      }

      if (!board.is_player_to_move()) {
        auto best_move = AI::GetBestMove(board, 4, false);
        board.MakeMove(std::get<0>(best_move), std::get<1>(best_move));
        board.set_player_to_move(true);
        input.ClearSelected();
      }

      window.display();
    }
  }

  return 0;
}
