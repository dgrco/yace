#include "../header/piece.h"

Piece::Piece(Color color, Type type, int position) {
  color_ = color;
  type_ = type;
  position_ = position;
}

void Piece::set_position(int position) { position_ = position; }

int Piece::get_position() { return position_; }

Color Piece::get_color() { return color_; }

Color Piece::get_opposite_color() { return color_ == White ? Black : White; }

bool Piece::IsType(Type type) { return type_ == type; }

bool Piece::IsColor(Color color) { return color_ == color; }

int Piece::GetValue() { return color_ & 0b11000 | type_ & 0b00111; }
