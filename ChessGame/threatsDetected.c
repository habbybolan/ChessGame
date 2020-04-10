#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "chess.h"
#include "validMoves.h"
#include "threatsDetected.h"

// set the threat level of each black piece, given all white pieces
void blackPiecesWithThreat() {
	struct chessPiece *cpW;
	struct chessPiece *cpB;
	int rowB;
	int colB;
	// iterate through the undefeated white pieces
		// checking their valid moves
	for (int i = 0; i < 16; i++) {
		cpW = &chessPiecesWhite[i];
		// check if the piece is white and undefeated
		if (cpW->is_live) {
			// iterate through the black pieces
				// checking if the white piece valid moves correspond to the black piece tile
			for (int k = 0; k < 16; k++) {
				cpB = &chessPiecesBlack[k];
				// check if the piece is a black piece
				if (cpB->is_live) {
					rowB = cpB->row;
					colB = cpB->col;
					// check if the currect white piece cbW has a valid move to the black piece cpB
					if (is_validMoveWhite(rowB, colB, *cpW)) {
						cpB->threats++;
						printf("\n");
						printf("%s: %d threat from %s", cpB->type, cpB->threats, cpW->type);
					}
				}
			}
		}
	}
}

// sort into an array.
	// last array element the most in threat. First has the least threat
struct chessPiece* sortBlackPiecesByThreat() {
	int LastEleSoFar = 0; // the last element in the array so far
	struct chessPiece *cpCurr; // the current black piece being looked at
	struct chessPiece *cpLast; // black piece in the struct list array one before cpCurr
	struct chessPiece *list[16]; // list of chesspieces, where the last element is the largest threat
	list[0] = &chessPiecesBlack[0]; // set the first element the first black pawn in the struct
	// loop to iterate through all pieces
	for (int i = 1; i < 16; i++) {
		cpCurr = &chessPiecesBlack[i];
			LastEleSoFar++;
			list[LastEleSoFar] = cpCurr;
			// goes through the array until the end
				// if the smallest element is being iterated on, it will move to the beginning
			for(int j = LastEleSoFar; j > 0; j--) {
				cpCurr = list[j];
				cpLast = list[j - 1];
					// if the cpCurr threat level is lower than cpLast, then swap their places in the array
						// cpLast goes up in the array, cpCurr goes down
					if (cpLast->threats > cpCurr->threats) {
						list[j - 1] = &cpCurr;
						list[j] = &cpLast;
					}
					else {
						j = 0; // stop the loop - everything in order so far
					}
			}
	}
	return list;
}

// resets the threat count of each piece
void resetThreats() {
	struct chessPiece *cp;
	for (int i = 0; i < 16; i++) {
		cp = &chessPiecesBlack[i];
		cp->threats = 0;
	}
}

bool is_BlackKingThreatened() {
	if (chessPiecesBlack[14].threats != 0)
		return true;
	return false;
}
