#include "../header/input_handler.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

InputHandler::InputHandler() {
  mouse_position_ = sf::Vector2i(0, 0);
  selected_piece = nullptr;
  click_locked = false;
}

void InputHandler::Update(sf::RenderWindow &window, sf::Event &event,
                          Board &board) {
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
      } else {
        selected_piece = piece;
      }
    }
  } else {
    click_locked = false;
  }
}

Piece *InputHandler::get_selected_piece() { return selected_piece; }

bool InputHandler::get_click_locked() { return click_locked; }

void InputHandler::set_click_locked(bool locked) { click_locked = locked; }
