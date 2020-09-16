#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "chess.h"
#include <stdbool.h>
#include "validMoves.h"
#include "moveBlackPiece.h"
#include "threatsDetected.h"

int rowBest;
int colBest;
struct chessPiece* bestCp;

// moves the fittest piece to (rowBest, rowCol) tile
	// if no fittest, then random move
void moveHighestFitness() {
	rowBest = -1;
	colBest = -1;
	bestCp = bestPieceToMove();
	struct chessPiece* cpW;

	// if there is no best piece/move, move a piece randomly
	if (bestCp == NULL) {
		randomBlackMove();
	}
	// othewise, move the best piece somewhere, depending on the pieces it can take and protect
	else {
		// if the piece is only threatened, but cant take or protect others
			// move it to a new random location !!! make a function to move it to a safe location if one exists
		if (bestCp->protects == 0 && bestCp->enemiesCanDefeat == 0) {
			if (!moveBlackIfValid(bestCp)) {
				randomBlackMove();
			}
		}
		else {
			// move the best piece to (rowBest, colBest)
			cpW = getPiece(rowBest, colBest);
			if (cpW != NULL) {
				cpW->row = 100;
				cpW->col = 100;
				cpW->is_live = 0;
			}
			bestCp->row = rowBest;
			bestCp->col = colBest;
		}
	}

}


// find the piece with the best fittest rating, thus making it the best to move
struct chessPiece* bestPieceToMove() {
	setFitnessRating();
	struct chessPiece* cpTest;
	// go thorugh each piece
	for (int j = 0; j < 16; j++) {
		cpTest = &chessPiecesBlack[j];
		printf("\n");
		printf("%s has fitness: %d", cpTest->type, cpTest->fitness);
	}
	int highestFitness = 0;
	struct chessPiece cp;
	struct chessPiece* bestCp = NULL;
	for (int i = 0; i < 16; i++) {
		cp = chessPiecesBlack[i];
		if (cp.fitness > highestFitness) {
			highestFitness = cp.fitness;
			bestCp = &chessPiecesBlack[i];
		}
	}
	return bestCp;
}


// sets the fittest rating best on the threat, protects, and pieces cp can take
void setFitnessRating() {
	int highestValPieceToTake; // highest value piece that cp can take
	int tempProtect; // keep track of the value of the piece that is being protected by cp after it takes another piece
	int tempFitness; // keeps track of the highest fitness so far
	int j; // keeps track of the iteration through listEnemiesToDefeat
	int k; // keeps track of the itreation through listProtects
	struct chessPiece* cp; // black chess piece to evaluate
	for (int i = 0; i < 16; i++) {
		highestValPieceToTake = 0; // reset for next cp
		tempProtect = 0; // reset for next cp

		cp = &chessPiecesBlack[i];

		// add value if the piece has a threat
		if (cp->threats != 0) {
			cp->fitness = getValueOfPiece(cp->type);
		}
		else {
			cp->fitness = 0;
		}

		j = 0;
		// adds value based on the highest value piece cp can take plus the most valuable piece it is protectting
				// minus the value of cp itself if the new position puts it in threat
		while (cp->listEnemiesCanDefeat[j] != NULL && j < 16) {
			tempProtect = 0;
			k = 0;
			// sets tempProtect to the most valuable piece that cp is protecting
			while (cp->listProtects[k] != NULL && k < 16) {
				if (is_validMoveWhite(cp->listProtectsRow[k], cp->listProtectsCol[k], *cp->listEnemiesCanDefeat[j])) {
					if (getValueOfPiece(cp->listProtects[k]->type) > tempProtect) {
						tempProtect = getValueOfPiece(cp->listProtects[k]->type);
					}
				}
				k++;
			}
			// makes highestValPieceToTake the largest value based on:
				// the most valuable piece it can take, most valuable teammate it's protecting, minus its value if it is put into threat

			if ((getValueOfPiece(cp->listEnemiesCanDefeat[j]->type) -
				newThreat(cp, cp->listEnemiesCanDefeat[j]->row, cp->listEnemiesCanDefeat[j]->col, cp->listEnemiesCanDefeat[j]) +
				tempProtect) >= highestValPieceToTake) {
				highestValPieceToTake = (getValueOfPiece(cp->listEnemiesCanDefeat[j]->type) -
					newThreat(cp, cp->listEnemiesCanDefeat[j]->row, cp->listEnemiesCanDefeat[j]->col, cp->listEnemiesCanDefeat[j]) +
					tempProtect);
				rowBest = cp->listEnemiesCanDefeat[j]->row;
				colBest = cp->listEnemiesCanDefeat[j]->col;
			}
			j++;
		}
		tempFitness = highestValPieceToTake;

		// set the value based on the curent threat, enemies cp can defeat, teammates it can protect and new threats after moving
		cp->fitness = cp->fitness + tempFitness;

	}
}

// ai picks a random piece and chooses a random tile to land on
void randomBlackMove() {
	struct chessPiece* cp;
	int random = rand() % 16; // chooses a random number between 0-15
	cp = &chessPiecesBlack[random]; // cp is the random chesspiece chosen
	int end = 1; // allows to leave while loop once valid piece is found
			 // choose a random piece 
			 // if that piece is either not black or it's not alive, choose a new piece
	while (end) {
		//printf("%d\n", random);
		if (cp->is_live == 1 && cp->team == 'B' && moveBlackIfValid(cp)) {
			end = 0;
		}
		else {
			random = rand() % 16; // chooses a random number between 0-15
			cp = &chessPiecesBlack[random];
		}
	}
}

// helper function for randonBlackMoves
	// choosen a random tile to place the random piece already chosen
	// if no valid move, then return 0 and don't move piece
int moveBlackIfValid(struct chessPiece* cp) {
	// iterate through random moves until it finds a valid move - set end to 0
			 // if it cant find a valid move after 20 tries, try another piece
	struct chessPiece* tempPiece; // piece on the spot ai is moving black piece

	for (int i = 0; i < 50; i++) {
		int col = rand() % 8; // chooses a random number between 0-7
		int row = rand() % 8; // chooses a random number between 0-7
		tempPiece = getPiece(row, col);

		// checking if the move with cp piece is valid
		if (is_validMoveBlack(row, col, *cp) && noTeamPiece(row, col, *cp)) { // move Black piece 
			// check if there is an enemy piece at spot
			// remove enemy piece if it is at spot to move
			if (tempPiece != NULL) {
				if (!noEnemyPiece(row, col, *cp)) { // then there is an enemy at the position
					tempPiece->is_live = 0;
					// move into invalid area - off the board
					tempPiece->row = 100;
					tempPiece->col = 100;
				}
			}
			// move the piece - valid move
			cp->row = row;
			cp->col = col;
			return 1;
		}
	}
	return 0;
}

// gets the value of the chessPiece
int getValueOfPiece(char* type) {
	// value of king = 1000
	if (strcmp("WKg", type) == 0 || strcmp("BKg", type) == 0) {
		return 1000;
	}
	// value of queen = 9
	else if (strcmp("WQn", type) == 0 || strcmp("BQn", type) == 0) {
		return 9;
	}
	// value of rook = 5
	else if (strcmp("WR ", type) == 0 || strcmp("BR ", type) == 0) {
		return 5;
		// value of bishop = 3
	}
	else if (strcmp("WB ", type) == 0 || strcmp("BB ", type) == 0) {
		return 3;
		// value of knight = 3
	}
	else if (strcmp("WK ", type) == 0 || strcmp("BK ", type) == 0) {
		return 3;
		// value of pawn
	}
	else {
		return 1;
	}

}

// helper function of setFitnessRating
	// returns the value of the piece if black chessPiece cpB taking white chesspiece cpW puts it in a new threat
	// can also check if an empty spot has no new threat by setting cpW to NULL and putting in a row and col of empty spot
int newThreat(struct chessPiece* cpB, int row, int col, struct chessPiece* cpW) {
	struct chessPiece* cpWAll; // used to iterate through all white chessPieces
	// iterate through white chess pieces to check if they have a valid move to cpW
	if (cpW != NULL) {
		cpW->row = 100; // move off board to check if other white pieces has a valid move to this one
		cpW->col = 100;
	}
	for (int i = 0; i < 16; i++) {
		cpWAll = &chessPiecesWhite[i];
		if (is_validMoveWhite(row, col, *cpWAll)) {
			if (cpW != NULL) {
				cpW->row = row;
				cpW->col = col;
			}
			return getValueOfPiece(cpB->type);
		}
	}
	// return 0 if no threat in new spot
	if (cpW != NULL) {
		cpW->row = row;
		cpW->col = col;
	}
	return 0;
}

// resets the fitness to 0 for all black pieces
void resetFitness() {
	struct chessPiece* cp;
	for (int i = 0; i < 16; i++) {
		cp = &chessPiecesBlack[i];
		cp->fitness = 0;
	}
}

// find a place on the board that is safe to move to
	// return true if a safe spot exists and move the piece there
	// otherwise, return false, no safe spot exists
bool movePieceNoThreat(struct chessPiece* cp) {
	struct chessPiece* cpW;
	// iterates through all pieces on the board
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// if row i and col j is a valid move
			if (is_validMoveBlack(i, j, *cp)) {
				//if no new threats at row i and col j, break loop
				if (!newThreat(cp, i, j, NULL) != 0) {
					cpW = getPiece(i, j);
					if (cpW != NULL) {
						cpW->row = 100;
						cpW->col = 100;
						cpW->is_live = 0;
					}
					cp->row = i;
					cp->col = j;
					return true;
				}
			}
		}
	}
	return false;
}