#ifndef MOVEBLACKPIECE_H
#define MOVEBLACKPIECE_H

#include <stdbool.h>


// randomly moves the black piece
void randomBlackMove();

// helper function for randomBlackmoves
	// moves the piece if the move is valid
int moveBlackIfValid(struct chessPiece *cp);

// moves the fittest piece to (rowBest, rowCol) tile
	// if no fittest, then random move
void moveHighestFitness();

// chooses the best piece to move based on fitness level
struct chessPiece* bestPieceToMove();

// sets the fitness rating of all black pieces
void setFitnessRating();

// outputs the valid of the piece cp
int getValueOfPiece(char* type);

// find if there is a new threat after cpB takes cpW
int newThreat(struct chessPiece* cpB, int row, int col, struct chessPiece* cpW);

// resets fitness level of all black pieces
void resetFitness();

// return true if there is a safe place for cp to move
	// move cp to that new spot
	// otherwise, return false, no safe places
bool movePieceNoThreat(struct chessPiece* cp);
/*
// chooses the best piece to move based on fitness level
struct chessPiece* bestPieceToMove();

// sets the fitness rating of all black pieces
void setFitnessRating();

// outputs the valid of the piece cp
int getValueOfPiece(char* type);

// returns the value of cpB if defeating cpW puts the piece in threat
int newThreat(struct chessPiece* cpB, struct chessPiece *cpW);

// moves the fittest piece to (rowBest, rowCol) tile
	// if no fittest, then random move
void moveHighestFitness()
*/
#endif
