#ifndef PIECE
#define PIECE

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum Type {
  NoType = 0,
  Pawn = 1,
  Knight = 2,
  Bishop = 3,
  Rook = 4,
  King = 5,
  Queen = 6,
};

enum Color {
  NoColor = 0,
  Black = 8,
  White = 16,
};

class Piece {
private:
  Type type_;
  Color color_;
  int position_;
  
public:
  Piece(Color, Type, int);
  void set_position(int);
  int get_position();
  Color get_color();
  Color get_opposite_color();
  bool IsType(Type);
  bool IsColor(Color);
  int GetValue();
};

#endif
