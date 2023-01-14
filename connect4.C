/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
*** Louis Ye - 804498969 ***
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/

int SecondPlacePrize(int prize1, int prize2, int prize3)
{	
	// If prize2 is in between prize1, and prize3, the second place prize is prize2.
	if (((prize2 <= prize1) && (prize2 >= prize3)) || ((prize2 >= prize1) && (prize2 <= prize3))) {
		return prize2;
	}

	// If prize3 is in between prize1, and prize2, the second place prize is prize3.
	if (((prize3 <= prize1) && (prize3 >= prize2)) || ((prize3 >= prize1) && (prize3 <= prize2))) {
		return prize3;
	}
	
	// Otherwise, the second place prize is prize1.
	return prize1;
}

//////

int FourInARow(int values[], int length)
{
	int i, j, count;

	// Go through the array.
	for (i = 0; i < length-3; i++) {
		
		// For the next three elements, count each time the current element and the next element matches.
		count = 0;
		for (j = i; j < i+4; j++) {
			if (values[i] == values[j]) {
				count++;
			}

			// If there are four in a row, return the index of the first element in the four-in-a-row.
			if (count == 4) {
				return i;
			}
		}
	}
	
	return -1;
}

//////

int BinaryToDecimal(int binary)
{
	int r;
	int power = 1;
	int decimal = 0;

	/* Take remainder of the binary integer over 10, multiply it by the power,
	and then sum with the decimal value. */
	while (binary != 0) {
		r = binary % 10;
		binary /= 10;
		decimal += r*power;
		power *= 2;
	}

	return decimal;
}

//////

/// Function for bubble sorting.

void BubbleSort(double array[], int length) {

	int i, j;
	double temp;

	// Go through array.
	for (i = 0; i < length; i++) {
		for (j = i+1; j < length; j++){

			// If the current element is greater than the next element, swap the elements.
			if (array[i] > array[j]) {
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			}
		}
	}
}

///

double MedianAbility(double abilities[], int length)
{
	// Sort the array from lowest to highest.
	BubbleSort(abilities, length);

	// If the amount of elements is odd, the median is the middle.
	if (length % 2 == 1) {
		return abilities[length/2];
	}

	// If the amount of elements is even, the median is the two middle most values summed, and divided by 2.
	else {
		return (abilities[length/2] + abilities[(length-1)/2])/2;
	}
}

//////

void RemoveSpaces(char *name)
{
	int i, j, k;	
	int length = strlen(name);

	// Go through the array (twice)
	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {

			// If the current element is a space, and the previous element is a space, shift each element to the left.
			if ((name[j] == ' ') && (name[j-1] == ' ')) {
				for (k = j; k < length; k++) {
					name[k] = name[k+1];
				}	
			}
		}
	}
}

//////

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	int i, j;

	// Make the entire board 0.
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}

	// If the size is odd, the centre will have one fixed piece.
	if (size%2 == 1) {
		board[size/2][size/2] = 3;
	}

	// If the size is even, the centre will have a block of fixed pieces.
	else {
		board[size/2][size/2] = 3;
		board[size/2-1][size/2] = 3;
		board[size/2][size/2-1] = 3;
		board[size/2-1][size/2-1] = 3;
	}
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	int i;

	// If the side is N, search from row 0 to the last row, at column [move].
	if (side == 'N') {
		for (i = 0; i < size-1; i++) {

			// If the current element is not empty, set last positions to -1.
			if (board[i][move] != 0) {
				*lastRow = -1;
				*lastCol = -1;
				return;
			}

			// If the current element is empty, and the next element isn't, place the token at the current element.			
			else if ((board[i][move] == 0) && (board[i+1][move] != 0)) {
				board[i][move] = player;
				*lastRow = i;
				*lastCol = move;
				return;
			}

			// Or if the token is in the last spot.
			else if ((board[i][move] == 0) && (i+1 == size-1)) {
				board[size-1][move] = player;
				*lastRow = size-1;
				*lastCol = move;
				return;
			}
		}

		// If it reaches the end and a token has not been able to be placed, set the last positions to -1.
		if (i == size-2) {
			*lastRow = -1;
			*lastCol = -1;
		}
	}

	// If the side is E, search from the last column to column 0, at row [move].
	if (side == 'E') {
		for (i = size-1; i > 0; i--) {

			if (board[move][i] != 0) {
				*lastRow = -1;
				*lastCol = -1;
				return;
			}

			if ((board[move][i] == 0) && (board[move][i-1] != 0)) {
				board[move][i] = player;
				*lastRow = move;
				*lastCol = i;
				return;
			}

			else if ((board[i][move] == 0) && (i-1 == 0)) {
				board[move][0] = player;
				*lastRow = move;
				*lastCol = 0;
				return;
			}
		}

		if (i == 1) {
			*lastRow = -1;
			*lastCol = -1;
		}
	}


	// If the side is S, search from last row to row 0, at column [move].
	if (side == 'S') {
		for (i = size-1; i > 0; i--) {
			
			if (board[i][move] != 0) {
				*lastRow = -1;
				*lastCol = -1;
				return;
			}

			if ((board[i][move] == 0) && (board[i-1][move] != 0)) {
				board[i][move] = player;
				*lastRow = i;
				*lastCol = move;
				return;
			}

			else if ((board[i][move] == 0) && (i-1 == 0)) {
				board[0][move] = player;
				*lastRow = 0;
				*lastCol = move;
				return;
			}
		}

		if (i == 1) {
			*lastRow = -1;
			*lastCol = -1;
		}
	}

	// If the side is W, search from column 0 to the last column, at row [move].
	if (side == 'W') {
		for (i = 0; i < size-1; i++) {

			if (board[move][i] != 0) {
				*lastRow = -1;
				*lastCol = -1;
				return;
			}

			if ((board[move][i] == 0) && (board[move][i+1] != 0)) {
				board[move][i] = player;
				*lastRow = move;
				*lastCol = i;
				return;
			}

			else if ((board[i][move] == 0) && (i+1 == size-1)) {
				board[move][size-1] = player;
				*lastRow = move;
				*lastCol = size-1;
				return;
			}
		}

		if (i == size-2) {
			*lastRow = -1;
			*lastCol = -1;			
		}
	}
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int i, j, k, l, count;
	int top = 0;
	int bot = 0;
	int left = 0;
	int right = 0;
	int starti, startj;

	// Count the number of filled spaces in the sides.
	for (i = 0; i < size; i++) {
		if (board[0][i] != 0) {
			top++;
		}
		if (board[size-1][i] != 0) {
			bot++;
		}
		if (board[i][0] != 0) {
			left++;
		}
		if (board[i][size-1] != 0) {
			right++;
		}

	}
	// If no empty spaces on the borders, the current player (the player who moved last) is the winner.
	if ((top == size) && (bot == size) && (left == size) && (right == size)) {
		return player;
	}

	// If the last move was an invalid move, the game is not over.
	if (row == -1) {
		return 0;
	}

	// Check for horizontal four-in-a-row.
	for (i = 0; i < size-3; i++) {
		count = 0;
		for (j = i; j < i+4; j++) {
			if (board[row][j] == player) {
				count++;
			}
			
			if (count == 4) {
				return player;
			}
		}
	}

	// Check for vertical four-in-a-row.
	for (i = 0; i < size-3; i++) {
		count = 0;
		for (j = i; j < i+4; j++) {
			if (board[j][col] == player) {
				count++;
			}

			if (count == 4) {
				return player;
			}
		}
	}

	// Find starting position.
	// Set the starting positions as row, and col.
	starti = row;
	startj = col;
	// Move upwards left until either one is 0.
	while ((starti != 0) && (startj != 0)) {
		starti--;
		startj--;
	}

	// Check for diagonal four-in-a-row (top left to bottom right).
	for (i = starti, j = startj; i <= row; i++, j++) {
		count = 0;
		for (k = i, l = j; (k <= row+3) && (k < size); k++, l++) {
			if (board[k][l] == player) {
				count++;
			}

			if (count == 4) {
				return player;
			}

		}
	}

	// Find the other starting position.
	starti = row;
	startj = col;
	while ((starti != 0) && (startj != 0)) {
		starti--;
		startj++;
	}
	// Check for diagonal four-in-a-row (top right to bottom left).
	for (i = starti, j = startj; i <= row; i++, j--) {
		count = 0;
		for (k = i, l = j; (k <= row+3) && (k < size); k++, l--) {
			if (board[k][l] == player) {
				count++;
			}

			if (count == 4) {
				return player;
			}
		}
	}

	// player is returned if there is a four-in-a-row, else game is not over.
	return 0;
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	int i, j;
	int idx = 0;

	// Border.
	for (i = 0; i < size+4; i++) {
		for (j = 0; j <= size + 4; j++) {

			// Corners.
			if ((j < 2) || ((j > size + 1) && (j < size + 4))) {
				boardString[idx] = '-';
			}


			// North.
			if ((i == 0) && ((j >= 2) && (j <= size + 1))) {
				boardString[idx] = 'N';
			}

			if ((i == 1) && ((j >= 2) && (j <= size + 1))) {
				boardString[idx] = (char)(j - 2 + '0');
			}


			// East.
			if (((i >= 2) && (i <= size + 1)) && (j == size + 3)) {
				boardString[idx] = 'E';
			}

			if (((i >= 2) && (i <= size + 1)) && (j == size + 2)) {
				boardString[idx] = (char)(i - 2 + '0');
			}


			// South.
			if ((i == size + 3) && ((j >= 2) && (j <= size + 1))) {
				boardString[idx] = 'S';
			}

			if ((i == size + 2) && ((j >= 2) && (j <= size + 1))) {
				boardString[idx] = (char)(j - 2 + '0');
			}


			// West.
			if (((i >= 2) && (i <= size + 1)) && (j == 0)) {
				boardString[idx] = 'W';
			}

			if (((i >= 2) && (i <= size + 1)) && (j == 1)) {
				boardString[idx] = (char)(i - 2 + '0');
			}

			// New line.
			boardString[idx+1] = '\n';

			idx++;
		}
	}

	// Board.
	idx = 2*(size+6);
	for (i =0; i < size; i++) {
		for (j = 0; j < size; j++) {

			// Empty Space.
			if (board[i][j] == 0) {
				boardString[idx] = '.';
			}

			// Player 1.
			if (board[i][j] == 1) {
				boardString[idx] = 'X';
			}

			// Player 2.
			if (board[i][j] == 2) {
				boardString[idx] = 'O';
			}

			// Fixed token.
			if (board[i][j] == 3) {
				boardString[idx] = '#';
			}

			// If at the end of the board, index increases by 6.
			if (j == size - 1) {
				idx += 6;
			}
			else {
				idx++;
			}
		}
	}

	boardString[(size+4)*(size+4)+size+4] = '\0';
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int i, j, SelectedSide;
	int row, col;

	
	row = -1;
	col = -1;

	// While the move is invalid, select moves.
	while (row == -1) {

		// Check every move to see if it is possible to win on its current move.
		for (i = 0; i < 4; i++) {
			for (j = 0; j < size; j++) {
				if (i == 0) {
					*side = 'N';
				}
				if (i == 1) {
					*side = 'E';
				}
				if (i == 2) {
					*side = 'S';
				}
				if (i == 3) {
					*side = 'W';
				}

				*move = j;

				// Changes row so that it can check whether or not it is valid when it loops again.
				AddMoveToBoard(board, size, *side, *move, player, &row, &col); 

				if (CheckGameOver(board, size, player, row, col) == player) {
					board[row][col] = 0; // Reset the position.
					return; // Return immediately if winning move.
				}
				else {
					board[row][col] = 0; // Else reset, and keep going.
				}

			}
		}

		// If there is no winning move, continue on to select a random side.
		SelectedSide = rand() % 4;
		if (SelectedSide == 0) {
			*side = 'N';
		}
		if (SelectedSide == 1) {
			*side = 'E';
		}
		if (SelectedSide == 2) {
			*side = 'S';
		}
		if (SelectedSide == 3) {
			*side = 'W';
		}

		// Select a random move.
		*move = rand() % size;

		AddMoveToBoard(board, size, *side, *move, player, &row, &col);
		board[row][col] = 0;
	}

}


void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int i, j, SelectedSide;
	int row, col;

	
	row = -1;
	col = -1;

	// While the move is invalid, select moves.
	while (row == -1) {

		// Check every move to see if it is possible to win on its current move.
		for (i = 0; i < 4; i++) {
			for (j = 0; j < size; j++) {
				if (i == 0) {
					*side = 'N';
				}
				if (i == 1) {
					*side = 'E';
				}
				if (i == 2) {
					*side = 'S';
				}
				if (i == 3) {
					*side = 'W';
				}

				*move = j;

				// Changes row so that it can check whether or not it is valid when it loops again.
				AddMoveToBoard(board, size, *side, *move, player, &row, &col); 

				if (CheckGameOver(board, size, player, row, col) == player) {
					board[row][col] = 0; // Reset the position.
					return; // Return immediately if winning move.
				}
				else {
					board[row][col] = 0; // Else reset, and keep going.
				}

			}
		}

		// If there is no winning move, continue on to select a random side.
		SelectedSide = rand() % 4;
		if (SelectedSide == 0) {
			*side = 'N';
		}
		if (SelectedSide == 1) {
			*side = 'E';
		}
		if (SelectedSide == 2) {
			*side = 'S';
		}
		if (SelectedSide == 3) {
			*side = 'W';
		}

		// Select a random move.
		*move = rand() % size;

		AddMoveToBoard(board, size, *side, *move, player, &row, &col);
		board[row][col] = 0;
	}
}
