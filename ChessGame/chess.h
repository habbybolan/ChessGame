#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

struct chessPiece {
	char type[10]; // the type of chesspiece it is
	 
	int col; // column of the chesspiece
	int row; // ro of the chesspiece
	int is_live; // if the chesspiece is still on the board
	char team; // team either B for black or W for white
	int threats; //number of enemy pieces that can defeat this piece
	int protects; // the number of teammates that this piece can save by defeating enemy pieces
	struct chessPiece* listProtects[16]; // list of pieces that are being protected by this peice
	int listProtectsRow[16]; // the corresponding row that index i of listProtects is protected from
	int listProtectsCol[16]; // the corresponding Col that index i of listProtects is protected from
	int enemiesCanDefeat; // the number of enemies that can be defeated by this piece
	struct chessPiece* listEnemiesCanDefeat[16]; // list of enemies that can be defeated by this piece
	int fitness; // the fitness rating of the piece - how likely this piece should be moved

};

struct chessPiece chessPiecesWhite[16];
struct chessPiece chessPiecesBlack[16];

// setting up the pieces at beginning of the game
void setAllPieces();
void setPawns();
void setKnights();
void setRooks();
void setBishops();
void setKingQueen();

void buildBoard();
struct chessPiece *getPiece(int row, int col);
int userInputRow();
int userInputCol();
char* is_gameNotfinished();
bool is_digit(char* f, int len);

// checking if moves are valid
int maxt(int n0, int n1);
int mint(int n0, int n1);


bool noTeamPiece(int row, int col, struct chessPiece cp);
bool noEnemyPiece(int row, int col, struct chessPiece cp);





#endif 
