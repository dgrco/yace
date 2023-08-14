#include "../header/board.h"
#include "../header/piece.h"
#include <iostream>

Board::Board() {
  squares_ = GetBoardFromFEN(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Board::~Board() {
  for (int i = 0; i < 64; i++) {
    delete squares_[i];
  }
  delete[] squares_;
}

void Board::SetPiece(int position, Piece *piece) { squares_[position] = piece; }

Piece *Board::GetPiece(int position) { return squares_[position]; }

Piece **Board::GetBoardFromFEN(std::string fen) {
  Piece **squares = new Piece *[64];
  fen = fen.substr(0, fen.find_first_of(' '));

  int idx = 0;
  int space_counter = 0;
  for (int i = 0; i < fen.length(); i++) {
    switch (fen[i]) {
    case 'r':
      squares[idx] = new Piece(Black, Rook, idx);
      idx++;
      break;
    case 'n':
      squares[idx] = new Piece(Black, Knight, idx);
      idx++;
      break;
    case 'b':
      squares[idx] = new Piece(Black, Bishop, idx);
      idx++;
      break;
    case 'q':
      squares[idx] = new Piece(Black, Queen, idx);
      idx++;
      break;
    case 'k':
      squares[idx] = new Piece(Black, King, idx);
      idx++;
      break;
    case 'p':
      squares[idx] = new Piece(Black, Pawn, idx);
      idx++;
      break;
    case 'R':
      squares[idx] = new Piece(White, Rook, idx);
      idx++;
      break;
    case 'N':
      squares[idx] = new Piece(White, Knight, idx);
      idx++;
      break;
    case 'B':
      squares[idx] = new Piece(White, Bishop, idx);
      idx++;
      break;
    case 'Q':
      squares[idx] = new Piece(White, Queen, idx);
      idx++;
      break;
    case 'K':
      squares[idx] = new Piece(White, King, idx);
      idx++;
      break;
    case 'P':
      squares[idx] = new Piece(White, Pawn, idx);
      idx++;
      break;
    case '1' ... '8':
      int digit_value = fen[i] - '0'; // converts char to int
      while (space_counter < digit_value) {
        squares[idx] = new Piece(NoColor, NoType, idx);
        idx++;
        space_counter++;
      }
      space_counter = 0;
      break;
    }
  }
  return squares;
}

std::vector<int> Board::GetPieceMovePositions(Piece *piece) {
  std::vector<int> positions;
  if (piece->IsColor(Black) && piece->IsType(Rook)) {
    AddStraights(positions, piece->get_position());
  } else if (piece->IsColor(Black) && piece->IsType(Knight)) {
  } else if (piece->IsColor(Black) && piece->IsType(Bishop)) {
  } else if (piece->IsColor(Black) && piece->IsType(Queen)) {
  } else if (piece->IsColor(Black) && piece->IsType(King)) {
  } else if (piece->IsColor(Black) && piece->IsType(Pawn)) {
  } else if (piece->IsColor(White) && piece->IsType(Rook)) {
  } else if (piece->IsColor(White) && piece->IsType(Knight)) {
  } else if (piece->IsColor(White) && piece->IsType(Bishop)) {
  } else if (piece->IsColor(White) && piece->IsType(Queen)) {
  } else if (piece->IsColor(White) && piece->IsType(King)) {
  } else if (piece->IsColor(White) && piece->IsType(Pawn)) {
  }

  return positions;
}

Piece **Board::get_squares() { return this->squares_; }

void Board::AddStraights(std::vector<int> &positions, int starting_position) {
  int curr_pos = starting_position;

  // up
  while (curr_pos > 7) {
    curr_pos -= 8;
    positions.push_back(curr_pos);
  }
  
  // down
  curr_pos = starting_position;
  while (curr_pos < 56) {
    curr_pos += 8;
    positions.push_back(curr_pos);
  }
  
  // left
  curr_pos = starting_position;
  while (curr_pos % 8 > 0) {
    curr_pos -= 1;
    positions.push_back(curr_pos);
  }

  // right
  curr_pos = starting_position;
  while (curr_pos % 8 < 7) {
    curr_pos += 1;
    positions.push_back(curr_pos);
  }
}

void Board::AddDiagonals(std::vector<int> &positions, int starting_position) {
  
}

void Board::Move(Piece *piece, int new_position) {
  int old_position = piece->get_position();
  Piece *empty_piece = new Piece(NoColor, NoType, old_position);
  squares_[old_position] = empty_piece;
  
  // Handle taking of piece
  delete GetPiece(new_position);

  piece->set_position(new_position);
  squares_[new_position] = piece;
}
