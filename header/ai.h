#ifndef AI_H
#define AI_H

#include "board.h"

namespace AI {
std::tuple<float, Piece *, int> Search(Board &board, int depth, float a, float b,
                                     bool maximizing);
float evaluate(Board &board);
std::tuple<Piece *, int> GetBestMove(Board &board, int depth,
                                     bool white_to_move);
int get_game_count();
} // namespace AI

#endif
