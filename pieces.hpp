#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include<bits/stdc++.h>

using namespace std;

typedef unsigned int Piece;
typedef unsigned int PieceColor;
typedef unsigned int PieceClass;

enum PieceColors{
    WHITE=16,
    BLACK=8,
    NOCOLOR=0
};

enum PieceEnum{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

namespace Pieces{
    PieceColor getPieceColor(Piece p);
    PieceClass getPieceClass(Piece p);
    Piece makePiece(PieceClass c,PieceColor pc);
    string getPieceFilename(Piece p);
}

#endif  // !PIECES_H_INCLUDED
