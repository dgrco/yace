#include "../header/input_handler.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>
#include <iostream>

InputHandler::InputHandler() {
  mouse_position_ = sf::Vector2i(0, 0);
  selected_piece = nullptr;
  click_locked = false;
}

void InputHandler::Update(sf::RenderWindow &window, sf::Event &event,
                          Board &board, bool playing_as_white) {
  std::vector<int> *avail_move_positions = nullptr;

  if (selected_piece) {
    avail_move_positions = new std::vector<int>();
    for (int pos : board.GetPieceMovePositions(selected_piece)) {
      avail_move_positions->push_back(pos);
    }
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    mouse_position_ = sf::Mouse::getPosition(window);
    if (!click_locked) {
      click_locked = true;
      if (mouse_position_.y > 800 || mouse_position_.y < 0 ||
          mouse_position_.x > 800 || mouse_position_.x < 0) {
        return;
      }

      Piece *piece = board.GetPiece((mouse_position_.y / 100) * 8 +
                                    mouse_position_.x / 100);

      if (selected_piece &&
          selected_piece->get_position() == piece->get_position()) {
        selected_piece = nullptr;
      }
      // if the selected square is in the available move positions, move the
      // selected piece to the square
      else if (avail_move_positions && board.is_player_to_move() && 
               std::find(avail_move_positions->begin(),
                         avail_move_positions->end(), piece->get_position()) !=
                   avail_move_positions->end()) {
        board.MakeMove(selected_piece, piece->get_position());
      } else {
        if (piece->IsColor(playing_as_white ? White : Black) &&
            board.is_player_to_move()) {
          selected_piece = piece;
        } 
      }
    }
  } else {
    click_locked = false;
  }

  if (avail_move_positions) {
    delete avail_move_positions;
  }
}

Piece *InputHandler::get_selected_piece() { return selected_piece; }

bool InputHandler::get_click_locked() { return click_locked; }

void InputHandler::set_click_locked(bool locked) { click_locked = locked; }

void InputHandler::ClearSelected() {
  selected_piece = nullptr;
}
