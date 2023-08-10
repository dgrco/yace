#include "../header/piece.h"

Piece::Piece(Color color, Type type) {
  this->color_ = color;
  this->type_ = type;
}

void Piece::set_position(int position) { this->position_ = position; }

int Piece::get_position() { return this->position_; }

bool Piece::IsType(Type type) { return this->type_ == type; }

bool Piece::IsColor(Color color) { return this->color_ == color; }

int Piece::GetValue() { return this->color_ & 0b11000 | this->type_ & 0b00111; }
