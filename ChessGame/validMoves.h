#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include <stdbool.h>

// row and col is the row and column the piece will move to/ is checking
bool is_validMoveWhite(int row, int col, struct chessPiece cp);
bool pawnWhiteMoveValid(int row, int col, struct chessPiece cp);
bool rookieMoveValid(int row, int col, struct chessPiece cp);
bool knightMoveValid(int row, int col, struct chessPiece cp);
bool bishopMoveValid(int row, int col, struct chessPiece cp);
bool kingMoveValid(int row, int col, struct chessPiece cp);
bool queenMoveValid(int row, int col, struct chessPiece cp);

bool is_validMoveBlack(int row, int col, struct chessPiece cp);
bool pawnBlackMoveValid(int row, int col, struct chessPiece cp);

#endif

