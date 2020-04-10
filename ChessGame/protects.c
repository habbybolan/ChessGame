#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "chess.h"
#include <stdbool.h>
#include "validMoves.h"
#include "protects.h"
#include "enemiesToDefeat.h"

// called in enemiesToDefeat function (whitePiecesToTake())
	// this saves unnecessary iterations
// sets the list of protects within the struct of chessPieces
	// the list consists of pieces that this chessPiece is protecting by defeating other pieces
	// also counts the number of teammates the piece is protecting 
// function is called by whitePiecesToTake in enemieToDefeat
// cpB: black piece that may be protecting others, cpW: white piece that can be taken my cpB
void lookForProtects(struct chessPiece* cpB, struct chessPiece* cpW) {
	struct chessPiece* cpBProtected;
	int rowB;
	int colB;
	int k = 0;
	// iterate through the black pieces that are possibly protected by other black piece
	for(int j = 0; j < 16; j++) {
		cpBProtected = &chessPiecesBlack[j];
		// make sure a piece is not protecting itself (threat level is for that)
		if (cpBProtected->row != cpB->row || cpBProtected->col != cpB->col) {
			if (cpBProtected->is_live) { // make sure the protected piece is undefeated
				rowB = cpBProtected->row;
				colB = cpBProtected->col;
				// check if the black piece can take a white piece that has valid moves to another black piece
				if (is_validMoveWhite(rowB, colB, *cpW)) {
					cpB->protects++;
					printf("\n");
					printf("%s is protecting piece %s from %s", cpB->type, cpBProtected->type, cpW->type);
					cpB->listProtects[k] = cpBProtected;
					cpB->listProtectsRow[k] = rowB; // row of white piece that can take a black piece
					cpB->listProtectsCol[k] = colB; // col of white piece that can take a black piece
					k++;
				}
			}
		}
	}
}


// resets the count and list of protects that black pieces can protect (their own team)
void resetProtects() {
	struct chessPiece* cp;
	int l;
	for (int i = 0; i < 16; i++) {
		l = 0;
		cp = &chessPiecesBlack[i];
		// reset the number of enemies that can be defeated
		cp->protects = 0;
		// resets the list holing the enemies that can be defeated
		while (cp->listProtects[l] != NULL) {
			cp->listProtects[l] = NULL;
			cp->listProtectsRow[l] = 100;
			cp->listProtectsCol[l] = 100;
			l++;
		}
	}
}