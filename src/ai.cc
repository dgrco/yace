#include "../header/ai.h"
#include <limits.h>
#include <limits>

namespace AI {
int game_count = 0;

std::tuple<float, Piece *, int> Search(Board &board, int depth, float a,
                                       float b, bool maximizing) {
  if (depth == 0) {
    game_count++;
    return {evaluate(board), NULL, -1};
  }

  std::tuple<float, Piece *, int> bestResult;
  if (maximizing) {
    bestResult = {std::numeric_limits<float>::min(), NULL, -1};
  } else {
    bestResult = {std::numeric_limits<float>::max(), NULL, -1};
  }

  if (maximizing) {
    float value = std::numeric_limits<float>::min();

    for (int i = 0; i < 64; i++) {
      Piece *piece = board.GetPiece(i);
      if (!piece->IsColor(White)) {
        continue;
      }

      for (int position : board.GetPieceMovePositions(piece)) {
        int old_pos = piece->get_position();
        board.SimMove(piece, position); // sim make the move
        value =
            std::max(value, std::get<0>(Search(board, depth - 1, a, b, false)));
        if (value > std::get<0>(bestResult)) {
          bestResult = {value, piece, position};
        }
        if (value > b) {
          board.UndoMove(piece, old_pos); // sim unmake the move
          return bestResult;
        }
        a = std::max(a, value);
        board.UndoMove(piece, old_pos); // sim unmake the move
      }
    }

    return bestResult;
  } else {
    float value = std::numeric_limits<float>::max();

    for (int i = 0; i < 64; i++) {
      Piece *piece = board.GetPiece(i);
      if (!piece->IsColor(Black)) {
        continue;
      }

      for (int position : board.GetPieceMovePositions(piece)) {
        int old_pos = piece->get_position();
        board.SimMove(piece, position); // sim make the move
        value =
            std::min(value, std::get<0>(Search(board, depth - 1, a, b, true)));
        if (value < std::get<0>(bestResult)) {
          bestResult = {value, piece, position};
        }
        if (value < a) {
          board.UndoMove(piece, old_pos); // sim unmake the move
          return bestResult;
        }
        b = std::min(b, value);
        board.UndoMove(piece, old_pos); // sim unmake the move
      }
    }

    return bestResult;
  }
}

float evaluate(Board &board) {
  int K = 0, k = 0;                     // number of white/black kings
  int Q = 0, q = 0;                     // number of white/black queens
  int R = 0, r = 0;                     // number of white/black rooks
  int B = 0, b = 0;                     // number of white/black bishops
  int N = 0, n = 0;                     // number of white/black knights
  int P = 0, p = 0;                     // number of white/black pawns
  int whiteMiddle = 0, blackMiddle = 0; // keep track of no. of centered pawns
  for (int i = 0; i < 64; i++) {
    Piece *piece = board.GetPiece(i);
    if (piece->IsType(King)) {
      if (piece->IsColor(White)) {
        K++;
      } else {
        k++;
      }
    } else if (piece->IsType(Queen)) {
      if (piece->IsColor(White)) {
        Q++;
      } else {
        q++;
      }
    } else if (piece->IsType(Rook)) {
      if (piece->IsColor(White)) {
        R++;
      } else {
        r++;
      }
    } else if (piece->IsType(Bishop)) {
      if (piece->IsColor(White)) {
        B++;
      } else {
        b++;
      }
    } else if (piece->IsType(Knight)) {
      if (piece->IsColor(White)) {
        N++;
      } else {
        n++;
      }
    } else if (piece->IsType(Pawn)) {
      if (piece->IsColor(White)) {
        P++;
        if (piece->get_position() > 15 && piece->get_position() < 48) {
          whiteMiddle++;
        }
      } else {
        p++;
        if (piece->get_position() > 15 && piece->get_position() < 48) {
          blackMiddle++;
        }
      }
    }
  }

  return 200 * (K - k) + 9 * (Q - q) + 5 * (R - r) + 3 * ((B - b) + (N - n)) +
         1 * (P - p) + 0.1 * (whiteMiddle - blackMiddle);
}

std::tuple<Piece *, int> GetBestMove(Board &board, int depth,
                                     bool white_to_move) {
  std::tuple<float, Piece *, int> search =
      Search(board, depth, std::numeric_limits<float>::min(),
             std::numeric_limits<float>::max(), white_to_move);
  Piece *piece = std::get<1>(search);
  int new_pos = std::get<2>(search);
  return {piece, new_pos};
}

int get_game_count() { return game_count; }
} // namespace AI
