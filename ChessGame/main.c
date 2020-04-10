#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chess.h"
#include "validMoves.h"
#include "moveBlackPiece.h"
#include "threatsDetected.h"
#include "enemiesToDefeat.h"
#include "testing.h"
#include "protects.h"


int main() {
	setAllPieces();
	buildBoard();
	int* locPiece;
	int moveToRow; // Row user wants to move piece to
	int moveToCol; // Column user wants to move piece to
	struct chessPiece *piece; // pointer of piece chosen by user
	struct chessPiece piece0; // non-pointer version of the chess piece obtained from user input
	struct chessPiece *tempPiece;
	while (is_gameNotfinished() == "continue") {
		bool isValid = false; // checks if move was valid. if not, loop over again and repeat move
		while (!isValid) {

			// White choosing which piece to move
			printf("%s\n", "");
			printf("choose row and column of a white piece to move:");
			printf("%s\n", "");

			int locPieceRow = userInputRow(); // user input for the row
			int locPieceCol = userInputCol(); // user input for the column

			// lets you move any piece to any point on the board ***************************
				// loops infinitely - cannot end the game through this
			if (locPieceRow == 99 && locPieceCol == 99) {
				while (1) {
					printf("\n");
					printf("choose any piece:  ");
					locPieceRow = userInputRow();
					locPieceCol = userInputCol();
					tempPiece = getPiece(locPieceRow, locPieceCol);

					printf("\n");
					printf("choose any tile to move %s to:  ", tempPiece->type);
					moveToRow = userInputRow();
					moveToCol = userInputCol();

					tempPiece->row = moveToRow;
					tempPiece->col = moveToCol;

					buildBoard();
					blackPiecesWithThreat();
					whitePiecesToTake();

					testEnemiesToDefeat();
					testProtects();

					resetThreats();
					resetWhitePiecesToTake();
					resetProtects();
				}
			}
			else {

				// continue normally if not god mode
				piece = getPiece(locPieceRow, locPieceCol);
				if (piece == NULL) { // choosing an empty spot
					printf("Please choose a valid spot: " "Row ""%d" ", Column " "%d" " is not valid", locPieceRow, locPieceCol);
					break;

				}
				piece0 = *piece;
				if (piece0.is_live == 0 || piece0.team == 'B') { // choosing a spot with a dead piece or wrong team
					printf("Please choose a valid spot: " "Row ""%d" ", Column " "%d" " is not valid", locPieceRow, locPieceCol);
					break;
				}

				// white choosing where to move already selected piece
				printf("%s\n", "");
				printf("choose where to move the " "%s" ":", piece0.type);
				printf("%s\n", "");

				moveToRow = userInputRow();
				moveToCol = userInputCol();
				tempPiece = getPiece(moveToRow, moveToCol);

				// checking if the move with piece0 piece is valid
				if (noTeamPiece(moveToRow, moveToCol, piece0) && 0<=moveToRow && moveToRow < 8 && 0<=moveToCol && moveToCol < 8) {
					if (is_validMoveWhite(moveToRow, moveToCol, piece0)) { // move white piece - user piece
						// check if there is an enemy piece at spot
							// remove enemy piece if it is at spot to move
						if (tempPiece != NULL) {
							if (!noEnemyPiece(moveToRow, moveToCol, piece0)) { // then there is an enemy at the position
								tempPiece->is_live = 0;
								// move into invalid area - off the board
								tempPiece->row = 100;
								tempPiece->col = 100;
							}
						}
						// move the player piece if valid move
						piece->row = moveToRow;
						piece->col = moveToCol;
						isValid = true; // leaves the while loop to check if the game is finished or not, otherwise repeat input - invalid move
					}
				}
				if (isValid == false) {
					printf("Please enter a valid move:");
					buildBoard();
				}
				else {
					buildBoard();
					blackPiecesWithThreat();
					whitePiecesToTake();

					moveHighestFitness();

					buildBoard();

					//testEnemiesToDefeat();
					//testProtects();

					resetThreats();
					resetWhitePiecesToTake();
					resetProtects();
					resetFitness();
				}
			}
		}
	}
	char* winner = is_gameNotfinished();
	return winner;
}