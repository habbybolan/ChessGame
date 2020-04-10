#ifndef TRHEATSDETECTED_H
#define THREATSDETECTED_H

#include <stdbool.h>

// sets the threat level of each black piece
void blackPiecesWithThreat();

// sorts the black pieces by their threat level
struct chessPiece* sortBlackPiecesByThreat();

// resets the threat level of all piece
void resetThreats();

// checks if the king is threatened
bool is_BlackKingThreatened();

#endif
