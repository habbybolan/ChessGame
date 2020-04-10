#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "chess.h"
#include <stdbool.h>
#include "validMoves.h"
#include "enemiesToDefeat.h"
#include "protects.h"

// counts and keeps track of the white pieces each black piece can defeat
	// keeps the number and the struct list of white pieces in each black chesspiece struct
	// also calls protect function to check which black pieces are protecting which of its teamamtes
void whitePiecesToTake() {
	struct chessPiece* cpW;
	struct chessPiece* cpB;
	int rowW;
	int colW;
	int l;
	// iterate through the undefeated black pieces
		// checking their valid moves and see which valid moves corespond
	for (int i = 0; i < 16; i++) {
		l = 0;
		cpB = &chessPiecesBlack[i];
		// check if the piece is black and undefeated
		if (cpB->is_live) {
			// iterate through the undefeated white pieces
				// checking if the black piece valid moves correspond to the white piece tile
			for (int k = 0; k < 16; k++) {
				cpW = &chessPiecesWhite[k];
				// check if the piece is a white piece and undefeated
				if (cpW->is_live) {
					rowW = cpW->row;
					colW = cpW->col;
					// check if the currect black piece cbB has a valid move to the white piece cpW
					if (is_validMoveBlack(rowW, colW, *cpB)) {
						cpB->enemiesCanDefeat++;
						cpB->listEnemiesCanDefeat[l] = cpW;
						l++;
						printf("\n");
						printf("%s can take piece: %s", cpB->type, cpW->type);
	
						// cpW: white piece, cpB: black piece
						lookForProtects(cpB, cpW);
					}
				}
			}
		}
	}
}

// resets the count and list of enemies that black pieces can defeat
void resetWhitePiecesToTake() {
	struct chessPiece* cp;
	int l;
	for (int i = 0; i < 16; i++) {
		l = 0;
		cp = &chessPiecesBlack[i];
		// reset the number of enemies that can be defeated
		cp->enemiesCanDefeat = 0;
		// resets the list holding the enemies that can be defeated
		while (cp->listEnemiesCanDefeat[l] != NULL) {
			cp->listEnemiesCanDefeat[l] = NULL;
			l++;
		}
	}
}
