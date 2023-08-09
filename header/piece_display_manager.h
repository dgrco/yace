#ifndef PIECE_DISPLAY_MANAGER
#define PIECE_DISPLAY_MANAGER

#include <SFML/Graphics.hpp>

class PieceDisplayManager {
  private:
    sf::Texture spritesheet_;

  public:
    PieceDisplayManager(std::string spritesheet_path);
    
};

#endif
