#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "chess.h"
#include <stdbool.h>
#include "validMoves.h"


void setPawns() {
	for (int i = 0; i < 8; i++) {
		strcpy(chessPiecesBlack[i].type, "BP ");
		chessPiecesBlack[i].col = i;
		chessPiecesBlack[i].row = 1;
		chessPiecesBlack[i].is_live = 1;
		chessPiecesBlack[i].team = 'B';
	}
	for (int i = 0; i < 8; i++) {
		strcpy(chessPiecesWhite[i].type, "WP ");
		chessPiecesWhite[i].col = i;
		chessPiecesWhite[i].row = 6;
		chessPiecesWhite[i].is_live = 1;
		chessPiecesWhite[i].team = 'W';
	}
}

void setKnights() {
		strcpy(chessPiecesBlack[8].type, "BK ");
		chessPiecesBlack[8].col = 1;
		chessPiecesBlack[8].row = 0;
		chessPiecesBlack[8].is_live = 1;
		chessPiecesBlack[8].team = 'B';

		strcpy(chessPiecesBlack[9].type, "BK ");
		chessPiecesBlack[9].col = 6;
		chessPiecesBlack[9].row = 0;
		chessPiecesBlack[9].is_live = 1;
		chessPiecesBlack[9].team = 'B';

		strcpy(chessPiecesWhite[8].type, "WK ");
		chessPiecesWhite[8].col = 1;
		chessPiecesWhite[8].row = 7;
		chessPiecesWhite[8].is_live = 1;
		chessPiecesWhite[8].team = 'W';

		strcpy(chessPiecesWhite[9].type, "WK ");
		chessPiecesWhite[9].col = 6;
		chessPiecesWhite[9].row = 7;
		chessPiecesWhite[9].is_live = 1;
		chessPiecesWhite[9].team = 'W';
}

void setRooks() {
	strcpy(chessPiecesBlack[10].type, "BR ");
	chessPiecesBlack[10].col = 0;
	chessPiecesBlack[10].row = 0;
	chessPiecesBlack[10].is_live = 1;
	chessPiecesBlack[10].team = 'B';

	strcpy(chessPiecesBlack[11].type, "BR ");
	chessPiecesBlack[11].col = 7;
	chessPiecesBlack[11].row = 0;
	chessPiecesBlack[11].is_live = 1;
	chessPiecesBlack[11].team = 'B';

	strcpy(chessPiecesWhite[10].type, "WR ");
	chessPiecesWhite[10].col = 0;
	chessPiecesWhite[10].row = 7;
	chessPiecesWhite[10].is_live = 1;
	chessPiecesWhite[10].team = 'W';

	strcpy(chessPiecesWhite[11].type, "WR ");
	chessPiecesWhite[11].col = 7;
	chessPiecesWhite[11].row = 7;
	chessPiecesWhite[11].is_live = 1;
	chessPiecesWhite[11].team = 'W';
}

void setBishops() {
	strcpy(chessPiecesBlack[12].type, "BB ");
	chessPiecesBlack[12].col = 2;
	chessPiecesBlack[12].row = 0;
	chessPiecesBlack[12].is_live = 1;
	chessPiecesBlack[12].team = 'B';

	strcpy(chessPiecesBlack[13].type, "BB ");
	chessPiecesBlack[13].col = 5;
	chessPiecesBlack[13].row = 0;
	chessPiecesBlack[13].is_live = 1;
	chessPiecesBlack[13].team = 'B';

	strcpy(chessPiecesWhite[12].type, "WB ");
	chessPiecesWhite[12].col = 2;
	chessPiecesWhite[12].row = 7;
	chessPiecesWhite[12].is_live = 1;
	chessPiecesWhite[12].team = 'W';

	strcpy(chessPiecesWhite[13].type, "WB ");
	chessPiecesWhite[13].col = 5;
	chessPiecesWhite[13].row = 7;
	chessPiecesWhite[13].is_live = 1;
	chessPiecesWhite[13].team = 'W';
}

void setKingQueen() {
	strcpy(chessPiecesBlack[14].type, "BKg");
	chessPiecesBlack[14].col = 3;
	chessPiecesBlack[14].row = 0;
	chessPiecesBlack[14].is_live = 1;
	chessPiecesBlack[14].team = 'B';

	strcpy(chessPiecesBlack[15].type, "BQn");
	chessPiecesBlack[15].col = 4;
	chessPiecesBlack[15].row = 0;
	chessPiecesBlack[15].is_live = 1;
	chessPiecesBlack[15].team = 'B';

	strcpy(chessPiecesWhite[14].type, "WKg");
	chessPiecesWhite[14].col = 3;
	chessPiecesWhite[14].row = 7;
	chessPiecesWhite[14].is_live = 1;
	chessPiecesWhite[14].team = 'W';

	strcpy(chessPiecesWhite[15].type, "WQn");
	chessPiecesWhite[15].col = 4;
	chessPiecesWhite[15].row = 7;
	chessPiecesWhite[15].is_live = 1;
	chessPiecesWhite[15].team = 'W';
}

void setAllPieces() {
	setPawns();
	setKnights();
	setRooks();
	setBishops();
	setKingQueen();
	// sets all pieces threats, protects, enemiesCanDefeat and fitness to 0
		// set lists for enemiesCanDefeat and Protects to NULL
	for (int i = 0; i < 16; i++) {
		chessPiecesWhite[i].threats = 0;
		chessPiecesWhite[i].protects = 0;
		chessPiecesWhite[i].enemiesCanDefeat = 0;
		chessPiecesWhite[i].fitness = 0;

		chessPiecesBlack[i].threats = 0;
		chessPiecesBlack[i].protects = 0;
		chessPiecesBlack[i].enemiesCanDefeat = 0;
		chessPiecesWhite[i].fitness = 0;
		for (int j = 0; j < 16; j++) {
			chessPiecesWhite[i].listEnemiesCanDefeat[j] = NULL;
			chessPiecesWhite[i].listProtects[j] = NULL;
			chessPiecesWhite[i].listProtectsRow[j] = 100;
			chessPiecesWhite[i].listProtectsCol[j] = 100;

			chessPiecesBlack[i].listEnemiesCanDefeat[j] = NULL;
			chessPiecesBlack[i].listProtects[j] = NULL;
			chessPiecesBlack[i].listProtectsRow[j] = 100;
			chessPiecesBlack[i].listProtectsCol[j] = 100;
		}
	}
}

void buildBoard() {
	struct chessPiece *cp;
	struct chessPiece cp0;
	char r[8][8];
	printf("%s\n", "");
	printf("%s", "    0    1    2    3    4    5    6    7");
	for (int n = 0; n < 8; n++) { // n = row number
		printf("%s\n", "");
		printf("%s\n", "  ----------------------------------------");
		for (int i = 0; i < 8; i++) { // i = column number
			cp = getPiece(n, i);
			if (cp == NULL || cp->is_live == 0) {// if row of cp is -1, then it's an empty space
				strcpy(r[i], "   ");
			}
			else {
				cp0 = *cp;
				strcpy(r[i], cp0.type);
			}
		}
		printf("%d" " ", n);
		printf("|" "%s" "| " "%s" "| " "%s" "| " "%s" "| " "%s" "| " "%s" "| " "%s" "| " "%s" "|", r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7]);
	

	}
	printf("%s\n", "");
	printf("%s", "  ----------------------------------------");
}

struct chessPiece *getPiece(int row, int col) {
	struct chessPiece *cp;
	for (int i = 0; i < 16; i++) {
		if ((chessPiecesWhite[i].row == row) && (chessPiecesWhite[i].col == col)) {
			cp = &chessPiecesWhite[i];
			return cp;
		} 
		else if ((chessPiecesBlack[i].row == row) && (chessPiecesBlack[i].col == col)) {
			cp = &chessPiecesBlack[i];
			return cp;
		}
	}
	return NULL;
}

// returns the winner if there is one
	// otherwise return NULL to continue the game
char* is_gameNotfinished() {
	// black king piece
	struct chessPiece *cpBlack = &chessPiecesBlack[14];
	//white king piece
	struct chessPiece *cpWhite = &chessPiecesWhite[14];

	// check if white king is defeated (then black team wins)
	if (cpWhite->is_live == 0) {
		return "Black team wins!";
	}
	// check if black king is deafeated (Then white team wins)
	else if (cpBlack->is_live == 0) {
		return "White team wins!";
	}
	// otherwise neither is deafeated. return NULL
	else {
		return "continue";
	}
}

// user input of the row they choose
int userInputRow() {
	int loc;
	char r[10];
	printf("%s", "enter a row: ");
	int len;
	while (1) {
		scanf("%2s", r);
		len = strlen(r);
		if (is_digit(r, len)) {
			break;
		}
		else {
			printf("%s\n", "please enter a valid number: ");
		}
	}

	int rInt = atoi(r);
	loc = rInt;
	return loc;
}

// user input of the column they choose
int userInputCol() {
	int loc;
	char c[20];  
	int len;
	printf("%s", "enter a column: ");
	while (1) {
		scanf("%2s", c);
		len = strlen(c);
		if (is_digit(c, len)) {
			break;
		}
		else {
			printf("%s\n", "please enter a valid number: ");
		}
	}
	int cInt = atoi(c);
	loc = cInt;
	return loc;
}

bool is_digit(char* f, int len) {
	int isDigit;
	for (int i = 0; i < len; i++) {
		isDigit = isdigit(f[i]);
		if (isDigit == 0) {
			return false;
		}
	}
	return true;
}

// row = row user wants to move to
// col = col user wants to move to
// cp = piece user is moving

int maxt(int n0, int n1) {
	if (n0 > n1)
		return n0;
	return n1;
}

int mint(int n0, int n1) {
	if (n0 < n1)
		return n0;
	return n1;
}

// return true if there is no team piece at (row, col)
bool noTeamPiece(int row, int col, struct chessPiece cp) {
	struct chessPiece *cpt = getPiece(row, col); // piece on the space user is trying to move to
	struct chessPiece cpt0;
	if (cpt == NULL) 
		return true;
	cpt0 = *cpt;
	if (cpt0.team != cp.team )
		return true;
	return false;
}

// return true if there is no enemy piece at (row, col) for piece cp
bool noEnemyPiece(int row, int col, struct chessPiece cp) {
	struct chessPiece *cpt = getPiece(row, col); // piece on the space user is trying to move to
	struct chessPiece cpt0;
	if (cpt == NULL)
		return true;
	cpt0 = *cpt;
	if (cpt0.team != cp.team)
		return false;
	return true;
}







	




