//***************************************************
// Filename: othello.c
//
// Author(s): Tyler West  
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
	char notDisc;

	if(disc == 'W'){
		notDisc = 'B';
    }
	if(disc == 'B'){
		notDisc = 'W';
    }

	int maxRow = size;
	int maxCol = size;
	int minRow = 1;
	int minCol = 1;


	int c = 1; //count var

	/* row - */
	if(board[row][col] == '-' && board[row-1][col] == notDisc && row-1 >= minRow){ /* checks to see if spot is empty and spot above is notDisc */
		while((row-c >= minRow) && board[row-c][col] == notDisc){ /* while in range of top and bottom rows */
			if(board[row-c-1][col] == disc){ /* if the next one after is the same as disc return true */
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* row + */
	if(board[row][col] == '-' && board[row+1][col] == notDisc && row+1 <= maxRow){ /* checks to see if spot is empty and spot above is notDisc */
		while((row+c <= maxRow) && board[row+c][col] == notDisc){ /* while in range of top and bottom rows */
			if(board[row+c+1][col] == disc){ /* if the next one after is the same as disc return true */
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* col - */
	if(board[row][col] == '-' && board[row][col-1] == notDisc && col-1 >= minCol){ /* checks to see if spot is empty and spot above is notDisc */
		while((col-c >= minCol) && board[row][col-c] == notDisc){ /* while in range of top and bottom rows */
			if(board[row][col-c-1] == disc){
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* col + */
	if(board[row][col] == '-' && board[row][col+1] == notDisc && col+1 <= maxCol){ /* checks to see if spot is empty and spot around is notDisc */
		while((col+c <= maxCol) && board[row][col+c] == notDisc){ /* while in range of top and bottom rows */
			if(board[row][col+c+1] == disc){
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* col + row + */
	if(board[row][col] == '-' && board[row+1][col+1] == notDisc && col+1 <= maxCol && row+1 <=maxRow){ /* checks to see if spot is empty and spot around is notDisc */
		while((col+c <= maxCol && row+c <= maxRow) && board[row+c][col+c] == notDisc){ /* while in range of top and bottom rows */
			if(board[row+c+1][col+c+1] == disc){
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* col + row - */
	if(board[row][col] == '-' && board[row-1][col+1] == notDisc && col+1 <= maxCol && row-1 >= minRow){ /* checks to see if spot is empty and spot around is notDisc */
		while((col+c <= maxCol && row-c >= minRow) && board[row-c][col+c] == notDisc){ /* while in range of top and bottom rows */
			if(board[row-c-1][col+c+1] == disc){
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* col - row - */
	if(board[row][col] == '-' && board[row-1][col-1] == notDisc && col-1 >= minCol && row-1 >= minRow){ /* checks to see if spot is empty and spot around is notDisc */
		while((col-c >= minCol && row-c >= minRow) && board[row-c][col-c] == notDisc){ /* while in range of top and bottom rows */
			if(board[row-c-1][col-c-1] == disc){
				return true;
            }
			c++;
        }
    }
	c = 1;

	/* col - row + */
	if(board[row][col] == '-' && board[row+1][col-1] == notDisc && col-1 >= minCol && row+1 <=maxRow){ /* checks to see if spot is empty and spot around is notDisc */
		while((col-c >= minCol && row+c <= maxRow) && board[row+c][col-c] == notDisc){ /* while in range of top and bottom rows */
			if(board[row+c+1][col-c-1] == disc){
				return true;
            }
			c++;
        }
    }
	c = 1;
	

	return false;
	//DONE
} 

// Places the disc at location row,col and flips the opponent discs as needed ""
void placeDiscAt(int size, char board[][size], int row, int col, char disc){
	//declares adn sets not disc the opposite of disc
	char notDisc;
	if(disc == 'B'){
		notDisc = 'W';
    }
	if(disc == 'W'){
		notDisc = 'B';
	}

	int maxRow = size;
	int maxCol = size;
	int minRow = 1;
	int minCol = 1;

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

	if(board[row+1][col] == notDisc && row+1 <= maxRow){ //bm 
		for(int i = 1; i < size; i++){
			if(board[row+i][col] == disc && row+i <= maxRow){
				bm = true;
            }
        }
    }
	if(board[row][col-1] == notDisc && col-1 >= minCol){ //ml   
		for(int i = 1; i < size; i++){
			if(board[row][col-i] == disc && col-i >= minCol){
				ml = true;
            }
        }
    } 
	if(board[row][col+1] == notDisc && col+1 <= maxCol){ //mr 
		for(int i = 1; i < size; i++){
			if(board[row][col+i] == disc && col+i <= maxCol){
				mr = true;
            }
        }
    }
	if(board[row+1][col+1] == notDisc && row+1 <= maxRow && col+1 <= maxCol){ //br  
		for(int i = 1; i < size; i++){
			if(board[row+i][col+i] == disc && row+i <= maxRow && col+i <= maxCol){
				br = true;
            }
        }
    }
	if(board[row-1][col-1] == notDisc && row-1 >= minRow && col-1 >= minCol){ //tl  
		for(int i = 1; i < size; i++){
			if(board[row-i][col-i] == disc && row-i >= minRow && col-i >= minCol){
				tl = true;
            }
        }
    }
	if(board[row+1][col-1] == notDisc && row && row+1 <= maxRow && col-1 >= minCol){ //bl
		for(int i = 1; i < size; i++){
			if(board[row+i][col-i] == disc && row+i <= maxRow && col-i >= minCol){
				bl = true;
            }
        }
    }
	if(board[row-1][col+1] == notDisc && row-1 >= minRow && col+1 <= maxCol){ /*tr */
		for(int i = 1; i < size; i++){
			if(board[row-i][col+i] == disc && row-i >= minRow && col+i <= maxCol){
				tr = true;
            }
        }
    }


	if(isValidMove(size,board,row,col,disc)){
		if(bm){
			while(board[row+c][col] == notDisc){
				board[row+c][col] = disc;
				c++;
			}
			c = 1;
        }
		if(tm){
			while(board[row-c][col] == notDisc){
				board[row-c][col] = disc;
				c++;
			}
			c = 1;
        }
		if(ml){
			while(board[row][col-c] == notDisc){
				board[row][col-c] = disc;
				c++;
			}
			c = 1;
        }
		if(mr){
			while(board[row][col+c] == notDisc){
				board[row][col+c] = disc;
				c++;
			}
			c = 1;
        }
		if(br){
			while(board[row+c][col+c] == notDisc){
				board[row+c][col+c] = disc;
				c++;
			}
			c = 1;
        }
		if(tr){
			while(board[row-c][col+c] == notDisc){
				board[row-c][col+c] = disc;
				c++;
			}
			c = 1;
        }
		if(tl){
			while(board[row-c][col-c] == notDisc){
				board[row-c][col-c] = disc;
				c++;
			}
			c = 1;
        }
		if(bl){
			while(board[row+c][col-c] == notDisc){
				board[row+c][col-c] = disc;
				c++;
			}
			c = 1;
        }


		board[row][col] = disc;
	}
 	//return;	
	// Done
}

/* Returns true if a valid move for disc is available; false otherwise */
bool isValidMoveAvailable(int size, char board[][size], char disc)
{
	for(int i = 0; i <= size; i++){
		for(int j = 0; j <= size; j++){
			if(isValidMove(size, board, i, j, disc)){
				return true;
			}
		}
	}
	return false;

	//Done
}

/* Returns true if the board is fully occupied with discs; false otherwise */
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