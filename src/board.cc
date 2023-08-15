#include "../header/board.h"
#include "../header/piece.h"
#include <algorithm>
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
  if (piece->IsType(Rook)) {
    AddStraights(positions, piece->get_position());
  } else if (piece->IsType(Knight)) {
    AddLs(positions, piece->get_position());
  } else if (piece->IsType(Bishop)) {
    AddDiagonals(positions, piece->get_position());
  } else if (piece->IsType(Queen)) {
    AddStraights(positions, piece->get_position());
    AddDiagonals(positions, piece->get_position());
  } else if (piece->IsType(King)) {
    AddKingMoves(positions, piece);
  } else if (piece->IsType(Pawn)) {
    AddPawnMoves(positions, piece);
  }

  return positions;
}

Piece **Board::get_squares() { return this->squares_; }

void Board::AddStraights(std::vector<int> &positions, int starting_position) {
  int curr_pos = starting_position;

  // up
  while (curr_pos > 7 && !squares_[curr_pos - 8]->IsColor(
                             squares_[starting_position]->get_color())) {
    if (squares_[curr_pos]->IsColor(
            squares_[starting_position]->get_opposite_color())) {
      break;
    };

    curr_pos -= 8;

    positions.push_back(curr_pos);
  }

  // down
  curr_pos = starting_position;
  while (curr_pos < 56 && !squares_[curr_pos + 8]->IsColor(
                              squares_[starting_position]->get_color())) {
    if (squares_[curr_pos]->IsColor(
            squares_[starting_position]->get_opposite_color())) {
      break;
    };

    curr_pos += 8;

    positions.push_back(curr_pos);
  }

  // left
  curr_pos = starting_position;
  while (curr_pos % 8 > 0 && !squares_[curr_pos - 1]->IsColor(
                                 squares_[starting_position]->get_color())) {
    if (squares_[curr_pos]->IsColor(
            squares_[starting_position]->get_opposite_color())) {
      break;
    };

    curr_pos -= 1;

    positions.push_back(curr_pos);
  }

  // right
  curr_pos = starting_position;
  while (curr_pos % 8 < 7 && !squares_[curr_pos + 1]->IsColor(
                                 squares_[starting_position]->get_color())) {
    if (squares_[curr_pos]->IsColor(
            squares_[starting_position]->get_opposite_color())) {
      break;
    };

    curr_pos += 1;

    positions.push_back(curr_pos);
  }
}

void Board::AddDiagonals(std::vector<int> &positions, int starting_position) {
  int curr_pos = starting_position;
  int shortest_dist = 0;

  // top-right
  shortest_dist = std::min(7 - curr_pos % 8, curr_pos / 8);
  for (int i = 0; i < shortest_dist; i++) {
    if (squares_[curr_pos - 7]->IsColor(
            squares_[starting_position]->get_color())) {
      break;
    } else if (squares_[curr_pos - 7]->IsColor(
                   squares_[starting_position]->get_opposite_color())) {
      positions.push_back(curr_pos - 7);
      break;
    }

    curr_pos -= 7;
    positions.push_back(curr_pos);
  }

  // bottom-right
  curr_pos = starting_position;
  shortest_dist = std::min(7 - curr_pos % 8, 7 - curr_pos / 8);
  for (int i = 0; i < shortest_dist; i++) {
    if (squares_[curr_pos + 9]->IsColor(
            squares_[starting_position]->get_color())) {
      break;
    } else if (squares_[curr_pos + 9]->IsColor(
                   squares_[starting_position]->get_opposite_color())) {
      positions.push_back(curr_pos + 9);
      break;
    }
    curr_pos += 9;
    positions.push_back(curr_pos);
  }

  // bottom-left
  curr_pos = starting_position;
  shortest_dist = std::min(curr_pos % 8, 7 - curr_pos / 8);
  for (int i = 0; i < shortest_dist; i++) {
    if (squares_[curr_pos + 7]->IsColor(
            squares_[starting_position]->get_color())) {
      break;
    } else if (squares_[curr_pos + 7]->IsColor(
                   squares_[starting_position]->get_opposite_color())) {
      positions.push_back(curr_pos + 7);
      break;
    }

    curr_pos += 7;
    positions.push_back(curr_pos);
  }

  // top-left
  curr_pos = starting_position;
  shortest_dist = std::min(curr_pos % 8, curr_pos / 8);
  for (int i = 0; i < shortest_dist; i++) {
    if (squares_[curr_pos - 9]->IsColor(
            squares_[starting_position]->get_color())) {
      break;
    } else if (squares_[curr_pos - 9]->IsColor(
                   squares_[starting_position]->get_opposite_color())) {
      positions.push_back(curr_pos - 9);
      break;
    }

    curr_pos -= 9;
    positions.push_back(curr_pos);
  }
}

void Board::AddLs(std::vector<int> &positions, int starting_position) {
  int rev_rank = starting_position / 8;
  int file = starting_position % 8;

  if (rev_rank - 2 >= 0 && file + 1 < 8) {
    // up-up-right
    if (!squares_[starting_position - 15]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position - 15);
    }
  }
  if (rev_rank - 1 >= 0 && file + 2 < 8) {
    // up-right-right
    if (!squares_[starting_position - 6]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position - 6);
    }
  }
  if (rev_rank + 1 < 8 && file + 2 < 8) {
    // down-right-right
    if (!squares_[starting_position + 10]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position + 10);
    }
  }
  if (rev_rank + 2 < 8 && file + 1 < 8) {
    // down-down-right
    if (!squares_[starting_position + 17]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position + 17);
    }
  }
  if (rev_rank - 2 >= 0 && file - 1 >= 0) {
    // up-up-left
    if (!squares_[starting_position - 17]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position - 17);
    }
  }
  if (rev_rank - 1 >= 0 && file - 2 >= 0) {
    // up-left-left
    if (!squares_[starting_position - 10]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position - 10);
    }
  }
  if (rev_rank + 1 < 8 && file - 2 >= 0) {
    // down-left-left
    if (!squares_[starting_position + 6]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position + 6);
    }
  }
  if (rev_rank + 2 < 8 && file - 1 >= 0) {
    // down-down-left
    if (!squares_[starting_position + 15]->IsColor(
            squares_[starting_position]->get_color())) {
      positions.push_back(starting_position + 15);
    }
  }
}

void Board::AddPawnMoves(std::vector<int> &positions, Piece *piece) {
  int rev_rank = piece->get_position() / 8;
  int file = piece->get_position() % 8;

  if (piece->IsColor(Black)) {
    // regular moves
    if (rev_rank == 1 &&
        squares_[piece->get_position() + 16]->IsColor(NoColor) &&
        squares_[piece->get_position() + 8]->IsColor(NoColor)) {
      positions.push_back(piece->get_position() + 16);
    }

    if (rev_rank + 1 < 8 &&
        squares_[piece->get_position() + 8]->IsColor(NoColor)) {
      positions.push_back(piece->get_position() + 8);
    }

    // captures
    if (file - 1 >= 0 && rev_rank + 1 < 8 &&
        squares_[piece->get_position() + 7]->IsColor(White)) {
      positions.push_back(piece->get_position() + 7);
    }

    if (file + 1 < 8 && rev_rank + 1 < 8 &&
        squares_[piece->get_position() + 9]->IsColor(White)) {
      positions.push_back(piece->get_position() + 9);
    }
  } else {
    // regular moves
    if (rev_rank == 6 &&
        squares_[piece->get_position() - 16]->IsColor(NoColor)) {
      positions.push_back(piece->get_position() - 16);
    }

    if (rev_rank - 1 >= 0 &&
        squares_[piece->get_position() - 8]->IsColor(NoColor)) {
      positions.push_back(piece->get_position() - 8);
    }

    // captures
    if (file - 1 >= 0 && rev_rank - 1 >= 0 &&
        squares_[piece->get_position() - 7]->IsColor(Black)) {
      positions.push_back(piece->get_position() - 7);
    }

    if (file + 1 < 8 && rev_rank - 1 >= 0 &&
        squares_[piece->get_position() - 9]->IsColor(Black)) {
      positions.push_back(piece->get_position() - 9);
    }
  }
}

void Board::AddKingMoves(std::vector<int> &positions, Piece *piece) {
  int rev_rank = piece->get_position() / 8;
  int file = piece->get_position() % 8;

  // up
  if (rev_rank - 1 >= 0 &&
      !squares_[piece->get_position() - 8]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() - 8);
  }

  // up-right
  if (rev_rank - 1 >= 0 && file + 1 < 8 &&
      !squares_[piece->get_position() - 7]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() - 7);
  }

  // right
  if (file + 1 < 8 &&
      !squares_[piece->get_position() + 1]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() + 1);
  }

  // down-right
  if (rev_rank + 1 < 8 && file + 1 < 8 &&
      !squares_[piece->get_position() + 9]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() + 9);
  }

  // down
  if (rev_rank + 1 < 8 &&
      !squares_[piece->get_position() + 8]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() + 8);
  }

  // down-left
  if (rev_rank + 1 < 8 && file - 1 >= 0 &&
      !squares_[piece->get_position() + 7]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() + 7);
  }

  // left
  if (file - 1 >= 0 &&
      !squares_[piece->get_position() - 1]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() - 1);
  }

  // top-left
  if (rev_rank - 1 >= 0 && file - 1 >= 0 &&
      !squares_[piece->get_position() - 9]->IsColor(piece->get_color())) {
    positions.push_back(piece->get_position() - 9);
  }
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
