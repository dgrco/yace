#include <iostream>
#include "../header/board_display.h"
#include "../header/board.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 800), "YACE");
  BoardDisplay board_display;

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

    // Draw
    board_display.DrawEach(window);

    window.display();
  }

  return 0;
}
