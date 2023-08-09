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
  int rank = 0;
  int space_counter = 0;
  for (int i = fen.length() - 1; i >= 0; i--) {
    switch (fen[i]) {
    case 'r':
      squares[rank * 8 + (7 - idx % 8)] = Piece(Black, Rook);
      idx++;
      break;
    case 'n':
      squares[rank * 8 + (7 - idx % 8)] = Piece(Black, Knight);
      idx++;
      break;
    case 'b':
      squares[rank * 8 + (7 - idx % 8)] = Piece(Black, Bishop);
      idx++;
      break;
    case 'q':
      squares[rank * 8 + (7 - idx % 8)] = Piece(Black, Queen);
      idx++;
      break;
    case 'k':
      squares[rank * 8 + (7 - idx % 8)] = Piece(Black, King);
      idx++;
      break;
    case 'p':
      squares[rank * 8 + (7 - idx % 8)] = Piece(Black, Pawn);
      idx++;
      break;
    case 'R':
      squares[rank * 8 + (7 - idx % 8)] = Piece(White, Rook);
      idx++;
      break;
    case 'N':
      squares[rank * 8 + (7 - idx % 8)] = Piece(White, Knight);
      idx++;
      break;
    case 'B':
      squares[rank * 8 + (7 - idx % 8)] = Piece(White, Bishop);
      idx++;
      break;
    case 'Q':
      squares[rank * 8 + (7 - idx % 8)] = Piece(White, Queen);
      idx++;
      break;
    case 'K':
      squares[rank * 8 + (7 - idx % 8)] = Piece(White, King);
      idx++;
      break;
    case 'P':
      squares[rank * 8 + (7 - idx % 8)] = Piece(White, Pawn);
      idx++;
      break;
    case '/':
      rank++;
      break;
    case '1' ... '8':
      int digit_value = fen[i] - '0'; // converts char to int
      while (space_counter < digit_value) {
        squares[idx + (7 - idx % 8)] = Piece(NoColor, NoType);
        idx++;
        space_counter++;
      }
      space_counter = 0;
      break;
    }
  }
  return squares;
}
