#include <iostream>
#include <fstream>
#include <string>
#include "hexlib.h"

/*
 Contains the definitions of the functions
 */

using namespace std;

void fill_board(char board[][13], int& size){

	for(int i = 0; i < 14; i++){

		for(int j = 0; j < 14; j++){

			if(i <= size && j <= size){

				if(i == 0 && j == 1)		board[i][j] = 'a';	//Specifies the cells' locations vertically
				else if(i == 1 && j == 0)	board[i][j] = '1';	//Specifies the cells' locations horizontally
				else if(i == 0 && j > 1) 	board[0][j] = board[0][j-1] + 1;
				else if(j == 0 && i > 1)	board[i][0] = board[i-1][0] + 1;
				else						board[i][j] = '.';	//Fills the parts of the board where the game will take place with '.'

			}else	board[i][j] = ' ';	//Fills the parts of the board that are out of the borders with ' '

	    }

	}

	board[0][0] = ' ';

}

void print_board(char board[][13], const int& size){

	for(int i = 0; i < size + 1; i++){

		if(i > 9)			cout << i;
		else				cout << board[i][0];

		for(int k = 0; k < i; k++)	cout << " "; /* To make the board appear a diamond shape, there are blank spaces left before every row,
													equal to the row number*/
		for(int j = 1; j < size + 1; j++){

			cout << board[i][j] << " ";

	    }

		cout << endl;

	}

}

int x_win(char board[][13], char check[][13], int size){ //Finds an x where letter is 'a', checks every possible way it can go to

	int num = 1, letter = 1;

	while(letter != size){

		if(num != size && board[num][letter] != 'x')	++num;
		else if(board[++num][--letter] == 'x'){

			check[num][letter] = 'x';		// If it finds an x on the way, it adds the location to the check array as 'x'
			++num;
			--letter;

		}else if(board[++num][letter] == 'x'){

			check[num][letter] = 'x';
			++num;

		}else if(board[num][++letter] == 'x'){

			check[num][letter] = 'x';
			++letter;

		}else if(board[num][--letter] == 'x'){

			check[num][letter] = 'x';
			--letter;

		}else if(board[--num][letter] == 'x'){

			check[num][letter] = 'x';
			--num;

		}else if(board[--num][++letter] == 'x'){

			check[num][letter] = 'x';
			--num;
			++letter;

		}else if(letter != size)	return 0;
		else{

			check[num][letter] = '*'; 	//If the way doesn't go to the very right, it marks the way back as '*'

		}

	}

	for(int i=1; i<=size; i++){

		for(int j=1; j<=size; j++){

			if(board[i][j] == check[i][j])	board[i][j] = 'X'; // The locations of the connected path is turned to 'X' on the original array

		}

	}

	return 1;

}

int o_win(char board[][13], char check[][13], int size){

	int num = 1, letter = 1;

	while(num != size){

		if(letter != size && board[num][letter] != 'o')	++letter;
		else if(board[++num][--letter] == 'o'){

			check[num][letter] = 'o';
			++num;
			--letter;

		}else if(board[++num][letter] == 'o'){

			check[num][letter] = 'o';
			++num;

		}else if(board[num][++letter] == 'o'){

			check[num][letter] = 'o';
			++letter;

		}else if(board[num][--letter] == 'o'){

			check[num][letter] = 'o';
			--letter;

		}else if(board[--num][letter] == 'o'){

			check[num][letter] = 'o';
			--num;

		}else if(board[--num][++letter] == 'o'){

			check[num][letter] = 'o';
			--num;
			++letter;

		}else if(num != size)	return 0;
		else{

			check[num][letter] = '*';

		}

	}

	for(int i=1; i<=size; i++){

		for(int j=1; j<=size; j++){

			if(board[i][j] == check[i][j])	board[i][j] = 'O';

		}

	}

	return 1;

}

void add_move(char board[][13], int size, char letter, int num, int player = 1){ //Adds the given move to the board

	if(player == 1)		board[num][letter - 64] = 'x'; 	// When the capital letters' ascii code is decremented by 64,
	else				board[num][letter - 64] = 'o';	// it gives us the row number of that letter

}

void save_game(char board[][13], int size, int player, int computer, string input, char last_letter, int last_num){ //player is 1 for user1, 2 for user2
														//computer is 1 for computer vs user, 0 for user vs user
	string filepath;
	int i=5;
	while(input[i] != '\0'){

		filepath[i-5] = input[i];
		i++;

	}

	ofstream fp;
	fp.open(filepath.c_str());

	if(!fp)		cerr << endl << "File could not be opened" << endl << endl;
	else{

		fp << size << " " <<  player << " " << computer << " ";
	
		for(int i=1; i<=size; i++){

			for(int j=1; j<=size; j++){

				if(board[i][j] == x)		fp << 'x';
				else if(board[i][j] == o)	fp << 'o';
				else if(board[i][j] == dot)	fp << '.';

			}

		}

		fp.close();

	}
	
	if(computer == 0)	user_vs_user(board, size, player);
	else if(computer == 1)	user_vs_computer(board, size, player, last_letter,last_num);

}

void load_game(char board[][13], string input){

	string filepath;
	char cell, last_letter;
	int i=5, size, player, computer, last_num;
	while(input[i] != '\0'){

		filepath[i-5] = input[i];
		i++;

	}

	ifstream fp;
	fp.open(filepath.c_str());

	if(!fp)		cerr << endl << "File does not exist" << endl << endl;
	else{

		fp >> size >> player >> computer;
	
		for(int i=1; i<=size; i++){

			for(int j=1; j<=size; j++){

				fp >> cell;

				if(cell == 'x')		board[i][j] = x;
				else if(cell == 'o')	board[i][j] = o;
				else if(cell == '.')	board[i][j] = dot;

			}

		}

		fp.close();

		if(computer == 1)	user_vs_computer(board, size, player, last_letter, last_num);
		else if(computer == 0)	user_vs_user(board, size, player);

	}

}

void user_vs_user(char board[][13], int size, int player){

	string input;
	char letter;
	int num;

	char check[13][13]; //Check will be a replica of the empty board, it will be used to check if a player won the game
	for(int i=0; i<13; i++){
		for(int j=0; j<13; j++)	check[i][j] = '*';
	}
	
	if(player == 1){
	
		print_board(board, size);

		do{
			input.clear();
			
			cout << "Player 1: ";
			getline(cin, input);

			if(input.length() == 3){
				letter = input[0];
				num = input[2] - 48;
			}else if(input.length() == 4){
				letter = input[0];
				num = (input[2] - 48)*10 + (input[3] - 48);
			}else if(input[1] == 'A')	save_game(board, size, 1, 0, input, 'A', 1);
			else if(input[1] == 'O')	load_game(board, input);

			if(board[num][letter - 64] != '.' || letter > 'L')	cerr << "Invalid move. Enter another move. " << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L');

		add_move(board, size, letter, num);

		if(x_win(board, check, size) == 1)		cout << endl << "Congratulations Player 1, you won!" << endl;
		
		print_board(board, size);

		do{			
			input.clear();

			cout << "Player 2: ";
			getline(cin, input);

			if(input.length() == 3){
				letter = input[0];
				num = input[2] - 48;
			}else if(input.length() == 4){
				letter = input[0];
				num = (input[2] - 48)*10 + (input[3] - 48);
			}else if(input[1] == 'A')	save_game(board, size, 2, 0, input, 'A', 1);
			else if(input[1] == 'O')	load_game(board, input);

			if(board[num][letter - 64] != '.' || letter > 'L')	cerr << "Invalid move. Enter another move. " << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L');

		add_move(board, size, letter, num, 2);

		if(o_win(board, check, size) == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;
	
	}else if(player == 2){
	
		print_board(board, size);

		do{			
			input.clear();

			cout << "Player 2: ";
			getline(cin, input);

			if(input.length() == 3){
				letter = input[0];
				num = input[2] - 48;
			}else if(input.length() == 4){
				letter = input[0];
				num = (input[2] - 48)*10 + (input[3] - 48);
			}else if(input[1] == 'A')	save_game(board, size, 2, 0, input, 'A', 1);
			else if(input[1] == 'O')	load_game(board, input);

			if(board[num][letter - 64] != '.' || letter > 'L')	cerr << "Invalid move. Enter another move. " << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L');

		add_move(board, size, letter, num, 2);

		if(o_win(board, check, size) == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;
	
	}
	
	cin.ignore();

	while(x_win(board, check, size) == 0 && o_win(board, check, size) == 0){ //The game will go on until a player wins the game since
											//there can't be a tie in a hex game
		print_board(board, size);

		do{
			input.clear();
			
			cout << "Player 1: ";
			getline(cin, input);

			if(input.length() == 3){
				letter = input[0];
				num = input[2] - 48;
			}else if(input.length() == 4){
				letter = input[0];
				num = (input[2] - 48)*10 + (input[3] - 48);
			}else if(input[1] == 'A')	save_game(board, size, 1, 0, input, 'A', 1);
			else if(input[1] == 'O')	load_game(board, input);

			if(board[num][letter - 64] != '.' || letter > 'L')	cerr << "Invalid move. Enter another move. " << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L');

		add_move(board, size, letter, num);

		if(x_win(board, check, size) == 1)		cout << endl << "Congratulations Player 1, you won!" << endl;
		else{

			print_board(board, size);

			do{
				input.clear();

				cout << "Player 2: ";
				getline(cin, input);

				if(input.length() == 3){
					letter = input[0];
					num = input[2] - 48;
				}else if(input.length() == 4){
					letter = input[0];
					num = (input[2] - 48)*10 + (input[3] - 48);
				}else if(input[1] == 'A')	save_game(board, size, 2, 0, input, 'A', 1);
				else if(input[1] == 'O')	load_game(board, input);

				if(board[num][letter - 64] != '.' || letter > 'L')	cerr << "Invalid move. Enter another move. " << endl;

			}while(board[num][letter - 64] != '.' || letter > 'L');

			add_move(board, size, letter, num, 2);

			if(o_win(board, check, size) == 1)	cout << endl << "Congratulations Player 2, you won!" << endl;

		}

	}

	print_board(board, size); //Prints the final board

}

void user_vs_computer(char board[][13], int size, int player, char last_letter, int last_num){

	string input;
	char letter, letter_c = 'A'; 						// letter_c and num_c represents computer's position
	int num, num_c = size / 2, count = -1; 			//the computer will start from the very left of the board and
											//try to make its way to the very right. Count is used to determine the moves the computer will make
	char check[13][13];									
	fill_board(check, size);
	
	if(player == 0){
	
		print_board(board, size);

		cout << "Computer: " << letter_c << " " << num_c << endl;

		add_move(board, size, letter_c, num_c);
	
	}else if(player == 1){
	
		letter_c = last_letter;
		num_c = last_num;
	
	}
	
	cin.ignore();

	while(x_win(board, check, size) == 0 && o_win(board, check, size) == 0){

		print_board(board, size);

		do{
			input.clear();
			
			cout << "Your move: ";
			getline(cin, input);

			if(input.length() == 3){
				letter = input[0];
				num = input[2] - 48;
			}else if(input.length() == 4){
				letter = input[0];
				num = (input[2] - 48)*10 + (input[3] - 48);
			}else if(input[1] == 'A')	save_game(board, size, 1, 1, input, letter_c, num_c);
			else if(input[1] == 'O')	load_game(board, input);

			if(board[num][letter - 64] != '.' || letter > 'L')	cerr << "Invalid move. Enter another move." << endl;

		}while(board[num][letter - 64] != '.' || letter > 'L'); // If that position is not marked by '.' or if it's greater then 'L',
																// player should pick another move
		add_move(board, size, letter, num, 2);

		if(o_win(board, check, size) == 1)	cout << endl << "Congratulations, you won!" << endl;
		else{

			print_board(board, size);

			count++;

			if(count == 0){ 		// Computer will go to one of the available positions on its six sides

				if(board[num_c][(letter_c - 64) + 1] != '.')	count += 2;
				else										letter_c++;

			}

			if(count == 1){

				if(board[num_c + 1][letter_c - 64] != '.')	count += 2;
				else											num_c++;

			}

			if(count == 2){

				if(board[num_c - 1][(letter_c - 64) + 1] != '.')	count += 2;
				else{

					letter_c++;
					num_c--;

				}

			}

			if(count == 3){

				if(board[num_c - 1][letter_c - 64] != '.')	count += 2;
				else										num_c--;

			}

			if(count == 4){

				if(board[num_c][(letter_c - 64) - 1] != '.')	count = (count + 3) % 6;
				else											letter_c--;

			}

			if(count == 5){

				if(board[num_c + 1][(letter_c - 64) - 1] != '.'){

					if(board[num_c - 1][(letter_c - 64) + 1] == '.'){

						letter_c++;
						num_c--;

					}

					count = -1;

				}
				else{

					letter_c--;
					num_c++;

				}

			}



			cout << "Computer: " << letter_c << " " << num_c << endl;

			add_move(board, size, letter_c, num_c);

			if(x_win(board, check, size) == 1)	cout << endl << "You lost..." << endl;

		}

	}

	print_board(board, size);

}

