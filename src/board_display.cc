#include "../header/board_display.h"
#include "../header/piece.h"
#include <SFML/System/Vector2.hpp>

BoardDisplay::BoardDisplay(Board &board) {
  bool white = false;

  // Set up squares
  for (int rank = 0; rank < 8; rank++) {
    for (int file = 0; file < 8; file++) {
      sf::RectangleShape *square = new sf::RectangleShape();
      square->setSize(sf::Vector2f(100, 100));
      square->setFillColor(white ? sf::Color(232, 206, 135, 255)
                                 : sf::Color(130, 78, 38, 255));
      square->setPosition(file * 100.0f, 700 - rank * 100.0f);
      squares_[rank * 8 + file] = square;
      white = !white;
    }
    white = !white;
  }

  // Set up pieces
  for (int i = 0; i < 64; i++) {
    Piece curr_piece = board.get_squares()[i];
    if (curr_piece.IsColor(Black) && curr_piece.IsType(Rook)) {
      PieceDisplay piece = PieceDisplay("assets/BRook.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(Black) && curr_piece.IsType(Knight)) {
      PieceDisplay piece = PieceDisplay("assets/BKnight.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(Black) && curr_piece.IsType(Bishop)) {
      PieceDisplay piece = PieceDisplay("assets/BBishop.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(Black) && curr_piece.IsType(Queen)) {
      PieceDisplay piece = PieceDisplay("assets/BQueen.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(Black) && curr_piece.IsType(King)) {
      PieceDisplay piece = PieceDisplay("assets/BKing.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(Black) && curr_piece.IsType(Pawn)) {
      PieceDisplay piece = PieceDisplay("assets/BPawn.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(White) && curr_piece.IsType(Rook)) {
      PieceDisplay piece = PieceDisplay("assets/WRook.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(White) && curr_piece.IsType(Knight)) {
      PieceDisplay piece = PieceDisplay("assets/WKnight.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(White) && curr_piece.IsType(Bishop)) {
      PieceDisplay piece = PieceDisplay("assets/WBishop.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(White) && curr_piece.IsType(Queen)) {
      PieceDisplay piece = PieceDisplay("assets/WQueen.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(White) && curr_piece.IsType(King)) {
      PieceDisplay piece = PieceDisplay("assets/WKing.png");
      this->pieces_.push_back({piece, i});
    } else if (curr_piece.IsColor(White) && curr_piece.IsType(Pawn)) {
      PieceDisplay piece = PieceDisplay("assets/WPawn.png");
      this->pieces_.push_back({piece, i});
    }
  }
}

void BoardDisplay::DrawBoard(sf::RenderWindow &window, Board &board) {
  for (int i = 0; i < 64; i++) {
    // Draw each square
    window.draw(*squares_[i]);
  }

  for (std::tuple<PieceDisplay, int> piece_with_position : this->pieces_) {
    // Draw each piece
    std::get<0>(piece_with_position)
        .Draw(window, std::get<1>(piece_with_position));
  }
}

BoardDisplay::~BoardDisplay() {
  for (int i = 0; i < 64; i++) {
    delete squares_[i];
  }
}
