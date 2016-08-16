#include<stdio.h>
#define X_MAX 3
#define Y_MAX 3
char board[X_MAX][Y_MAX];  //board for the game
char turn; // u for user and c for cpu
char user_symbol, cpu_symbol; 	//'X' or 'O' depending on whose turn is first

void initialise_board()	//initialise the board to start the game
{
	for(int x=0;x<X_MAX;x++)
	{
		for (int y=0;y<Y_MAX;y++)
		{
			board[x][y]='-';
		}
	}
}

void print_board()	//print the board
{
	for(int x=0;x<X_MAX;x++)
	{
		for (int y=0;y<Y_MAX;y++)
		{
			printf("%c  ",board[x][y]);
		}
		printf("\n");
	}
}

int fill_pos_in_board(int x, int y, char symbol)	//fill the (x,y) position in board if it is empty 
{
	if (x<X_MAX && y<Y_MAX && board[x][y]=='-')
	{	
		board[x][y]=symbol;
		return 0;
	}
	else
		return -1;
}

void user_turn()
{
	int row,column;
	printf("\n Enter the position in terms of row and column: ");
	scanf("%d%d",&row,&column);
	if (fill_pos_in_board(row-1,column-1,user_symbol)==-1)
	{
		printf("\n Wrong choice!");
		user_turn();
	}
		
}

void cpu_turn()
{
}

int has_won(char symbol) 	//returns 1 if the player with the symbol wins
{
	for(int i=0;i<X_MAX;i++)
	{
		if(board[i][0]==symbol && board [i][1]==symbol && board[i][2]==symbol)
			return 1;
		if(board[0][i]==symbol && board [1][i]==symbol && board[2][i]==symbol)
			return 1;
	}
	if(board[0][0]==symbol && board [1][1]==symbol && board[2][2]==symbol)
		return 1;
	if(board[0][2]==symbol && board [1][1]==symbol && board[2][0]==symbol)
		return 1;
	return 0;
	
}

void gameplay()
{
	char ans;
	initialise_board();
	printf("\n Lets start the game!");
	printf("\n Do you wanna take first turn? y/n: 	");
	scanf("%c",&ans);
	if (ans=='y')
	{	
		turn='u';
		user_symbol='X';
		cpu_symbol='O';
	}	
	else
	{
		turn='c';
		user_symbol='O';
		cpu_symbol='X';
	}
	print_board();
	while(1)
	{
		if (turn=='u')
		{
			user_turn();
			print_board();
			if (has_won(user_symbol))
			{
				printf("Congrats! You have won the game!");
				break;
			}
			turn='c';
		}
		else
		{
			cpu_turn();
			print_board();
			if (has_won(cpu_symbol))
			{
				printf("Oops! You have lost the game!");
				break;
			}
			turn='u';
		}
	}

}

int main()
{
	gameplay();
	return 0;
}

















