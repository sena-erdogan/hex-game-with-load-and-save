/*
 * 	This is the header file for the library of hex game
 * 	Contains the declarations of the functions used in the program
 *
 */

#ifndef HEXLIB_H
#define HEXLIB_H

enum Cell{x = 'x', o = 'o', dot = '.'};

void fill_board(char board[][13], int& size);

void print_board(char board[][13], const int& size);

int x_win(char board[][13], char check[][13], int size);

int o_win(char board[][13], char check[][13], int size);

void add_move(char board[][13], int size, char letter, int num, int player);

void save_game(char board[][13], int size, int player, int computer, std::string input, char last_letter, int last_num);

void load_game(char board[][13], std::string input);

void user_vs_user(char board[][13], int size, int player);

void user_vs_computer(char board[][13], int size, int player, char last_letter, int last_num);

#endif
