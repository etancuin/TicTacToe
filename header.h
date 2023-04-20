//
//  header.h
//  TICTACTOE
//
//  Created by Ethan Quinn on 9/27/22.
//

#ifndef header_h
#define header_h

int GamemodeMenu(int gamemode);
int DifficultyMenu(int difficulty);
int PlayAgainMenu(int playAgain);
int RowSelection(int rowChoice);
int ColumnSelection(int columnChoice);
bool EasyAiSelection(int columnChoice, int rowChoice, char ticTacToe[3][3], char turn);
bool HardAiSelection(int columnChoice, int rowChoice, char ticTacToe[3][3], char turn);
bool minimaxMovesLeft(char ticTacToe[3][3]);
int minimaxWinConditions(char player, char ai, char ticTacToe[3][3]);
int minimaxMoves(char ticTacToe[3][3], int depth, bool maxTurn, char player, char ai);
void minimaxTurnRunner(char ticTacToe[3][3], char ai, char player);
void PrintGameBoard(char ticTacToe[3][3], char turn, bool gameover, int turnNumber);
void PrintGameOutcome(bool gameover, char ticTacToe[3][3], char turn, int turnNumber, bool playerTurn, int gamemode);
bool UpdateGameBoard(int columnChoice, int rowChoice, char ticTacToe[3][3], char turn, bool gameover, int turnNumber, int gamemode);
bool TestWinConditions(char turn, char ticTacToe[3][3]);
int TwoPlayerGame(int playAgain, char ticTacToe[3][3], char turn, int columnChoice, int rowChoice, bool gameover, int turnNumber, int gamemode);
int OnePlayerGame(char ticTacToe[3][3], char turn, int columnChoice, int rowChoice, bool gameover, int turnNumber, int difficulty, int gamemode);

#endif
