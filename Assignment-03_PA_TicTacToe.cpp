/****************************************************************
*
 * File: Assignment-03_PA_TicTacToe.cpp
 * By: Liecie Salvador
 * Date: 7-10-25
 *
 * Description: This program implements a Tic-Tac-Toe application,
 * with the implementation of the following functions; isWon, isDraw
 * displayBoard, and makeAMove.
 *
 ****************************************************************/
#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);


int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
}

void displayBoard(char board[0][3]) { // Function to display board
		cout << "\n-------------\n";
		for (int i = 0; i < 3; i++) {
			cout << "|";
			for (int j = 0; j < 3; j++) {
				cout << " " << board[i][j] << " " << "|";
			}
			cout << "\n-------------\n";
		}

}

void makeAMove(char board[3][3], char player) { // Function to ask for user input and check if move is valid
		int row, col;
		bool check = false;

		while (!check) {
			cout << "Enter a row (0, 1, 2) for player " << player << "\t:" << " ";
			cin >> row;
			cout << "Enter a column (0, 1, 2) for player " << player << "\t:" << " ";
			cin >> col;

			if (board[row][col] != player && board[row][col] != 'X' && board[row][col] != 'O') {
				board[row][col] = player; // "Storing" spot
				check = true;
			} else {
				cout << "This cell is already occupied. Try a different cell.\n";
				check = false; // Loops if move is invalid
			}

		}
	}


bool isWon(char player, char  board[][3]) { // Function to check for three in a row
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
			return true;
	}
	for (int j = 0; j < 3; j++) {
		if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
			return true;
	}
	if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
		return true;
	if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
		return true;
	return false;
}

bool isDraw(char board[][3]) { // Function which checks spaces in board
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == ' ') // If empty, game continues
				return false;
		}
	}
	return true;
}
