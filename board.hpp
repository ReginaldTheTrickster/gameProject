#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <bits/stdc++.h>

#include "defines.hpp"
#include "pieces.hpp"

const string STARTING_FEN="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

class Board{
    PieceColor active_color=WHITE;
    float move_number=1.0f;

    bool is_reversed=0;

    Location selected_piece ={-1,-1};

    public:
    int board[8][8];

    float getMoveNumber();
    void incrementMoveNumber();

    PieceColor getActiveColor();
    void toggleActiveColor();

    Location getSelectedPiece();
    int getPieceAt(Location location);

    void setSelectedPiece(int i,int j);
    bool hasSelectedPiece();
    void clearSelectedPiece();

    void tryMove(Location starting,Location ending);
    void makeMove(Location starting,Location ending);

    void readFen(const string fen);
    void printBoard();

    void reverse();
    bool isReversed();
};

#endif  // !BOARD_H_INCLUDED
