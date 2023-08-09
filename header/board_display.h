#ifndef BOARD_DISPLAY
#define BOARD_DISPLAY

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class BoardDisplay {
private:
  sf::RectangleShape *squares_[64];

public:
  BoardDisplay();
  void DrawEach(sf::RenderWindow& window);
  ~BoardDisplay();
};

#endif
