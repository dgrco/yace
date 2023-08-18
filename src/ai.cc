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

int evaluate(Board &board) {
  int num_black_pieces = 0;
  int num_white_pieces = 0;

  for (int i = 0; i < 64; i++) {
    if (board.GetPiece(i)->IsColor(Black))
      num_black_pieces++;
    else if (board.GetPiece(i)->IsColor(White))
      num_white_pieces++;
  }

  return num_white_pieces - num_black_pieces;
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
