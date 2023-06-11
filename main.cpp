//
// 
//  TicTacToe
//  9/23/22.
//  P.S. I left the minimax since it doesn't effect the program unless you choose the hard difficulty ai
//  but that being said it is not exactly functional

#include <iostream>
#include <iomanip>
#include <ctime>
#include "header.h"
using namespace std;

int main() {
    int gamemode = 0;
    int difficulty = 0;
    int playAgain = 1;
    int columnChoice = 0;
    int rowChoice = 0;
    char turn = '\0';
    
    while (playAgain == 1) {
        int turnNumber = 1;
        bool gameover = false;
        playAgain = 0;
        char ticTacToe[3][3] = {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};
        gamemode = GamemodeMenu(0);
        if (gamemode == 2) {
            playAgain = TwoPlayerGame(playAgain, ticTacToe, turn, columnChoice, rowChoice, gameover, turnNumber, gamemode);
        }
        else if (gamemode == 1) {
            difficulty = DifficultyMenu(difficulty);
            playAgain = OnePlayerGame(ticTacToe, turn, columnChoice, rowChoice, gameover, turnNumber, difficulty, gamemode);
        }
    }
    return 0;
}
    
int GamemodeMenu(int gamemode) {
    do {
        cout << "For one player gamemode enter: 1. For two player gamemode enter: 2.";
        cout << endl << ">. ";
        cin >> gamemode;
        if (cin.fail() == true || (gamemode != 1 && gamemode !=2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << "Invalid entry. ";
        }
    } while (gamemode != 1 && gamemode != 2);
    return gamemode;
}
    
int DifficultyMenu(int difficulty) {
    do {
        cout << endl << "For easy difficulty enter: 1. For hard difficulty enter: 2.";
        cout << endl << ">. ";
        cin >> difficulty;
        if (cin.fail() == true || (difficulty != 1 && difficulty !=2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << "Invalid entry. ";
        }
    } while (difficulty != 1 && difficulty != 2);
    return difficulty;
}
    
int PlayAgainMenu(int playAgain) {
    do {
        cout << "To play again enter: 1. To exit enter: 2.";
        cout << endl << ">. ";
        cin >> playAgain;
        if (cin.fail() == true || (playAgain !=1 && playAgain !=2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << "Invalid entry. ";
        }
    } while (playAgain != 1 && playAgain != 2);
    cout << endl;
    return playAgain;
}

int RowSelection(int rowChoice) {
    bool validRow = false;
    while (validRow == false) {
        cout << "Enter the row number you wish to play." << endl << ">. ";
        cin >> rowChoice;
        if (cin.fail() == true || rowChoice < 1 || rowChoice > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid entry. ";
        }
        else {
            validRow = true;
        }
    }
    return rowChoice;
}
    
int ColumnSelection(int columnChoice) {
    bool validColumn = false;
    while (validColumn == false) {
        cout << endl << "Enter the column number you wish to play." << endl << ">. ";
        cin >> columnChoice;
        if (cin.fail() == true || columnChoice < 1 || columnChoice > 3) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid entry. ";
        }
        else {
            validColumn = true;
        }
    }
    return columnChoice;
}

bool EasyAiSelection(int columnChoice, int rowChoice, char ticTacToe[3][3], char turn) {
    do {
        rowChoice = rand() % 3;
        columnChoice = rand() % 3;
    }while (ticTacToe[rowChoice][columnChoice] != '-');
    ticTacToe[rowChoice][columnChoice] = turn;
    return true;
}

bool HardAiSelection(int columnChoice, int rowChoice, char ticTacToe[3][3], char turn) {
    char ai;
    char player;
    if (turn == 'O') {
        ai = 'O';
        player = 'X';
    }
    else {
        ai = 'X';
        player = 'O';
    }
    minimaxTurnRunner(ticTacToe, ai, player);
    return true;
}

bool minimaxMovesLeft(char ticTacToe[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ticTacToe[i][j] == '-') {
                return true;
            }
        }
    }
    return false;
}

int minimaxWinConditions(char player, char ai, char ticTacToe[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (ticTacToe[i][0] == ticTacToe[i][1] && ticTacToe[i][1] == ticTacToe[i][2]) {
            if (ticTacToe[i][0] == player) {
                return -10;
            }
            else if (ticTacToe[i][0] == ai) {
                return 10;
            }
        }
        else if (ticTacToe[0][i] == ticTacToe[1][i] && ticTacToe[1][i] == ticTacToe[2][i]) {
            if (ticTacToe[0][i] == player) {
                return -10;
            }
            else if (ticTacToe[0][i] == ai){
                return 10;
            }
        }
    }
    if (ticTacToe[0][0] == ticTacToe[1][1] && ticTacToe[1][1] == ticTacToe[2][2]){
        if (ticTacToe[0][0] == player) {
            return -10;
        }
        else if (ticTacToe[0][0] == ai){
            return 10;
        }
    }
    else if (ticTacToe[0][2] == ticTacToe[1][1] && ticTacToe[1][1] == ticTacToe[2][0]) {
        if (ticTacToe[0][2] == player) {
            return -10;
        }
        else if (ticTacToe[0][2] == ai){
            return 10;
        }
    }
    return 0;
}

int minimaxMoves(char ticTacToe[3][3], int depth, bool maxTurn, char player, char ai) {
    int score = minimaxWinConditions(player, ai, ticTacToe);
    
    if (minimaxMovesLeft(ticTacToe) == false) {
        return 0;
    }
    
    if (score == 10 || score == -10) {
        return score;
    }
    
    if (maxTurn == true) {
        int best = -11;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (ticTacToe[i][j] == '-') {
                    ticTacToe[i][j] = ai;
                    score = minimaxMoves(ticTacToe, depth + 1, false, player, ai);
                    best = max(score - depth, best);
                    ticTacToe[i][j] = '-';
                }
            }
        }
        return best;
    }
    else if (maxTurn == false) {
        int best = 11;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (ticTacToe[i][j] == '-') {
                    ticTacToe[i][j] = player;
                    score = minimaxMoves(ticTacToe, depth + 1, true, player, ai);
                    best = min(score + depth, best);
                    ticTacToe[i][j] = '-';
                }
            }
        }
        return best;
    }
    return 0;
}

void minimaxTurnRunner(char ticTacToe[3][3], char ai, char player) {
    int bestColumn = -1;
    int bestRow = -1;
    int moveValue = 0;
    int bestValue = -1000;
    
    for (int k = 0; k < 3; ++k) {
        for (int l = 0; l < 3; ++l) {
            if (ticTacToe[k][l] == '-') {
                ticTacToe[k][l] = ai;
                moveValue = minimaxMoves(ticTacToe, 0, true, player, ai);
                ticTacToe[k][l] = '-';
                    
            }
            if (moveValue > bestValue) {
                bestValue = moveValue;
                bestRow = k;
                bestColumn = l;
            }
        }
    }
    ticTacToe[bestRow][bestColumn] = ai;
    return;
}

void PrintGameBoard(char ticTacToe[3][3], char turn, bool gameover, int turnNumber) {
    if (gameover == false && turnNumber < 10) {
        cout << endl << "Player " << turn << "'s turn." << endl;
    }
    cout << endl << "     Column    " << endl;
    cout << "    1   2   3  " << endl;
    cout << "  1 " << ticTacToe[0][0] << " | " << ticTacToe[0][1] << " | " << ticTacToe[0][2] << endl;
    cout << "R  ---|---|---" << endl;
    cout << "O 2 " << ticTacToe[1][0] << " | " << ticTacToe[1][1] << " | " << ticTacToe[1][2] << endl;
    cout << "W  ---|---|---" << endl;
    cout << "  3 " << ticTacToe[2][0] << " | "<< ticTacToe[2][1] << " | " << ticTacToe[2][2] << endl;
    cout << endl;
}

void PrintGameOutcome(bool gameover, char ticTacToe[3][3], char turn, int turnNumber, bool playerTurn, int gamemode) {
    PrintGameBoard(ticTacToe, turn, gameover, turnNumber);
    if (gameover == true) {
        if (gamemode == 2) {
            cout << "Gameover. " << turn << " wins. Congratulations." << endl << endl;
        }
        if (gamemode == 1) {
            if ((playerTurn == false && turn == 'X') || (playerTurn == false && turn == 'O')){
                cout << "Gameover. Player wins. Congratulations." << endl << endl;
            }
            else {
                cout << "Gameover. Ai wins. Better luck next time." << endl << endl;
            }
        }
    }
    else {
        cout << "Game ended in a draw. Better luck next time. " << endl << endl;
    }
}

bool UpdateGameBoard(int columnChoice, int rowChoice, char ticTacToe[3][3], char turn, bool gameover, int turnNumber, int gamemode) {
    if (ticTacToe[rowChoice - 1][columnChoice - 1] == '-') {
        ticTacToe[rowChoice - 1][columnChoice - 1] = turn;
        return true;
    }
    else {
        cout << endl << "Invalid turn, please try again." << endl;
        if (gamemode == 2){
            PrintGameBoard(ticTacToe, turn, gameover, turnNumber);
        }
    }
    return false;
}

bool TestWinConditions(char turn, char ticTacToe[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (ticTacToe[i][0] == turn && ticTacToe[i][1] == turn && ticTacToe[i][2] == turn) {
            return true;
        }
        else if (ticTacToe[0][i] == turn && ticTacToe[1][i] == turn && ticTacToe[2][i] == turn) {
            return true;
        }
    }
    if (ticTacToe[0][0] == turn && ticTacToe[1][1] == turn && ticTacToe[2][2] == turn){
        return true;
    }
    else if (ticTacToe[0][2] == turn && ticTacToe[1][1] == turn && ticTacToe[2][0] == turn) {
        return true;
    }
    return false;
}

int TwoPlayerGame(int playAgain, char ticTacToe[3][3], char turn, int columnChoice, int rowChoice, bool gameover, int turnNumber, int gamemode) {
    while (turnNumber < 10 && gameover == false) {
        bool validTurn = false;
        turn = (turnNumber % 2 == 0) ? 'O':'X';
        PrintGameBoard(ticTacToe, turn, gameover, turnNumber);
        while (validTurn == false) {
            rowChoice = RowSelection(rowChoice);
            columnChoice = ColumnSelection(columnChoice);
            validTurn = UpdateGameBoard(columnChoice, rowChoice, ticTacToe, turn, gameover, turnNumber, gamemode);
        }
    gameover = TestWinConditions(turn, ticTacToe);
    ++turnNumber;
    }
    PrintGameOutcome(gameover, ticTacToe, turn, turnNumber, false, gamemode);
    return PlayAgainMenu(playAgain);
}

int OnePlayerGame(char ticTacToe[3][3], char turn, int columnChoice, int rowChoice, bool gameover, int turnNumber, int difficulty, int gamemode) {
    srand(time(NULL) % 99999);
    bool playerTurn = ((rand() % 2) == 0);
    while (turnNumber < 10 && gameover == false) {
        bool validTurn = false;
        turn = (turnNumber % 2 == 0) ? 'O':'X';
        while (validTurn == false) {
            if (playerTurn == true) {
                PrintGameBoard(ticTacToe, turn, gameover, turnNumber);
                rowChoice = RowSelection(rowChoice);
                columnChoice = ColumnSelection(columnChoice);
                validTurn = UpdateGameBoard(columnChoice, rowChoice, ticTacToe, turn, gameover, turnNumber, gamemode);
            }
            else if (playerTurn == false) {
                if (difficulty == 1) {
                    validTurn = EasyAiSelection(columnChoice, rowChoice, ticTacToe, turn);
                }
                else if (difficulty == 2) {
                    validTurn = HardAiSelection(columnChoice, rowChoice, ticTacToe, turn);
                }
            }
        }
        gameover = TestWinConditions(turn, ticTacToe);
        ++turnNumber;
        playerTurn = !playerTurn;
    }
    PrintGameOutcome(gameover, ticTacToe, turn, turnNumber, playerTurn, gamemode);
    return PlayAgainMenu(1);
}
