# ChessGame

A console chess game programmed in C. Play as the white chessBoard pieces against a deterministic AI that uses a fitness score to determine the next move.
 - each black piece is given a certain score, where pawns ranks the lowest and kings ranks the highest.
 - Fitness score is based on the value of itself if it is in danger, value of the most valuable piece it can take, and value of the most 
 valuable team piece it is protecting.
 - if no best move based on fitness, then move a piece at random.
 
 ![chess board beginning](https://github.com/habbybolan/ChessGame/blob/master/beginning_board.PNG)
  
 ![chess board in progress](https://github.com/habbybolan/ChessGame/blob/master/game_in_progress.PNG)
