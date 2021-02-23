//***************************************************
// Filename: othello.c
//
// Author(s): 
//***************************************************

#include "othello.h"

// Constructs and returns a string representation of the board
char *toString(int size, char board[][size])
{
	char *str = (char *) calloc(3 * (size+1) * (size+1), sizeof(char));
	char *ptr = str;

	for (int i = 0; i < size; i++) {
		ptr += sprintf(ptr,(i == 0 ? "%3d" : "%2d"),i+1);
	}
	sprintf(ptr,"\n");
	ptr++;

	for (int i = 0; i < size; i++) {
		sprintf(ptr,"%1d",i+1);
		ptr++;
		for (int j = 0; j < size; j++) {
			sprintf(ptr,"%2c",board[i][j]);
			ptr += 2;
		}
		sprintf(ptr,"\n");
		ptr++;
	}

	return str;
}

// Initializes the board with start configuration of discs (see project specs)
void initializeBoard(int size, char board[][size])
{
	int halfMax = size /2;
	int halfMin = halfMax -1;

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			//sets the black markers
			if((i == halfMax) && (j == halfMax)){
				board[i][j] = 'B';
			}
			else if(i == halfMin && j == halfMin){
				board[i][j] = 'B';
			}
			//sets the white markers
			else if((i == halfMin || i == halfMax) && (j == halfMax || j == halfMin)){
				board[i][j] = 'W';
			}
			else{
				board[i][j] = '-';
			}
		}
	}
} //DONE

// Returns true if moving the disc to location row,col is valid; false otherwise
bool isValidMove(int size, char board[][size], int row, int col, char disc)
{	
	bool canFlip = false;
	int r = 1;
	int c = 1;

	//row +r
	while(board[row+r+1][col] == 'W' || board[row+r+1][col] == 'B' || board[row+r+1][col] == '-'){
		if((board[row+r][col] == disc) && (board[row+1][col] != disc) && (board[row+1][col] != '-')){
			canFlip = true;
		}
		r = r + 1;
	}
	r = 1;
	c = 1;

	//row -r
	while(board[row-r-1][col] == 'W' || board[row-r-1][col] == 'B' || board[row-r-1][col] == '-'){
		if(board[row-r][col] == disc && (board[row-1][col] != disc) && (board[row-1][col] != '-')){
			canFlip = true;
		}
		r = r + 1;
	}
	r = 1;
	c = 1;

	//col +c
	while(board[row][col+c+1] == 'W' || board[row][col+c+1] == 'B' || board[row][col+c+1] == '-'){
		if(board[row][col+c] == disc && (board[row][col+1] != disc) && (board[row][col+1] != '-')){
			canFlip = true;
		}
		c = c + 1;
	}
	r = 1;
	c = 1;

	//col -c
	while(board[row][col-c-1] == 'W' || board[row][col-c-1] == 'B' || board[row][col-c-1] == '-'){
		if(board[row][col-c] == disc && (board[row][col-1] != disc) && (board[row][col-1] != '-')){
			canFlip = true;
		}
		c = c + 1;
	}
	r = 1;
	c = 1;

	//col +c row + r
	while(board[row+r+1][col+c+1] == 'W' || board[row+r+1][col+c+1] == 'B' || board[row+r+1][col+c+1] == '-'){
		if(board[row+r][col+c] == disc && (board[row+1][col+1] != disc) && (board[row+1][col+1] != '-')){
			canFlip = true;
		}
		c = c + 1;
		r = r + 1;
	}
	r = 1;
	c = 1;

	//col +c row -r
	while(board[row-r-1][col+c+1] == 'W' || board[row-r-1][col+c+1] == 'B' || board[row-r-1][col+c+1] == '-'){
		if(board[row-r][col+c] == disc && (board[row-1][col+1] != disc) && (board[row-1][col+1] != '-')){
			canFlip = true;
		}
		c = c + 1;
		r = r + 1;
	}
	r = 1;
	c = 1;

	//col -c row -r
	while(board[row-r-1][col-c-1] == 'W' || board[row-r-1][col-c-1] == 'B' || board[row-r-1][col-c-1] == '-'){
		if(board[row-r][col-c] == disc && (board[row-1][col-1] != disc) && (board[row-1][col-1] != '-')){
			canFlip = true;
		}
		c = c + 1;
		r = r + 1;
	}
	r = 1;
	c = 1;	

	//col -c row +r
	while(board[row+r+1][col-c-1] == 'W' || board[row+r+1][col-c-1] == 'B' || board[row+r+1][col-c-1] == '-'){
		if(board[row+r][col-c] == disc && (board[row+1][col-1] != disc) && (board[row+1][col-1] != '-')){
			canFlip = true;
		}
		c = c + 1;
		r = r + 1;
	}
	r = 1;
	c = 1;

	if((canFlip) && (board[row][col] == '-' )){
		return true;
	}else{
		return false;
	} 
} //Done

// Places the disc at location row,col and flips the opponent discs as needed
void placeDiscAt(int size, char board[][size], int row, int col, char disc){
	//declares adn sets not disc the opposite of disc
	char notDisc;
	if(disc == 'B'){
		notDisc = 'W';
    }
	if(disc == 'W'){
		notDisc = 'B';
	}

	bool tl = false;
	bool tm = false;
	bool tr = false;
	bool ml = false;
	bool mr = false;
	bool bl = false;
	bool bm = false;
	bool br = false;

	//counter for going through a lane
	int c = 1;

	// where we set the lanes true or false values prior to the isValid move check 

	if(board[row+1][col] == notDisc){ //bm r+
		for(int i = 0; i < size; i++){
			if(board[row+i][col] == disc){
				bm = true;
            }
        }
    }
	if(board[row-1][col] == notDisc){ //tm r- 
		for(int i = 0; i < size; i++){
			if(board[row-i][col] == disc){
				tm = true;
            }
        }
    }
	if(board[row][col-1] == notDisc){ //ml c- 
		for(int i = 0; i < size; i++){
			if(board[row][col-i] == disc){
				ml = true;
            }
        }
    }
	if(board[row][col+1] == notDisc){ //mr c+ 
		for(int i = 0; i < size; i++){
			if(board[row][col+i] == disc){
				mr = true;
            }
        }
    }
	if(board[row+1][col+1] == notDisc){ //br r+  c+ 
		for(int i = 0; i < size; i++){
			if(board[row+i][col+i] == disc){
				br = true;
            }
        }
    }
	if(board[row-1][col-1] == notDisc){ //tl r- c-
		for(int i = 0; i < size; i++){
			if(board[row-i][col-i] == disc){
				tl = true;
            }
        }
    }
	if(board[row+1][col-1] == notDisc){ //bl r+ c-
		for(int i = 0; i < size; i++){
			if(board[row+i][col-i] == disc){
				bl = true;
            }
        }
    }
	if(board[row-1][col+1] == notDisc){ //tr r- c+
		for(int i = 0; i < size; i++){
			if(board[row-i][col+i] == disc){
				tr = true;
            }
        }
    }


	if(isValidMove(size,board,row,col,disc)){
		if(bm){
			while(board[row+c][col] == notDisc){
				if(board[row+2][col] == 'W' || board[row+2][col] == 'B'){
					board[row+c][col] = disc;
                }
				c++;
			}
			c = 1;
        }
		if(tm){
			while(board[row-c][col] == notDisc){
				if(board[row-2][col] == 'W' || board[row-2][col] == 'B'){
					board[row-c][col] = disc;
				}
				c++;
			}
			c = 1;
        }
		if(ml){
			while(board[row][col-c] == notDisc){
				if(board[row][col-2] == 'W' || board[row][col-2] == 'B'){
					board[row][col-c] = disc;
				}
				c++;
			}
			c = 1;
        }
		if(mr){
			while(board[row][col+c] == notDisc){
				if(board[row][col+2] == 'W' || board[row][col+2] == 'B'){
					board[row][col+c] = disc;
				}
				c++;
			}
			c = 1;
        }
		if(br){
			while(board[row+c][col+c] == notDisc){
				if(board[row+2][col+2] == 'W' || board[row+2][col+2] == 'B'){
					board[row+c][col+c] = disc;
				}
				c++;
			}
			c = 1;
        }
		if(tl){
			while(board[row-c][col-c] == notDisc){
				if(board[row-2][col-2] == 'W' || board[row-2][col-2] == 'B'){
					board[row-c][col-c] = disc;
				}
				c++;
			}
			c = 1;
        }
		if(tr){
			while(board[row-c][col+c] == notDisc){
				if(board[row-2][col+2] == 'W' || board[row-2][col+2] == 'B'){
					board[row-c][col+c] = disc;
				}
				c++;
			}
			c = 1;
        }
		if(bl){
			while(board[row+c][col-c] == notDisc){
				if(board[row+2][col-2] == 'W' || board[row+2][col-2] == 'B'){
					board[row+c][col-c] = disc;
				}
				c++;
			}
			c = 1;
        }

		board[row][col] = disc;
	}
 	//return;	
	// Finish this
}

// Returns true if a valid move for disc is available; false otherwise
bool isValidMoveAvailable(int size, char board[][size], char disc)
{

	int whiteCounter = 0;
	int blackCounter = 0;
	bool canMove = false;

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(board[i][j] == 'B'){
				blackCounter = blackCounter + 1;
			}
			if(board[i][j] == 'W'){
				whiteCounter = whiteCounter + 1;
			}
		}
	}

	if(whiteCounter == 0 || blackCounter == 0){
		return canMove;
	}

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(isValidMove(size, board, i, j, disc)){
				canMove = true;
			}
		}
	}
	return canMove;
	//Done
}

// Returns true if the board is fully occupied with discs; false otherwise
bool isBoardFull(int size, char board[][size])
{
	int count = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(board[i][j] == 'W' || board[i][j] == 'B'){
				count = count + 1;
			}
		}
	}
	if(count == size * size){
		return true;
	}
	return false;
	// Done
}

// Returns true if either the board is full or a valid move is not available for either disc; false otherwise
bool isGameOver(int size, char board[][size])
{
	if((isBoardFull(size, board)) || (!isValidMoveAvailable(size,board,'W') && (!isValidMoveAvailable(size,board,'B')))){
		return true;
	}else{
		return false;
	}
	return false;	// Done
}

// If there is a winner, it returns the disc (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns TIE. When called before the game is over, it returns 0.
char checkWinner(int size, char board[][size])
{
	int blackCounter = 0;
	int whiteCounter = 0;

	if (!isGameOver(size,board)) {
		return 0;
	}

	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(board[i][j] == 'W'){
				whiteCounter = whiteCounter + 1;
			}
			if(board[i][j] == 'B'){
				blackCounter = blackCounter + 1;
			}
		}
	}
	if(blackCounter > whiteCounter){
		return BLACK;
	}
	else if(whiteCounter > blackCounter){
		return WHITE;
	}else{
		return TIE;
	}
		//Done
}