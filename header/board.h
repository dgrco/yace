#ifndef BOARD
#define BOARD

#include "piece.h"

class Board {
private:
  Piece **squares_; // 16 total pieces; the rest have values of 0 (from Piece:
                   // NA for both color and type)
  void AddStraights(std::vector<int> &positions, int starting_position);
  void AddDiagonals(std::vector<int> &positions, int starting_position);

public:
  Board();
  ~Board();
  void SetPiece(int position, Piece *piece);
  Piece *GetPiece(int position);
  Piece **get_squares();
  std::vector<int> GetPieceMovePositions(Piece *piece);
  // Returns an array of pieces/squares in ascending order starting from a0
  // given a FEN string
  Piece **GetBoardFromFEN(std::string fen);
  void Move(Piece *piece, int new_position);
};

#endif
