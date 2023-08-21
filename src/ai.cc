#include "../header/ai.h"
#include <limits.h>

namespace AI {
int game_count = 0;

int Search(Board &board, int depth, bool maximizing) {
  if (depth == 0) {
    game_count++;
    return evaluate(board);
  }

  if (maximizing) {
    int value = INT_MIN;

    for (int i = 0; i < 64; i++) {
      Piece *piece = board.GetPiece(i);
      if (!piece->IsColor(White)) {
        continue;
      }

      for (int position : board.GetPieceMovePositions(piece)) {
        int old_pos = piece->get_position();
        board.SimMove(piece, position); // sim make the move
        value = std::max(value, Search(board, depth - 1, false));
        board.UndoMove(piece, old_pos); // sim unmake the move
      }
    }

    return value;
  } else {
    int value = INT_MAX;

    for (int i = 0; i < 64; i++) {
      Piece *piece = board.GetPiece(i);
      if (!piece->IsColor(Black)) {
        continue;
      }

      for (int position : board.GetPieceMovePositions(piece)) {
        int old_pos = piece->get_position();
        board.SimMove(piece, position); // sim make the move
        value = std::min(value, Search(board, depth - 1, true));
        board.UndoMove(piece, old_pos); // sim unmake the move
      }
    }

    return value;
  }
}

int get_piece_score(Piece *piece) {
  switch (piece->GetValue() & 0b00111) { // check each piece type
    case Pawn:
      return 1;
    case Bishop:
      return 3;
    case Knight:
      return 3;
    case Rook:
      return 5;
    case Queen:
      return 9;
    case King:
      return INT_MAX;
    default:
      return 0;
  }
}


int evaluate(Board &board) {
  int white_score = 0;
  int black_score = 0;

  for (int i = 0; i < 64; i++) {
    Piece *piece = board.GetPiece(i);
    if (piece->IsColor(Black)) 
      black_score += get_piece_score(piece);
    else if (piece->IsColor(White))
      white_score += get_piece_score(piece);
  }

  return white_score - black_score;
}

std::tuple<Piece *, int> GetBestMove(Board &board, int depth, bool white_to_move) {
  std::tuple<Piece *, int> best_move;
  if (white_to_move) {
    int max_eval = INT_MIN;
    for (int i = 0; i < 64; i++) {
      Piece *piece = board.GetPiece(i);
      int old_position = piece->get_position();
      if (!piece->IsColor(White)) {
        continue;
      }

      for (int position : board.GetPieceMovePositions(piece)) {
        board.SimMove(piece, position);
        int search_result = Search(board, depth - 1, false);
        board.UndoMove(piece, old_position);

        if (max_eval < search_result) {
          max_eval = search_result;
          best_move = {piece, position};
        }
      }
    }
  } else {
    int min_eval = INT_MAX;
    for (int i = 0; i < 64; i++) {
      Piece *piece = board.GetPiece(i);
      int old_position = piece->get_position();
      if (!piece->IsColor(Black)) {
        continue;
      }

      for (int position : board.GetPieceMovePositions(piece)) {
        board.SimMove(piece, position);
        int search_result = Search(board, depth - 1, true);
        board.UndoMove(piece, old_position);

        if (min_eval > search_result) {
          min_eval = search_result;
          best_move = {piece, position};
        }
      }
    }
  }
  return best_move;
}

int get_game_count() {
  return game_count;
}
} // namespace AI
