#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include "board.h"
#include <SFML/System.hpp>

class InputHandler {
private:
  sf::Vector2i mouse_position_;
  Piece *selected_piece;
  bool click_locked;

public:
  InputHandler();
  // Updates all input-related data to allow mouse event capturing
  void Update(sf::RenderWindow &window, sf::Event &event, Board &board,
              bool playing_as_white);
  Piece *get_selected_piece();
  // Click locks are used to prevent dragging input
  bool get_click_locked();
  void set_click_locked(bool);
  // clears the selected piece
  void ClearSelected();
};

#endif
