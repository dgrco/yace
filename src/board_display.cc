#include "../header/board_display.h"
#include "../header/piece.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

// Initializes the squares of a board on a GUI
BoardDisplay::BoardDisplay(Board &board) {
  // Set up squares
  DrawSquares();
}

// Updates the pieces vector with new moves
void BoardDisplay::UpdateDisplayPieces(Board &board) {
  _pieces.clear();
  for (int i = 0; i < 64; i++) {
    Piece *curr_piece = board.get_squares()[i];
    if (curr_piece->IsColor(Black) && curr_piece->IsType(Rook)) {
      PieceDisplay piece = PieceDisplay("assets/BRook.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(Black) && curr_piece->IsType(Knight)) {
      PieceDisplay piece = PieceDisplay("assets/BKnight.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(Black) && curr_piece->IsType(Bishop)) {
      PieceDisplay piece = PieceDisplay("assets/BBishop.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(Black) && curr_piece->IsType(Queen)) {
      PieceDisplay piece = PieceDisplay("assets/BQueen.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(Black) && curr_piece->IsType(King)) {
      PieceDisplay piece = PieceDisplay("assets/BKing.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(Black) && curr_piece->IsType(Pawn)) {
      PieceDisplay piece = PieceDisplay("assets/BPawn.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(White) && curr_piece->IsType(Rook)) {
      PieceDisplay piece = PieceDisplay("assets/WRook.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(White) && curr_piece->IsType(Knight)) {
      PieceDisplay piece = PieceDisplay("assets/WKnight.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(White) && curr_piece->IsType(Bishop)) {
      PieceDisplay piece = PieceDisplay("assets/WBishop.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(White) && curr_piece->IsType(Queen)) {
      PieceDisplay piece = PieceDisplay("assets/WQueen.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(White) && curr_piece->IsType(King)) {
      PieceDisplay piece = PieceDisplay("assets/WKing.png");
      _pieces.push_back({piece, i});
    } else if (curr_piece->IsColor(White) && curr_piece->IsType(Pawn)) {
      PieceDisplay piece = PieceDisplay("assets/WPawn.png");
      _pieces.push_back({piece, i});
    }
  }
}

// Draws each square and piece on the board
void BoardDisplay::DrawSquares() {
  bool white = true;
  // Set up squares
  for (int y_pos = 0; y_pos < 8; y_pos++) {
    for (int x_pos = 0; x_pos < 8; x_pos++) {
      sf::RectangleShape *square = new sf::RectangleShape();
      square->setSize(sf::Vector2f(100, 100));
      square->setFillColor(white ? sf::Color(232, 206, 135, 255)
                                 : sf::Color(130, 78, 38, 255));
      square->setPosition(x_pos * 100.0f, y_pos * 100.0f);
      squares_[y_pos * 8 + x_pos] = square;
      white = !white;
    }
    white = !white;
  }
}

void BoardDisplay::DrawBoard(sf::RenderWindow &window, Board &board) {
  for (int i = 0; i < 64; i++) {
    // Draw each square
    window.draw(*squares_[i]);
  }

  for (std::tuple<PieceDisplay, int> piece_with_position : _pieces) {
    // Draw each piece
    std::get<0>(piece_with_position)
        .Draw(window, std::get<1>(piece_with_position));
  }
}

// Highlight a selected square, shows available positions with colored circles
void BoardDisplay::Highlight(sf::RenderWindow &window, Board &board,
                             int position) {
  // Reset board
  DrawSquares();

  // Highlight selected piece
  squares_[position]->setFillColor(sf::Color(154, 154, 156, 255));

  // Highlight available moves
  std::vector<int> avail_positions =
      board.GetPieceMovePositions(board.GetPiece(position));

  for (int pos : avail_positions) {
    sf::CircleShape circle;
    float rad = 15.0f;
    circle.setRadius(rad);
    // this looks confusing, but it just centers by microadjusting the position
    // given the radius
    circle.setPosition(pos % 8 * 100 + (100 - rad) / 2.0 - rad / 2,
                       (pos / 8) * 100 + (100 - rad) / 2.0 - rad / 2);
    if (board.GetPiece(pos)->IsColor(
            board.GetPiece(position)->get_opposite_color())) {
      circle.setFillColor(sf::Color::Blue);
    } else {
      circle.setFillColor(sf::Color::Magenta);
    }
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color::Black);
    window.draw(circle);
  }
}

BoardDisplay::~BoardDisplay() {
  for (int i = 0; i < 64; i++) {
    delete squares_[i];
  }
}
