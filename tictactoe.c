#include<stdio.h>
#define X_MAX 3
#define Y_MAX 3
char board[X_MAX][Y_MAX];  //board for the game
char turn; // u for user and c for cpu
char user_symbol, cpu_symbol; 	//'X' or 'O' depending on whose turn is first
int x_opt,y_opt;
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
	printf("\n");
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

void user_turn()		//let the user take his turn
{
	int row,column;
	printf("\nEnter the position in terms of row and column: ");
	scanf("%d%d",&row,&column);
	if (fill_pos_in_board(row-1,column-1,user_symbol)==-1)
	{
		printf("\n Wrong choice!");
		user_turn();
	}
		
}

int has_won(char symbol) 	//returns 1 if the player with the symbol wins and 0 if the game is draw else -1
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
	for (int x=0;x<X_MAX;x++)
		for(int y=0;y<Y_MAX;y++)
			if (board[x][y]=='-')
				return -1;
			
	return 0;
	
}

int optimal_choice()		//gives the score for the present state of board (minimax algo.)
{
	int optimal_score=-2,temp2;
	
	if(has_won(user_symbol)!=-1)
		return -1*has_won(user_symbol);
	if(has_won(cpu_symbol)!=-1)
		return has_won(cpu_symbol);
	for (int x=0;x<X_MAX;x++)
	{
		for (int y=0;y<Y_MAX;y++)
		{
			if(board[x][y]=='-')
			{
				if(turn=='c')
				{
					board[x][y]=cpu_symbol;
					turn='u';
					temp2 = optimal_choice();
					//printf("\n Score for %d and %d pos is %d \n",x,y,temp2);
					if(temp2>=optimal_score || optimal_score==-2)
					{
						optimal_score=temp2;
					}
					board[x][y]='-';
					turn='c';
				}
				else if(turn=='u')
				{
					board[x][y]=user_symbol;
					turn='c';
					temp2 = optimal_choice();
					if(temp2<=optimal_score || optimal_score==-2)
					{
						optimal_score=temp2;
					}
					board[x][y]='-';
					turn='u';
				}	

			}
		}
	}
//print_board();
return optimal_score;
}


void cpu_turn()		//lets cpu take the turn
{
int optimal_score=-1,temp2;
int x_opt,y_opt;
for (int x=0;x<X_MAX;x++)
	{
		for (int y=0;y<Y_MAX;y++)
		{
			if(board[x][y]=='-')
			{
				board[x][y]=cpu_symbol;
				turn='u';
				temp2 = optimal_choice();
				//printf("\n Score for %d and %d pos is %d \n",x,y,temp2);
				if(temp2>=optimal_score)
				{
					optimal_score=temp2;
					x_opt=x;
					y_opt=y;
				}
				board[x][y]='-';
				turn='c';
			}
		}
	}
fill_pos_in_board(x_opt,y_opt,cpu_symbol);	
}



void gameplay()		//the main game function
{
	char ans;
	initialise_board();
	printf("\nLets start the game!");
	printf("\nDo you wanna take first turn? y/n: 	");
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
	int temp;
	while(1)
	{
		if (turn=='u')
		{
			user_turn();
			print_board();	
			temp=has_won(user_symbol);
			if (temp==1)
			{
				printf("\nCongrats! You have won the game!\n");
				break;
			}
			else if(temp==0)
			{
				printf("\nIts a draw!\n");
				break;
			}
			turn='c';
		}
		else
		{
			cpu_turn();
			print_board();
			temp=has_won(cpu_symbol);
			if (temp==1)
			{
				printf("\nOops! You have lost the game!\n");
				break;
			}
			else if(temp==0)
			{
				printf("\nIts a draw!\n");
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

















