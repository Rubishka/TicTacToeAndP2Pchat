/*
 * TicTacToe.h
 *
 *  Created on: Aug 30, 2017
 *      Author: user
 */
#ifndef TICTACTOE_H_
#define TICTACTOE_H_


#include "Common.h"


using namespace std;

class TicTacToe
{

public:
	TCPSocket* server_sock;
	bool running;
	bool  playerTurn;
	char mat[3][3];
	// std::condition_variable cv;

	TicTacToe(TCPSocket* sock);
	int startGame();
	void play();
	void display();
	int endGame();
	int input(char choice, int x, int y);
};

#endif /* TICTACTOE_H_ */
