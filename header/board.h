#ifndef BOARD
#define BOARD

#include "piece.h"

class Board {
private:
  Piece *squares_; // 16 total pieces; the rest have values of 0 (from Piece:
                   // NA for both color and type)

public:
  Board();
  ~Board();
  void SetPiece(int position, Piece piece);
  Piece GetPiece(int position);
  Piece *get_squares();
  // Returns an array of pieces/squares in ascending order starting from a0
  // given a FEN string
  Piece *GetBoardFromFEN(std::string fen);
};

#endif
