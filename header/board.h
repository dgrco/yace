#ifndef BOARD
#define BOARD

#include "piece.h"
#include <stack>

class Board {
private:
  Piece **squares_; // 16 total pieces; the rest have values of 0 (from Piece:
                    // NA for both color and type)
  Color player_color;
  bool player_to_move;
  std::stack<Piece *> taken_piece_buffer; // This is used to store potentially
                                          // taken pieces during simulation so
                                          // they can be replaced in UndoMove

  // Add all "straight" (horizontal/vertical) available moves to a vector
  void AddStraights(std::vector<int> &positions, int starting_position);
  // Add all diagonal available moves to a vector
  void AddDiagonals(std::vector<int> &positions, int starting_position);
  // Add all "Ls" (Knight movements) to a vector
  void AddLs(std::vector<int> &positions, int starting_position);
  // Add pawn moves to a vector
  void AddPawnMoves(std::vector<int> &positions, Piece *piece);
  // Add king moves to a vector
  void AddKingMoves(std::vector<int> &positions, Piece *piece);

public:
  Board(Color player_color);
  ~Board();
  void SetPiece(int position, Piece *piece);
  Piece *GetPiece(int position);

  Piece **get_squares();
  // checks to see if it is the player's turn to move
  bool is_player_to_move();
  void set_player_to_move(bool);

  // Gets all available move positions of a given pointer to a piece
  std::vector<int> GetPieceMovePositions(Piece *piece);
  // Returns an array of pieces/squares in ascending order starting from a0
  // given a FEN string
  Piece **GetBoardFromFEN(std::string fen);
  // Make an irreversible move
  void MakeMove(Piece *piece, int new_position);

  // Move a piece and store any captured pieces into a stack for future recovery
  // (useful in minimax)
  void SimMove(Piece *piece, int new_position);

  // Undoes a move made using SimMove
  void UndoMove(Piece *piece, int old_position);
  // Used for visualizing a board -- useful for debugging invalid moves
  void print_fen();
};

#endif
