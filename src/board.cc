#include "../header/board.h"

Board::Board() {
  this->squares_ = GetBoardFromFEN(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::~Board() { free(this->squares_); }

void Board::SetPiece(int position, Piece piece) {
  this->squares_[position] = piece;
}

Piece Board::GetPiece(int position) { return this->squares_[position]; }

Piece *Board::GetBoardFromFEN(std::string fen) {
  Piece *squares = (Piece *)malloc(64 * sizeof(Piece));
  fen = fen.substr(0, fen.find_first_of(' '));

  int idx = 0;
  int space_counter = 0;
  for (int i = 0; i < fen.length(); i++) {
    switch (fen[i]) {
    case 'r':
      squares[idx++] = Piece(Black, Rook);
      break;
    case 'n':
      squares[idx++] = Piece(Black, Knight);
      break;
    case 'b':
      squares[idx++] = Piece(Black, Bishop);
      break;
    case 'q':
      squares[idx++] = Piece(Black, Queen);
      break;
    case 'k':
      squares[idx++] = Piece(Black, King);
      break;
    case 'p':
      squares[idx++] = Piece(Black, Pawn);
      break;
    case 'R':
      squares[idx++] = Piece(White, Rook);
      break;
    case 'N':
      squares[idx++] = Piece(White, Knight);
      break;
    case 'B':
      squares[idx++] = Piece(White, Bishop);
      break;
    case 'Q':
      squares[idx++] = Piece(White, Queen);
      break;
    case 'K':
      squares[idx++] = Piece(White, King);
      break;
    case 'P':
      squares[idx++] = Piece(White, Pawn);
      break;
    case '1' ... '8':
      int digit_value = fen[i] - '0'; // converts char to int
      while (space_counter < digit_value) {
        squares[idx++] = Piece(NoColor, NoType);
        space_counter++;
      }
      space_counter = 0;
      break;
    }
  }
  return squares;
}

Piece *Board::get_squares() {
  return this->squares_;
}
  
void Board::set_squares(Piece *squares) {
  this->squares_ = squares;
}
