/*
 * TicTacToe.h
 *
 *  Created on: Aug 30, 2017
 *      Author: user
 */
#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "Common.h"
#include "ServerTicTacToe.h"

using namespace std;

class ServerTicTacToe{

public:
	char mat[3][3];
	TCPSocket* user1Socket, *user2Socket;


	ServerTicTacToe(TCPSocket* socket1,TCPSocket* socket2);
	int startGame();
	void display();
	char check();
	int input(char choice, int x, int y);
	virtual ~ServerTicTacToe();

};
#endif /* TICTACTOE_H_ */
