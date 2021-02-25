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

	int maxRow = size;
	int maxCol = size;
	int minRow = 1;
	int minCol = 1;

	if(disc == 'W'){
		notDisc = 'B';
    }
	if(disc == 'B'){
		notDisc = 'W';
    }

	bool surrondedByOpposite = ((board[row+1][col] == notDisc && row+1 <= maxRow) || (board[row-1][col] == notDisc && row-1 >= minRow) || (board[row][col+1] == notDisc &&  col+1 <= maxCol) ||
								(board[row][col-1] == notDisc && col-1 >= minCol) || (board[row-1][col-1] == notDisc && col-1 >= minCol && row-1 >= minRow) || 
								(board[row+1][col+1] == notDisc && col+1 >= minCol && row+1 >= minRow) || (board[row+1][col-1] == notDisc && col-1 >= minCol && row+1 <= maxRow) ||
								(board[row-1][col+1] == notDisc && col+1 <= maxCol && row-1 >= minRow));

	bool tlOpp = (board[row-1][col-1] == notDisc && col-1 >= minCol && row-1 >= minRow);
	bool trOpp = (board[row-1][col+1] == notDisc && col+1 <= maxCol && row-1 >= minRow);
	bool tmOpp = (board[row-1][col] == notDisc && row-1 >= minRow);
	bool mrOpp = (board[row][col+1] == notDisc &&  col+1 <= maxCol);
	bool mlOpp = (board[row][col-1] == notDisc && col-1 >= minCol);
	bool blOpp = (board[row+1][col-1] == notDisc && col-1 >= minCol && row+1 <= maxRow);
	bool bmOpp = (board[row+1][col] == notDisc && row+1 <= maxRow);
	bool brOpp = (board[row+1][col+1] == notDisc && col+1 >= minCol && row+1 >= minRow);

	bool bl = false;
	bool bm = false;
	bool br = false;
	bool mr = false;
	bool ml = false;
	bool tr = false;
	bool tm = false;
	bool tl = false;

	int c = 1;

	if(surrondedByOpposite){
		//tl
		if(tlOpp){
			while(board[row-c][col-c] == notDisc && row-c >= minRow && col-c >= minCol){
				c++;
			}
			if(board[row-c][col-c] == disc){
				tl = true;
			}
		}
		c = 1;
		
		//tr
		if(trOpp){
			while(board[row-c][col+c] == notDisc && row-c >= minRow && col+c <= maxCol){
				c++;
			}
			if(board[row-c][col+c] == disc){
				tr = true;
			}
		}
		c = 1;

		//tm
		if(tmOpp){
			while(board[row-c][col] == notDisc && row-c >= minRow){
				c++;
			}
			if(board[row-c][col] == disc){
				tm = true;
			}
		}
		c = 1;

		//ml
		if(mlOpp){
			while(board[row][col-c] == notDisc && col-c >= minCol){
				c++;
			}
			if(board[row][col-c] == disc){
				ml = true;
			}
		}
		c = 1;

		//mr
		if(mrOpp){
			while(board[row][col+c] == notDisc && col+c <= maxCol){
				c++;
			}
			if(board[row][col+c] == disc){
				mr = true;
			}
		}
		c = 1;

		//bl
		if(blOpp){
			while(board[row+c][col-c] == notDisc && row+c <= maxRow  && col-c >= minCol){
				c++;
			}
			if(board[row+c][col-c] == disc){
				bl = true;
			}
		}
		c = 1;

		
		//bm
		if(bmOpp){
			while(board[row+c][col] == notDisc && row+c <= maxRow){
				c++;
			}
			if(board[row+c][col] == disc){
				bm = true;
			}
		}
		c = 1;

		//br
		if(brOpp){
			while(board[row+c][col+c] == notDisc && row+c <= maxRow  && col+c <= maxCol){
				c++;
			}
			if(board[row+c][col+c] == disc){
				br = true;
			}
		}
		c = 1;
	} 

	if(tm){
		while(board[row-c][col] == notDisc){
			c++;
		}
		if(board[row-c][col] == disc){
			return true;
		}
	}
	c = 1;

	if(bm){
		while(board[row+c][col] == notDisc){
			c++;
		}
		if(board[row+c][col] == disc){
			return true;
		}
	}
	c = 1;

	if(ml){
		while(board[row][col-c] == notDisc){
			c++;
		}
		if(board[row][col-c] == disc){
			return true;
		};
	}
	c = 1;

	if(mr){
		while(board[row][col+c] == notDisc){
			c++;
		}
		if(board[row][col+c] == disc){
			return true;
		}
	}
	c = 1;

	if(tl){
		while(board[row-c][col-c] == notDisc){
			c++;
		}
		if(board[row-c][col-c] == disc){
			return true;
		};
	}
	c = 1;

	if(br){
		while(board[row+c][col+c] == notDisc){
			c++;
		}
		if(board[row+c][col+c] == disc){
			return true;
		}
	}
	c = 1;

	if(bl){
		while(board[row+c][col-c] == notDisc){
			c++;
		}
		if(board[row+c][col-c] == disc){
			return true;
		}
	}
	c = 1;

	if(tr){
		while(board[row-c][col+c] == notDisc){
			c++;
		}
		if(board[row-c][col+c] == disc){
			return true;
		};
	}
	c = 1;

	return false;
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

	int c = 1;

	bool tlFlips = false;
	bool tmFlips = false;
	bool trFlips = false;
	bool mlFlips = false;
	bool mrFlips = false;
	bool blFlips = false;
	bool bmFlips = false;
	bool brFlips =  false;
				
	bool tlOpp = (board[row-1][col-1] == notDisc && col-1 >= minCol && row-1 >= minRow);
	bool trOpp = (board[row-1][col+1] == notDisc && col+1 <= maxCol && row-1 >= minRow);
	bool tmOpp = (board[row-1][col] == notDisc && row-1 >= minRow);
	bool mrOpp = (board[row][col+1] == notDisc &&  col+1 <= maxCol);
	bool mlOpp = (board[row][col-1] == notDisc && col-1 >= minCol);
	bool blOpp = (board[row+1][col-1] == notDisc && col-1 >= minCol && row+1 <= maxRow);
	bool bmOpp = (board[row+1][col] == notDisc && row+1 <= maxRow);
	bool brOpp = (board[row+1][col+1] == notDisc && col+1 >= minCol && row+1 >= minRow);

	//tl
	if(tlOpp){
		while(board[row-c][col-c] == notDisc && row-c >= minRow && col-c >= minCol){
			c++;
		}
		if(board[row-c][col-c] == disc){
			tlFlips = true;
		}
	}
	c = 1;
	
	//tr
	if(trOpp){
		while(board[row-c][col+c] == notDisc && row-c >= minRow && col+c <= maxCol){
			c++;
		}
		if(board[row-c][col+c] == disc){
			trFlips = true;
		}
	}
	c = 1;

	//tm
	if(tmOpp){
		while(board[row-c][col] == notDisc && row-c >= minRow){
			c++;
		}
		if(board[row-c][col] == disc){
			tmFlips = true;
		}
	}
	c = 1;

	//ml
	if(mlOpp){
		while(board[row][col-c] == notDisc && col-c >= minCol){
			c++;
		}
		if(board[row][col-c] == disc){
			mlFlips = true;
		}
	}
	c = 1;

	//mr
	if(mrOpp){
		while(board[row][col+c] == notDisc && col+c <= maxCol){
			c++;
		}
		if(board[row][col+c] == disc){
			mrFlips = true;
		}
	}
	c = 1;

	//bl
	if(blOpp){
		while(board[row+c][col-c] == notDisc && row+c <= maxRow  && col-c >= minCol){
			c++;
		}
		if(board[row+c][col-c] == disc){
			blFlips = true;
		}
	}
	c = 1;

		
	//bm
	if(bmOpp){
		while(board[row+c][col] == notDisc && row+c <= maxRow){
			c++;
		}
		if(board[row+c][col] == disc){
			bmFlips = true;
		}
	}
	c = 1;

	//br
	if(brOpp){
		while(board[row+c][col+c] == notDisc && row+c <= maxRow  && col+c <= maxCol){
			c++;
		}
		if(board[row+c][col+c] == disc){
			brFlips = true;
		}
	}
	c = 1; 

	if(isValidMove(size,board,row,col,disc)){
		if(tlFlips){
			while(board[row-c][col-c] == notDisc){
				board[row-c][col-c] = disc;
				c++;
			}
		}
		c = 1;
		if(brFlips){
			while(board[row+c][col+c] == notDisc){
				board[row+c][col+c] = disc;
				c++;
			}
		}
		c = 1;
		if(trFlips){
			while(board[row-c][col+c] == notDisc){
				board[row-c][col+c] = disc;
				c++;
			}
		}
		c = 1;
		if(blFlips){
			while(board[row+c][col-c] == notDisc){
				board[row+c][col-c] = disc;
				c++;
			}
		}
		c = 1;
		if(mlFlips){
			while(board[row][col-c] == notDisc){
				board[row][col-c] = disc;
				c++;
			}
		}
		c = 1;
		if(mrFlips){
			while(board[row][col+c] == notDisc){
				board[row][col+c] = disc;
				c++;
			}
		}
		c = 1;
		if(bmFlips){
			while(board[row+c][col] == notDisc){
				board[row+c][col] = disc;
				c++;
			}
		}
		c = 1;
		if(tmFlips){
			while(board[row-c][col] == notDisc){
				board[row-c][col] = disc;
				c++;
			}
		}
		c = 1;
		board[row][col] = disc;
	}
 	//return;	
	// wonky still
}

/* Returns true if a valid move for disc is available; false otherwise */
bool isValidMoveAvailable(int size, char board[][size], char disc)
{
	for(int i = 0; i <= size; i++){
		for(int j = 0; j <= size; j++){
			if(isValidMove(size, board, i, j, disc) && board[i][j] == '-'){
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