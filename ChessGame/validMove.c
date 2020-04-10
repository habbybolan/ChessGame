#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "chess.h"
#include <stdbool.h>
#include "validMoves.h"

// checks if the white piece's move is valid
bool is_validMoveWhite(int row, int col, struct chessPiece cp) {

	if (strcmp(cp.type, "WP ") == 0) {
		return pawnWhiteMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "WR ") == 0) {
		return rookieMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "WK ") == 0) {
		return knightMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "WB ") == 0) {
		return bishopMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "WKg") == 0) {
		return kingMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "WQn") == 0) {
		return queenMoveValid(row, col, cp);
	}
	return false;
}
// checks of white pawn move valid
bool pawnWhiteMoveValid(int row, int col, struct chessPiece cp) {

	if (cp.row == 6 && col == cp.col && row == cp.row - 2 && noTeamPiece(row, col, cp) // when pawn is at start, can move 2 spots
		&& noTeamPiece(row + 1, col, cp) && noEnemyPiece(row, col, cp) && noEnemyPiece(row + 1, col, cp)) {
		return true;

	}
	else if (col == cp.col && row == cp.row - 1 && 0<row<8 && 0<col<8 && noTeamPiece(row, col, cp) // pawn moving 1 move forward
		&& noEnemyPiece(row, col, cp)) {
		return true;
	}
	else if (((col == cp.col + 1 && row == cp.row - 1) || (col == cp.col - 1 && row == cp.row - 1)) // pawn move diagonal if enemy 1 spot diagonal
		&& !noEnemyPiece(row, col, cp)) {
		return true;
	}
	return false;
}
// checks if rookie move is valid
bool rookieMoveValid(int row, int col, struct chessPiece cp) {
	int n = 0;
		if (row != cp.row && col == cp.col) {
			if (cp.row < row) {
				cp.row++;
				n = 1;
			}
			else {
				cp.row--;
				n = -1;
			}
			for (int i = cp.row; i != row; i = i + n) {
				if (!noTeamPiece(i, col, cp) || !noEnemyPiece(i, col, cp))
					return false;
			}
			if (!noTeamPiece(row, col, cp)) {
				return false;
			}
			else {
				return true;
			}
		}
		else if (col != cp.col && row == cp.row) {
			if (cp.col < col) {
				cp.col++;
				n = 1;
			}
			else {
				cp.col--;
				n = -1;
			}
			for (int i = cp.col; i != col; i = i + n) {
				if (!noTeamPiece(row, i, cp) || !noEnemyPiece(row, i, cp)) // if a team piece exists in the path
					return false;
			}
			if (!noTeamPiece(row, col, cp)) {
				return false;
			}
			else {
				return true;
			}
		}
	return false;
}
// checks if knight move is valid
bool knightMoveValid(int row, int col, struct chessPiece cp) {
		if ((row == cp.row + 2 || row == cp.row - 2) && (col == cp.col - 1 || col == cp.col + 1)) {
			return true;
		}
		else if ((col == cp.col + 2 || col == cp.col - 2) && (row == cp.row + 1 || row == cp.row - 1)) {
			return true;
		}
	return false;
}
// checks if bishop move is valid
bool bishopMoveValid(int row, int col, struct chessPiece cp) {
	if (abs(col - cp.col) == abs(row - cp.row)) {
		int n = abs(col - cp.col); // number of spaces to move column-wise
		int i = 0; // keeps trqack of the number of diagonal spaces looked at
		if (row > cp.row && col > cp.col) { // fourth quadrant
			while (i < n) {
				cp.row++;
				cp.col++;
				if (!noTeamPiece(cp.row, cp.col, cp) || (!noEnemyPiece(cp.row, cp.col, cp) && cp.col != col)) {
						return false;
				}
				i++;
			}
			return true;
		}
		else if (row > cp.row && col < cp.col) { // third quadrant
			while (i < n) {
				cp.row++;
				cp.col--;
				if (!noTeamPiece(cp.row, cp.col, cp) || (!noEnemyPiece(cp.row, cp.col, cp) && cp.col != col)) {
						return false;
				}
				i++;
			}
			return true;
		}
		else if (row<cp.row && col<cp.col) { // second quadrant
			while (i < n) {
				cp.row--;
				cp.col--;
				if (!noTeamPiece(cp.row, cp.col, cp) || (!noEnemyPiece(cp.row, cp.col, cp) && cp.col != col)) {
						return false;
				}
				i++;
			}
			return true;
		}
		else if (row<cp.row && col>cp.col) { // first quadrant
			while (i < n) {
				cp.row--;
				cp.col++;
				if (!noTeamPiece(cp.row, cp.col, cp) || (!noEnemyPiece(cp.row, cp.col, cp) && cp.col != col)) {
						return false;
				}
				i++;
			}
			return true;
		}
	}
	return false;
}
// checks if king move is valid
bool kingMoveValid(int row, int col, struct chessPiece cp) {
	if ((col == cp.col && (row == cp.row-1 || row == cp.row+1)) ||
		(row == cp.row && (col == cp.col-1 || col == cp.col+1)) ||
		(col == cp.col+1 && (row == cp.row-1 || row == cp.row+1)) ||
		(col == cp.col-1 && (row == cp.row-1 || row == cp.row+1)) ||
		(row == cp.row+1 && (col == cp.col-1 || col == cp.col+1)) ||
		(row == cp.row-1 && (col == cp.col-1 || col == cp.col+1))) {
		return true;
	}
	return false;
}
// checks if queen move is valid
bool queenMoveValid(int row, int col, struct chessPiece cp) {
	if (rookieMoveValid(row, col, cp) || bishopMoveValid(row, col, cp))
		return true;
	return false;
}

// checks if the black move is valid
bool is_validMoveBlack(int row, int col, struct chessPiece cp) {

	if (strcmp(cp.type, "BP ") == 0) {
		//printf("movePawn: ");
		return pawnBlackMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "BR ") == 0) {
		//printf("moveRook: ");
		return rookieMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "BK ") == 0) {
		//printf("moveKnight: ");
		return knightMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "BB ") == 0) {
		//printf("moveBishop: ");
		return bishopMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "BKg") == 0) {
		//printf("moveKing: ");
		return kingMoveValid(row, col, cp);
	}
	else if (strcmp(cp.type, "BQn") == 0) {
		//printf("moveQueen: ");
		return queenMoveValid(row, col, cp);
	}
	return false;
}
// cehcks if black pawn move is valid
bool pawnBlackMoveValid(int row, int col, struct chessPiece cp) {

	// when pawn is at start, can move 2 spots
	if (cp.row == 1 && col == cp.col && row == cp.row + 2 && noTeamPiece(row, col, cp)
		&& noTeamPiece(row - 1, col, cp) && noEnemyPiece(row, col, cp) && noEnemyPiece(row - 1, col, cp)) {
		return true;
	}
	// pawn moving 1 move forward
	else if (col == cp.col && row == cp.row + 1 && 0<row<8 && 0<col<8 && noTeamPiece(row, col, cp)
		&& noEnemyPiece(row, col, cp)) {
		return true;
	}
	// pawn move diagonal if enemy 1 spot diagonal
	else if (((col == cp.col - 1 && row == cp.row + 1) || (col == cp.col + 1 && row == cp.row + 1))
		&& !noEnemyPiece(row, col, cp)) {
		return true;
	}
	return false;
}
