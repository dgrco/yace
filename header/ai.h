#ifndef AI_H
#define AI_H

#include "board.h"

namespace AI {
int Search(Board &board, int depth, bool maximizing);
int evaluate(Board &board);
std::tuple<Piece *, int> GetBestMove(Board &board, int depth,
                                     bool white_to_move);
int get_game_count();
} // namespace AI

#endif
