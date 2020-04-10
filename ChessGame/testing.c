#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "chess.h"
#include "validMoves.h"
#include "moveBlackPiece.h"
#include "threatsDetected.h"
#include "enemiesToDefeat.h"
#include "protects.h"
#include "testing.h"

// test if the listEnemieToDefeat stores the chessPieces correctly 
void testEnemiesToDefeat() {
	/*struct chessPiece* cp;
	for (int i = 0; i < 32; i++) {
		cp = &chessPiecesBlack[i];
		if (cp->enemiesCanDefeat != 0) {
			int j = 0;
			printf("%s: %d", cp->type, cp->enemiesCanDefeat);
			while (cp->listEnemiesCanDefeat[j] != NULL) {
				printf("\n");
				printf("%s can take %s", cp->type, cp->listEnemiesCanDefeat[j]->type);
				j++;
			}
		}
	}*/
}

void testProtects() {
	/*struct chessPiece* cp;
	for (int i = 0; i < 32; i++) {
		cp = &chessPieces[i];
		if (cp->protects != 0) {
			int j = 0;
			while (cp->listProtects[j] != NULL) {
				printf("\n");
				printf("%s can protect %s", cp->type, cp->listProtects[j]->type);
				j++;
			}
		}
	}*/
}